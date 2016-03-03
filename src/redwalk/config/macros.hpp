#ifndef REDWALK_MACROS
#define REDWALK_MACROS

#define REDWALK_VERSION "0.1"
#define REDWALK_MAJOR_VERSION 0
#define REDWALK_MINOR_VERSION 1

#define REDWALK_VERSION_AT_LEAST(x,y) ((REDWALK_MAJOR_VERSION>=x) && \
                                       (REDWALK_MINOR_VERSION>=y))

#if __cplusplus >= 201103L
#  define _RW_CXX11 1
#  define RW_NULLPTR nullptr
#  define RW_CONSTEXPR constexpr
#  define RW_CONSTEXPR_OR_CONST constexpr
#else
#  ifdef NULL
#    define RW_NULLPTR NULL
#  else
#    define RW_NULLPTR 0
#  endif
#  define RW_CONSTEXPR
#  define RW_CONSTEXPR_OR_CONST const
#endif

#endif //REDWALK_MACROS
