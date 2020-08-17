#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfparser.hpp"


TEST_CASE("sdf_parser", "[sdf]") {
  auto s = read_from_sdf("");
  REQUIRE(s.shapes.empty());
  REQUIRE(s.lights.empty());
}
