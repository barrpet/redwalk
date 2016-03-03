project(redwalk)

subdirs(
  config
  graph
  fastcluster
)

################################################################################
# STATIC LIBRARY
add_library(
  libredwalk-static
  STATIC
  paths.cpp
  dissimilarity.cpp
)

set_target_properties(libredwalk-static PROPERTIES
  OUTPUT_NAME redwalk 
)

target_compile_features(libredwalk-static PUBLIC
  cxx_constexpr
  cxx_nullptr
  cxx_nonstatic_member_init
  cxx_override
  cxx_range_for
)

install(
  TARGETS libredwalk-static
  ARCHIVE DESTINATION lib
)

################################################################################
# SHARED LIBRARY
add_library(libredwalk SHARED
  paths.cpp
  dissimilarity.cpp
)

set_target_properties(libredwalk PROPERTIES
  OUTPUT_NAME redwalk
)

target_compile_features(libredwalk PUBLIC
  cxx_constexpr
  cxx_nullptr
  cxx_nonstatic_member_init
  cxx_override
  cxx_range_for
)

install(
  TARGETS libredwalk
  LIBRARY DESTINATION lib
)

