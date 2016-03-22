add_library(fastcluster STATIC
  fastcluster.cpp
)

set_target_properties(fastcluster
  PROPERTIES
    EXCLUDE_FROM_DEFAULT_BUILD TRUE
    EXCLUDE_FROM_ALL TRUE
)
