project(redwalk)

subdirs(
  redwalk
)

include_directories(redwalk)

add_executable(redwalk-bin
  redwalk.cpp
)

set_target_properties(redwalk-bin PROPERTIES
  OUTPUT_NAME redwalk-bin
)

target_compile_features(redwalk-bin PUBLIC
  cxx_constexpr
  cxx_nullptr
  cxx_nonstatic_member_init
  cxx_override
  cxx_range_for
)

install(
  TARGETS redwalk-bin
  RENAME redwalk
  RUNTIME DESTINATION bin
)
