cmake_minimum_required(VERSION 2.8.5)

if(NOT DEFINED REDWALK_ENABLE_DOCS)
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
else(DOXYGEN_FOUND)
  message(WARNING "Doxygen not found, unable to build documentation")
endif(DOXYGEN_FOUND)
