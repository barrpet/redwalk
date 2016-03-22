#ifndef FASTCLUSTER_H
#define FASTCLUSTER_H

//------------------------------------------------------------------------------
// FC_NULLPTR (C++11)
//------------------------------------------------------------------------------
#if __cplusplus >= 201103L
#  define FC_NULLPTR nullptr
#else
#  ifdef NULL
#    define FC_NULLPTR NULL
#  else
#    define FC_NULLPTR 0
#  endif
#endif
//------------------------------------------------------------------------------

#include <limits>

#include <cfloat> // also for DBL_MAX, DBL_MIN
#ifndef DBL_MANT_DIG
#error The constant DBL_MANT_DIG could not be defined.
#endif
#define T_FLOAT_MANT_DIG DBL_MANT_DIG

#ifndef LONG_MAX
#include <climits>
#endif
#ifndef LONG_MAX
#error The constant LONG_MAX could not be defined.
#endif
#ifndef INT_MAX
#error The constant INT_MAX could not be defined.
#endif

#ifndef INT32_MAX
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#endif

//TODO; fix this
typedef int t_index;
//typedef int_fast32_t t_index;
#ifndef INT32_MAX
#define MAX_INDEX 0x7fffffffL
#else
#define MAX_INDEX INT32_MAX
#endif
#if (LONG_MAX < MAX_INDEX)
#error The integer format "t_index" must not have a greater range than "long int".
#endif
#if (INT_MAX > MAX_INDEX)
#error The integer format "int" must not have a greater range than "t_index".
#endif
typedef double t_float;

//------------------------------------------------------------------------------
// METHOD CODES
//------------------------------------------------------------------------------
enum method_codes {
  // non-Euclidean methods
  METHOD_METR_SINGLE           = 0,
  METHOD_METR_COMPLETE         = 1,
  METHOD_METR_AVERAGE          = 2,
  METHOD_METR_WEIGHTED         = 3,
  METHOD_METR_WARD             = 4,
  METHOD_METR_WARD_D           = METHOD_METR_WARD,
  METHOD_METR_CENTROID         = 5,
  METHOD_METR_MEDIAN           = 6,
  METHOD_METR_WARD_D2          = 7,

  MIN_METHOD_CODE              = 0,
  MAX_METHOD_CODE              = 7
};

enum method_codes_vector {
  // Euclidean methods
  METHOD_VECTOR_SINGLE         = 0,
  METHOD_VECTOR_WARD           = 1,
  METHOD_VECTOR_CENTROID       = 2,
  METHOD_VECTOR_MEDIAN         = 3,

  MIN_METHOD_VECTOR_CODE       = 0,
  MAX_METHOD_VECTOR_CODE       = 3
};

enum {
  METRIC_R_EUCLIDEAN = 0,
  METRIC_R_MAXIMUM   = 1,
  METRIC_R_MANHATTAN = 2,
  METRIC_R_CANBERRA  = 3,
  METRIC_R_BINARY    = 4,
  METRIC_R_MINKOWSKI = 5
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MERGE CONTAINER
//------------------------------------------------------------------------------
template <typename IntType, typename FloatType>
class Merge
{
private:
  IntType      N_;        //number of nodes
  IntType*     merge_;    //(N-1)x2 matrix
  FloatType*   height_;   //N-1 vector
  IntType*     order_;    //N vector

private:
  void fill_zero()
  {
    if(N_ == 0) { return; }
    for(IntType i = 0; i < N_; i++)
    {
      order_[i] = 0;
      if(i < N_-1) { height_[i] = 0; }
    }
    for(IntType i = 0; i < ((N_-1)*2); i++)
      merge_[i] = 0.0;
  }
  
public:
  Merge()
    : N_(0), merge_(FC_NULLPTR), height_(FC_NULLPTR), order_(FC_NULLPTR) { }
    
  Merge(const Merge& m)
    : N_(0), merge_(FC_NULLPTR), height_(FC_NULLPTR), order_(FC_NULLPTR)
  {
    this->init(m.N_);
    for(IntType i = 0; i < N_; i++)
    {
      order_[i] = m.order_[i];
      if(i < (N_-1))
        height_[i] = m.height_[i];
    }
    for(IntType i = 0; i < ((N_-1)*2); i++)
    {
      merge_[i] = m.merge_[i];
    }
  }
  
  Merge& operator=(const Merge& m)
  {
    if(this == &m) { return *this; }
    if(N_ != m.N_)
    {
      this->free();
      this->init(m.N_);
    }
    for(IntType i = 0; i < N_; i++)
    {
      order_[i] = m.order_[i];
      if(i < (unsigned int)N_-1)
        height_[i] = m.height_[i];
    }
    for(unsigned int i = 0; i < ((unsigned int)N_-1)*2; i++)
    {
      merge_[i] = m.merge_[i];
    }
    return *this;
  }

#if __cplusplus >= 201103L
  Merge(Merge&& m)
  {
    merge_ = m.merge_;
    height_ = m.height_;
    order_ = m.order_;
    N_ = m.N_;
    m.merge_ = FC_NULLPTR;
    m.height_ = FC_NULLPTR;
    m.order_ = FC_NULLPTR;
    m.N_ = 0;
  }
  
  Merge& operator=(Merge&& m)
  {
    if(this == &m) { return *this; }
    this->free();
    merge_ = m.merge_;
    height_ = m.height_;
    order_ = m.order_;
    N_ = m.N_;
    m.merge_ = FC_NULLPTR;
    m.height_ = FC_NULLPTR;
    m.order_ = FC_NULLPTR;
    m.N_ = 0;
    return *this;
  }
#endif

  Merge(unsigned int N) : N_(0) { init(N); }
  ~Merge() { free(); }
  
  void free()
  {
    if(N_ == 0) { return; }
    delete [] merge_;
    delete [] height_;
    delete [] order_;
    merge_ = FC_NULLPTR;
    height_ = FC_NULLPTR;
    order_ = FC_NULLPTR;
    N_ = 0;
  }
  
  void init(unsigned int N)
  {
    if(N != static_cast<unsigned int>(N_))
    {
      free();
      N_ = N;
      merge_ = new IntType[(N_-1)*2];
      height_ = new FloatType[N_-1];
      order_ = new IntType[N_];
    }
    fill_zero();
  }
  
  IntType get_n() const { return N_; }
  IntType  size() const { return N_; }
  
  IntType*    merge() { return merge_;  }
  FloatType* height() { return height_; }
  IntType*    order() { return order_;  }
  
  const IntType*    merge() const { return merge_;  }
  const FloatType* height() const { return height_; }
  const IntType*    order() const { return order_;  }
};

typedef Merge<int, double> MergeFC;
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// MAIN FASTCLUSTER FUNCTION
//------------------------------------------------------------------------------
extern "C" {
MergeFC* fastcluster(int const N_,
                     method_codes const method_,
                     const double* D_,
                     const int* members_ = FC_NULLPTR);
}
//------------------------------------------------------------------------------
#endif //FASTCLUSTER_H
