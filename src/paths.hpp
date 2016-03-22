#ifndef REDWALK_PATHS_H
#define REDWALK_PATHS_H

#include "types.hpp"
#include "graph/adjacency_array.hpp"

namespace redwalk
{

redwalk::MatrixUS shortest_path_lengths(const adjacency_array<vid_t>& adj);

redwalk::MatrixUS shortest_path_lengths_subsets(const adjacency_array<vid_t>& adj,
  const vertex_list& s);
 
}

#endif //REDWALK_PATHS_H


