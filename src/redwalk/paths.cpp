#include <redwalk/paths.hpp>
#include <vector>
#include <queue>
#include <stdexcept>
#include <string>

namespace redwalk
{

MatrixUS shortest_path_lengths(const adjacency_array<vid_t>& adj)
{
  const idx_t nv = adj.vcount();
  MatrixUS sp(nv, nv);
  sp.setConstant(INF_US);

  std::vector<vid_t> already_counted(nv, 0);
  std::queue<vid_t> q;
  for(vid_t v = 0; v < nv; v++)
  {
    already_counted[v] = v + 1;
    sp(v,v) = 0;
    q.push(v);
    while(!q.empty())
    {
      vid_t u = q.front(); q.pop();
      NeighborhoodList<vid_t> nbrs = adj[u];
      NeighborhoodList<vid_t>::iterator itr;
      for(itr = nbrs.cbegin(); itr != nbrs.cend(); itr++)
      {
        vid_t n = *itr;
        if(already_counted[n] == v + 1) { continue; }
        already_counted[n] = v + 1;
        sp(n,v) = sp(u,v) + 1;
        q.push(n);
      }
    }
  }
  return sp;
}

MatrixUS shortest_path_lengths_subsets(const adjacency_array<vid_t>& adj,
  const std::vector<vid_t>& s)
{
  const idx_t nv = adj.vcount();
  const idx_t ns = s.size();
  if(ns == nv)
    return shortest_path_lengths(adj);

  std::vector<vid_t> already_counted(nv, 0);
  std::vector<vid_t> indexv(nv, 0);
  std::queue<vid_t> q;
  std::queue<ushort_t> d;
  idx_t j = 0;
  for(idx_t vi = 0; vi < ns; vi++)
  {
    vid_t v = s[vi];
    if(indexv[v] != 0)
      throw std::runtime_error(std::string("error: duplicate vertices in S"));
    indexv[v] = ++j;
  }
  MatrixUS sp(ns, ns);
  sp.setConstant(INF_US);
  for(vid_t vi = 0; vi < ns; vi++)
  {
    int v = s[vi];
    sp(vi,vi) = 0;
    vertex_id_t reached = 0;
    q.push(v);
    d.push(0);
    already_counted[v] = vi + 1;
    while(!q.empty())
    {
      int u = q.front(); q.pop();
      int ud = d.front(); d.pop();
      if(indexv[u] != 0)
      {
        sp(vi, indexv[u]-1) = ud;
        reached++;
        if(reached == ns)
        {
          #ifdef _RW_CXX11
            std::queue<vid_t>().swap(q);
            std::queue<ushort_t>().swap(d);
          #else
            while(!q.empty()) { q.pop(); }
            while(!d.empty()) { d.pop(); }
          #endif
          break;
        }
      }
      NeighborhoodList<vid_t> nbrs = adj[u];
      NeighborhoodList<vid_t>::iterator nitr;
      for(nitr = nbrs.begin(); nitr != nbrs.end(); nitr++)
      {
        vid_t n = *nitr;
        if(already_counted[n] == vi + 1) { continue; }
        already_counted[n] = vi + 1;
        q.push(n);
        d.push(ud+1);
      }
    }
  }
  return sp;
}

} //namespace redwalk
