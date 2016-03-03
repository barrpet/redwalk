project(redwalk)
cmake_minimum_required(VERSION 2.8.5)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# guard against bad build-type strings
string(TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if(    NOT cmake_build_type_tolower STREQUAL "debug"
   AND NOT cmake_build_type_tolower STREQUAL "release")
  message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug and Release (case-insensitive).")
endif()

#############################################################################
# retrieve version infomation                                               #
#############################################################################

# automatically parse the version number
file(READ "${PROJECT_SOURCE_DIR}/src/redwalk/config/macros.hpp" _redwalk_version_header)
string(REGEX MATCH "define[ \t]+REDWALK_MAJOR_VERSION[ \t]+([0-9]+)" _redwalk_major_version_match "${_redwalk_version_header}")
set(REDWALK_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+REDWALK_MINOR_VERSION[ \t]+([0-9]+)" _redwalk_minor_version_match "${_redwalk_version_header}")
set(REDWALK_MINOR_VERSION "${CMAKE_MATCH_1}")
set(REDWALK_VERSION_NUMBER ${REDWALK_MAJOR_VERSION}.${REDWALK_MINOR_VERSION})

include(ExternalProject)
include(CheckCXXCompilerFlag)
include(GNUInstallDirs)

# set cmake modules path
set(CMAKE_MODULE_PATH ${redwalk_SOURCE_DIR}/cmake)

# find eigen3
find_package(Eigen3 3.2.5 REQUIRED)

# pkg-config
if(NOT WIN32)
  option(REDWALK_BUILD_PKGCONFIG "Build pkg-config .pc file for redwalk" ON)
endif(NOT WIN32)

# Check compiler flag and add it if available
macro(redwalk_add_cxx_compiler_flag FLAG)
  string(REGEX REPLACE "-" "" SFLAG ${FLAG})
  check_cxx_compiler_flag(${FLAG} COMPILER_SUPPORT_${SFLAG})
  if(COMPILER_SUPPORT_${SFLAG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
  endif()
endmacro(redwalk_add_cxx_compiler_flag)

# set include path
include_directories(${redwalk_SOURCE_DIR}/src)

if(NOT MSVC)
  # We assume that other compilers are partly compatible with GNUCC
  
  #compiler flags
  redwalk_add_cxx_compiler_flag("-Wall")
  redwalk_add_cxx_compiler_flag("-Wextra")
  redwalk_add_cxx_compiler_flag("-Wno-attributes")
  redwalk_add_cxx_compiler_flag("-Wno-deprecated-declarations")
  redwalk_add_cxx_compiler_flag("-Wno-ignored-qualifiers")
  redwalk_add_cxx_compiler_flag("-march=native")
  
  check_cxx_compiler_flag("-fopenmp" COMPILER_SUPPORT_OPENMP)
  if(COMPILER_SUPPORT_OPENMP)
    option(REDWALK_ENABLE_OPENMP "Enable/Disable OpenMP" ON)
    if(REDWALK_ENABLE_OPENMP AND NOT NO_OPENMP)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
      set(REDWALK_OPENMP_STATUS "enabled")
      message(STATUS "Enabling OpenMP")
    endif()
  endif()
  
  if(cmake_build_type_tolower STREQUAL "release")
    redwalk_add_cxx_compiler_flag("-mtune=native")
  elseif()
  endif()
  
  set(CMAKE_C_FLAGS_DEBUG "-O0 -g0 -Winit-self")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g0 -Winit-self")
  set(CMAKE_C_FLAGS_RELEASE "-O3 -g3")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g3")
  
else(NOT MSVC)
# TODO: MSVC FLAGS AND OPTIONS
endif(NOT MSVC)

if(REDWALK_BUILD_PKGCONFIG)
  configure_file(redwalk.pc.in redwalk.pc @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/redwalk.pc
    DESTINATION ${CMAKE_INSTALL_DATADIR}/pkgconfig
  )
endif(REDWALK_BUILD_PKGCONFIG)

# Set install dirs
if(NOT CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_BINDIR bin)
endif()
if(NOT CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR lib)
endif()
if(NOT CMAKE_INSTALL_INCLUDEDIR)
  set(CMAKE_INSTALL_INCLUDEDIR include)
endif()

# Set subdirectories
subdirs(
  src
  test
)

# Set installation rules
install(DIRECTORY src/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"  PATTERN "*.h"
  PATTERN ".git"  PATTERN "Eigen" EXCLUDE
)


## =============================================================================

if (CMAKE_BUILD_TYPE MATCHES "Release")
  message(STATUS "Release build with C++ flags: " ${CMAKE_CXX_FLAGS_RELEASE} ${CMAKE_CXX_FLAGS})
  message(STATUS "Release build with C flags: " ${CMAKE_C_FLAGS_RELEASE} ${CMAKE_C_FLAGS})
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Debug build with C++ flags: " ${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS})
  message(STATUS "Debug build with C flags: " ${CMAKE_C_FLAGS_DEBUG} ${CMAKE_C_FLAGS})
endif()

string(TOLOWER "${CMAKE_GENERATOR}" cmake_generator_tolower)
if(cmake_generator_tolower MATCHES "makefile")
  message(STATUS "redwalk v${REDWALK_VERSION_NUMBER}")
  message(STATUS "---------------+--------------------------------------------------------------")
  message(STATUS "OPTIONS        |   VALUES")
  message(STATUS "---------------+--------------------------------------------------------------")
  message(STATUS "Build Type     | ${CMAKE_BUILD_TYPE}")
  message(STATUS "C Flags        | ${CMAKE_C_FLAGS}")
  message(STATUS "C++ Flags      | ${CMAKE_CXX_FLAGS}")
  message(STATUS "OpenMP         | ${REDWALK_OPENMP_STATUS}")
  message(STATUS "Install Prefix | ${CMAKE_INSTALL_PREFIX}")
  message(STATUS "Include Dir    | ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  message(STATUS "Library Dir    | ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  message(STATUS "Binary Dir     | ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
  message(STATUS "---------------+--------------------------------------------------------------")
else()
  message(STATUS "")
  message(STATUS "")
endif()

message(STATUS "")
