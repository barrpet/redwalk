#include "dissimilarity.hpp"
#include "paths.hpp"
#include "graph/adjacency_array.hpp"
#include <Eigen/Sparse>
#include <vector>

namespace redwalk
{

std::vector<double> dissimilarity_sp(const adjacency_array<vid_t>& adj,
                                     const MatrixUS& sp)
{
  //Get number of vertices
  idx_t nv = adj.vcount();

  //Allocate D2 - what will become a "dist"
  //number of entries in contiguous symmetric matrix with no diagonal
  std::vector<double> D((nv * nv - nv) >> 1, 0.0);

  //Do avg shortest paths of neighbors
  //TODO: optimize
  idx_t idx = 0;
  redwalk::flt_t mspi, mspj;
  for(idx_t i = 0; i < (nv-1); i++)
  {
    NeighborhoodList<vid_t> nbrsi = adj[i];
    idx_t degi = nbrsi.size();
    for(idx_t j = (i+1); j < nv; j++)
    {
      mspi = 0; mspj = 0;
      NeighborhoodList<vid_t> nbrsj = adj[j];
      idx_t degj = nbrsj.size();
      for(idx_t n = 0; n < degi; n++)
        mspi += sp(nbrsi[n],j);
      mspi /= degi;
      for(idx_t n = 0; n < degj; n++)
        mspj += sp(nbrsj[n],i);
      mspj /= degj;
      D[idx] = (mspi < mspj) ? mspi : mspj;
      idx++;
    }
  }

  return D;
}

std::vector<double> dissimilarity_subsets_sp(
  const adjacency_array<vid_t>& adj,
  const vertex_list& s, const redwalk::MatrixUS& sp)
{
  const idx_t nv = adj.vcount();
  const idx_t ns = s.size();

  //to check if a vertex is a target
  std::vector<bool> is_targ(nv, false);
  for(idx_t i = 0; i < ns; i++)
    is_targ[s[i]] = true;

  //Set up triplet list for sparse matrix
  typedef Eigen::Triplet<redwalk::flt_t> Triplet;
  std::vector<Triplet> tripletList;
  tripletList.reserve(nv + 2 * adj.ecount()); //TODO: reserve exact or close to

  //Build the tripletlist
  for(idx_t i = 0; i < nv; i++)
  {
    tripletList.push_back(Triplet(i, i, redwalk::ONE_F));
    if(!is_targ[i])
    {
      redwalk::flt_t val = redwalk::NEG_ONE_F / (redwalk::flt_t)adj.degree(i);
      NeighborhoodList<vid_t> nbrs = adj[i];
      NeighborhoodList<vid_t>::iterator nitr;
      for(nitr = nbrs.begin(); nitr != nbrs.end(); nitr++)
        tripletList.push_back(Triplet(i,*nitr,val));
    }
  }

  //set up the random walk normalized laplacian
  Eigen::SparseMatrix<redwalk::flt_t> L(nv, nv);
  L.setFromTriplets(tripletList.begin(), tripletList.end());
  L.makeCompressed();

  //free the triplets
  std::vector<Triplet>().swap(tripletList);

  //factor the RWNL
  Eigen::SparseLU<Eigen::SparseMatrix<redwalk::flt_t, Eigen::ColMajor>,
                  Eigen::COLAMDOrdering<int> > solver;
  solver.analyzePattern(L);
  solver.factorize(L);

  //setup b
  redwalk::MatrixF b(nv, ns);
  b.fill(0);
  for(idx_t i = 0; i < ns; i++)
    b.row(s[i]) = sp.col(i).cast<redwalk::flt_t>();

  //Solve
  const redwalk::MatrixF x = solver.solve(b);

  //Free b
  b.resize(0,0);

  //Free L
  Eigen::SparseMatrix<redwalk::flt_t, Eigen::ColMajor>().swap(L);

  //Allocate D - what will become a "dist"
  //number of entries in contiguous symmetric matrix with no diagonal
  std::vector<double> D((ns * ns - ns) >> 1, 0.0);

  idx_t idx = 0;
  redwalk::flt_t mspi, mspj;
  for(idx_t i = 0; i < (ns-1); i++)
  {
    vid_t ti = s[i];
    idx_t degi = adj.degree(ti);
    NeighborhoodList<vid_t> nbrsi = adj[ti];
    for(idx_t j = i+1; j < ns; j++)
    {
      vid_t tj = s[j];
      idx_t degj = adj.degree(tj);
      NeighborhoodList<vid_t> nbrsj = adj[tj];
      mspi = 0; mspj = 0;
      for(idx_t n = 0; n < degi; n++)
        mspi += x(nbrsi[n],j);
      mspi /= degi;
      for(idx_t n = 0; n < degj; n++)
        mspj += x(nbrsj[n],i);
      mspj /= degj;
      D[idx] = (mspi < mspj) ? mspi : mspj;
      idx++;
    }
  }

  return D;
}

} //namespace redwalk
