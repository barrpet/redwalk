#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("catch testing framework", "[testing][framework]")
{
  SECTION("require")
  {
    REQUIRE( true );
  }

  SECTION("require false")
  {
    REQUIRE_FALSE( false );
  }
  
  SECTION("c++11")
  {
    int* x = nullptr;
    static constexpr int y = 10;
    REQUIRE( x == nullptr );
    REQUIRE( y == 10 );
  }
}
