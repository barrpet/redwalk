cmake_minimum_required(VERSION 3.1.0)
project(libredwalk CXX)

################################################################################
# BUILD OPTIONS AND GUARDS
################################################################################
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

################################################################################
# BUILD OPTIONS AND GUARDS
################################################################################
# automatically parse the version number
file(READ "${PROJECT_SOURCE_DIR}/include/src/config/macros.hpp" _redwalk_version_header)
string(REGEX MATCH "define[ \t]+REDWALK_MAJOR_VERSION[ \t]+([0-9]+)" _redwalk_major_version_match "${_redwalk_version_header}")
set(LIBREDWALK_MAJOR_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "define[ \t]+REDWALK_MINOR_VERSION[ \t]+([0-9]+)" _redwalk_minor_version_match "${_redwalk_version_header}")
set(LIBREDWALK_MINOR_VERSION "${CMAKE_MATCH_1}")
set(LIBREDWALK_VERSION_NUMBER ${REDWALK_MAJOR_VERSION}.${REDWALK_MINOR_VERSION})

# set cmake modules path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(LIBREDWALK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIBREDWALK_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

################################################################################
# COMPILER
################################################################################
include(CheckCXXCompilerFlag)

macro(redwalk_add_cxx_compiler_flag FLAG)
  string(REGEX REPLACE "-" "" SFLAG ${FLAG})
  check_cxx_compiler_flag(${FLAG} COMPILER_SUPPORT_${SFLAG})
  if(COMPILER_SUPPORT_${SFLAG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG}")
  endif()
endmacro(redwalk_add_cxx_compiler_flag)

if(NOT MSVC)
  #compiler flags
  redwalk_add_cxx_compiler_flag("-Wall")
  redwalk_add_cxx_compiler_flag("-Wextra")
  redwalk_add_cxx_compiler_flag("-Wno-attributes")
  redwalk_add_cxx_compiler_flag("-Wno-deprecated-declarations")
  redwalk_add_cxx_compiler_flag("-Wno-ignored-qualifiers")
  redwalk_add_cxx_compiler_flag("-march=native")
  
  set(REDWALK_OPENMP_STATUS "unsupported")
  check_cxx_compiler_flag("-fopenmp" COMPILER_SUPPORT_OPENMP)
  if(COMPILER_SUPPORT_OPENMP)
    option(REDWALK_ENABLE_OPENMP "Enable/Disable OpenMP" ON)
    if(REDWALK_ENABLE_OPENMP AND NOT REDWALK_NO_OPENMP)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
      set(REDWALK_OPENMP_STATUS "enabled")
    else()
      set(REDWALK_OPENMP_STATUS "disabled")
    endif()
  endif()
  
  if(cmake_build_type_tolower STREQUAL "release")
    redwalk_add_cxx_compiler_flag("-mtune=native")
  endif()
  
  set(CMAKE_C_FLAGS_DEBUG "-O0 -g0 -Winit-self")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g0 -Winit-self")
  set(CMAKE_C_FLAGS_RELEASE "-O3 -g3")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g3")
endif(NOT MSVC)

################################################################################
# INCLUDE INTERFACE
################################################################################
add_library(libredwalk-interface INTERFACE)
target_include_directories(libredwalk-interface INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/redwalk>
)

subdirs(
  src
)
