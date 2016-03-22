#ifndef ADJACENCY_ARRAY_HPP
#define ADJACENCY_ARRAY_HPP

#include "graph_base.hpp"

namespace redwalk
{

////////////////////////////////////////////////////////////////////////////////
// ADJACENCY ARRAY
////////////////////////////////////////////////////////////////////////////////
template <typename vertex_id_t>
class adjacency_array : public graph_base<vertex_id_t>
{
public:
  typedef graph_base<vertex_id_t> graph;
  typedef typename graph::vid_t   vid_t;
  typedef typename graph::vid_t   idx_t;
  typedef typename graph::vid_t*  pointer;
  typedef typename graph::NeighborList NeighborList;

private:
  pointer  adj_ = nullptr;
  pointer* vtx_ = nullptr;

public:
  template <typename ForwardIterator>
  adjacency_array(ForwardIterator beg, ForwardIterator end, bool rowMajor = false) : graph_base<vid_t>()
  {
    if(rowMajor) {
      this->setFromEdgeList<ForwardIterator, true>(beg, end);
    } else {
      this->setFromEdgeList<ForwardIterator, false>(beg, end);
    }
  }

  virtual ~adjacency_array()
  {
    delete [] adj_;
    delete [] vtx_;
  }

  template <typename Iterator, bool RowMajor = false>
  void setFromEdgeList(Iterator beg, Iterator end)
  {
    const idx_t nv = *(std::max_element(beg, end)) + 1;
    const idx_t ne = std::distance(beg, end) >> 1;
    this->set_nv(nv);
    this->set_ne(ne);
    if(!(nv && ne)) { return; }
    adj_ = new vid_t[2 * ne];
    vtx_ = new vid_t*[nv + 1];

    //Get degree of each vertex
    idx_t* deg = new idx_t[nv];
    std::fill(&deg[0], &deg[nv], 0);
    for(Iterator el = beg; el != end; el++)
      deg[*el]++;

    //Set heads
    vtx_[0] = &adj_[0];
    vtx_[nv] = &adj_[ne << 1];
    for(idx_t v = 1; v < nv; v++)
      vtx_[v] = vtx_[v-1] + deg[v-1];

    //Clear degree
    std::fill(&deg[0], &deg[nv], 0);

    //Set adjacency array
    Iterator e0 = beg;
    Iterator e1 = (RowMajor) ? (e0 + 1) : (e0 + ne);
    const idx_t inc = (RowMajor) ? 2 : 1;
    while((e1 != end) && (e0 != end))
    {
      vid_t v0 = *e0;
      vid_t v1 = *e1;
      *(vtx_[v0] + deg[v0]) = v1;
      *(vtx_[v1] + deg[v1]) = v0;
      deg[v0]++; deg[v1]++;
      e0 += inc; e1 += inc;
    }

    //Delete degree array
    delete [] deg;
  }

  virtual inline NeighborList operator[](vid_t v) const override
  { return NeighborList(vtx_[v], vtx_[v+1]); }

  virtual inline idx_t degree(vid_t v) const override
  { return vtx_[v+1] - vtx_[v]; }

};  //class adjacency_array

} //namespace redwalk

#endif //ADJACENCY_ARRAY_HPP
