#ifndef REDWALK_MACROS_HPP
#define REDWALK_MACROS_HPP

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

#endif //REDWALK_MACROS_HPP

