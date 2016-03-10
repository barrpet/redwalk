project(redwalk CXX)
cmake_minimum_required(VERSION 2.8.5)

# automatically parse the version number
#file(READ "${PROJECT_SOURCE_DIR}/src/redwalk/config/macros.hpp" _redwalk_version_header)
#string(REGEX MATCH "define[ \t]+REDWALK_MAJOR_VERSION[ \t]+([0-9]+)" _redwalk_major_version_match "${_redwalk_version_header}")
#set(REDWALK_MAJOR_VERSION "${CMAKE_MATCH_1}")
#string(REGEX MATCH "define[ \t]+REDWALK_MINOR_VERSION[ \t]+([0-9]+)" _redwalk_minor_version_match "${_redwalk_version_header}")
#set(REDWALK_MINOR_VERSION "${CMAKE_MATCH_1}")
#set(REDWALK_VERSION_NUMBER ${REDWALK_MAJOR_VERSION}.${REDWALK_MINOR_VERSION})


if(NOT DEFINED DOXYGEN_FOUND)
  find_package(Doxygen)
endif()

# add a target to generate API documentation with Doxygen
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif(DOXYGEN_FOUND)
