#ifndef REDWALK_DISSIMILARITY_H
#define REDWALK_DISSIMILARITY_H

#include "types.hpp"
#include "graph/adjacency_array.hpp"

namespace redwalk
{

std::vector<double> dissimilarity_sp(const adjacency_array<vid_t>& adj,
  const MatrixUS& sp);

std::vector<double> dissimilarity_subsets_sp(const adjacency_array<vid_t>& adj,
  const vertex_list& s, const MatrixUS& sp);

}

#endif //REDWALK_DISSIMILARITY_H
