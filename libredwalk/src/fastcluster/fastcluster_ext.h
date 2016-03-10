#ifndef FASTCLUSTER_EXT_H
#define FASTCLUSTER_EXT_H

//------------------------------------------------------------------------------
//fixes for missing R macros
#ifndef RMATH_H
#include <cmath>
#include <limits>
#include <stdexcept> // for std::runtime_error
#include <string> // for std::string

static const double FC_INF = std::numeric_limits<double>::infinity();
static const double FC_NINF = -FC_INF;

#define R_pow(x,y) std::pow(x,y)

#if __cplusplus >= 201103L
#  define R_FINITE(X) std::isfinite(X)
#else
#  define R_FINITE(X) (((X)!=(FC_INF))&&((X)!=(FC_NINF)))
#endif

#ifndef ISNAN
#  if __cplusplus >= 201103L
#    define ISNAN(X) isnan(X)
#  else
#    define ISNAN(X) ((X)!=(X))
#  endif
#endif
  
#ifndef NA_REAL
#  if __cplusplus >= 201103L
#    define NA_REAL std::nan("")
#  else
#    define NA_REAL (double)NAN
#  endif
#endif

#ifndef FC_NULLPTR
#if __cplusplus >= 201103L
#  define FC_NULLPTR nullptr
#else
#  ifdef NULL
#    define FC_NULLPTR NULL
#  else
#    define FC_NULLPTR 0
#  endif
#endif
#endif

#define Rf_isNull(X) ((X) == (FC_NULLPTR))

typedef unsigned long R_xlen_t;

#define Rf_error(X) throw std::runtime_error(std::string(X))
//#define Rf_error(X) int y = 3;
#define R_NilValue 0
#define INTEGER_VALUE(X) X
#define PROTECT(X) 
#define UNPROTECT(X) 
#define NUMERIC_POINTER(X) X
#define INTEGER_POINTER(X) X

#endif
//------------------------------------------------------------------------------



#endif //FASTCLUSTER_EXT_H
