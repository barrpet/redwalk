add_executable(redwalk
  redwalk.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #TODO: fix

set_target_properties(redwalk
  PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )

install(TARGETS redwalk
  RUNTIME DESTINATION bin
)
