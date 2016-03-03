project(redwalk)

################################################################################
# STATIC LIBRARY
add_library(
  libfastcluster-static
  STATIC
  fastcluster.cpp
)

set_target_properties(libfastcluster-static PROPERTIES
  OUTPUT_NAME fastcluster
)

install(
  TARGETS libfastcluster-static
  ARCHIVE
  DESTINATION lib
)
