install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
  DESTINATION include/redwalk
  FILES_MATCHING
    PATTERN "redwalk"
    PATTERN "*.hpp"
    PATTERN "*.h"
    PATTERN "*.txt" EXCLUDE
    PATTERN ".git" EXCLUDE
)
