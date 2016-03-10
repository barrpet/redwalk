#ifndef REDWALK_TYPES_H
#define REDWALK_TYPES_H

#include <cstddef>
#include <limits>
#include <vector>
#include <Eigen/Dense>
#include "macros.hpp"

namespace redwalk
{
  typedef double float_t;
  typedef unsigned long index_t;
  typedef unsigned long vertex_id_t;
  typedef unsigned short ushort_t;
  typedef unsigned char uchar_t;

  typedef float_t flt_t;
  typedef index_t idx_t;
  typedef vertex_id_t vid_t;
  
  typedef std::vector<vid_t> vertex_list;

  typedef Eigen::Matrix<float_t, Eigen::Dynamic, Eigen::Dynamic> MatrixF;
  typedef Eigen::Matrix<ushort_t, Eigen::Dynamic, Eigen::Dynamic> MatrixUS;

  static RW_CONSTEXPR_OR_CONST vid_t NONE = std::numeric_limits<vid_t>::max();
  static RW_CONSTEXPR_OR_CONST ushort_t INF_US = std::numeric_limits<ushort_t>::max();

  static RW_CONSTEXPR_OR_CONST flt_t INF_F = std::numeric_limits<flt_t>::infinity();
  static RW_CONSTEXPR_OR_CONST flt_t NAN_F = std::numeric_limits<flt_t>::quiet_NaN();
  static RW_CONSTEXPR_OR_CONST flt_t ZERO_F = flt_t(0);
  static RW_CONSTEXPR_OR_CONST flt_t ONE_F = flt_t(1);
  static RW_CONSTEXPR_OR_CONST flt_t NEG_ONE_F = flt_t(-1);
  static RW_CONSTEXPR_OR_CONST flt_t HALF_F = flt_t(0.5);
};

#endif //REDWALK_TYPES_H
