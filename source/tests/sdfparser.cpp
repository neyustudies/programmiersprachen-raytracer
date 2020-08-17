#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfparser.hpp"


TEST_CASE("sdf_parser", "[sdf]") {
  GIVEN("a simple scene") {
    auto s = read_from_sdf("../source/tests/simple.sdf");

    REQUIRE(2 == s.materials.size());
    auto mat_red = s.materials.find("red")->second;
    REQUIRE("red" == mat_red.name);
    Color red{1, 0, 0};
    REQUIRE(mat_red.ka == red);
    REQUIRE(mat_red.kd == red);
    REQUIRE(mat_red.ks == red);
    REQUIRE(1 == mat_red.m);
    auto mat_blue = s.materials.find("blue")->second;
    REQUIRE("blue" == mat_blue.name);
    Color blue{0, 0, 1};
    REQUIRE(mat_blue.ka == blue);
    REQUIRE(mat_blue.kd == blue);
    REQUIRE(mat_blue.ks == blue);
    REQUIRE(1 == mat_blue.m);

    REQUIRE(2 == s.shapes.size());

    REQUIRE(1 == s.lights.size());
  }
}
