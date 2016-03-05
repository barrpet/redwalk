#ifndef REDWALK_OPENMP_H
#define REDWALK_OPENMP_H

#include <Rconfig.h>

#ifdef SUPPORT_OPENMP
#ifdef _OPENMP
  #include <omp.h>
  #if _OPENMP >= 201307
    #define OMP_V4
  #endif
#else
  typedef int omp_int_t;
  inline omp_int_t omp_get_thread_num()  { return 0; }
  inline omp_int_t omp_get_num_threads() { return 1; }
  inline omp_int_t omp_get_max_threads() { return 1; }
  inline omp_int_t omp_in_parallel()     { return false; }
#endif //_OPENMP
#endif //SUPPORT_OPENMP

#endif //REDWALK_OPENMP_H