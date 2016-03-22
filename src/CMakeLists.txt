include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include/src")

set(LIBREDWALK_SOURCES
  paths.cpp
  dissimilarity.cpp
)

add_subdirectory(fastcluster)

################################################################################
# OBJECT LIBRARY
add_library(libredwalk-static STATIC
  ${LIBREDWALK_SOURCES}
)

target_compile_features(libredwalk-static PUBLIC
  cxx_constexpr
  cxx_nullptr
  cxx_nonstatic_member_init
  cxx_override
  cxx_range_for
)

set_target_properties(libredwalk-static
  PROPERTIES
    OUTPUT_NAME redwalk
)

target_link_libraries(libredwalk-static libredwalk-interface)
target_link_libraries(libredwalk-static fastcluster)

################################################################################
# SHARED LIBRARY
add_library(libredwalk-shared SHARED
  ${LIBREDWALK_SOURCES}
)

target_compile_features(libredwalk-shared PUBLIC
  cxx_constexpr
  cxx_nullptr
  cxx_nonstatic_member_init
  cxx_override
  cxx_range_for
)

set_target_properties(libredwalk-shared
  PROPERTIES
    OUTPUT_NAME redwalk
)

target_link_libraries(libredwalk-shared libredwalk-interface)
target_link_libraries(libredwalk-shared fastcluster)
