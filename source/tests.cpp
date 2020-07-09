#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp" 


TEST_CASE("default constructor sphere", "[default constructor]") {
  Sphere s1 = Sphere{};

  REQUIRE(s1.center().x == 0.0f);
  REQUIRE(s1.center().y == 0.0f);
  REQUIRE(s1.center().z == 0.0f);
  REQUIRE(s1.radius()   == 0.0f);
  REQUIRE(s1.area()     == 0.0f);
  REQUIRE(s1.volume()   == 0.0f);
}

TEST_CASE("default constructor box", "[default constructor]") {
  Box b1 = Box{};

  REQUIRE(b1.max().x  == 0.0f);
  REQUIRE(b1.max().y  == 0.0f);
  REQUIRE(b1.min().x  == 0.0f);
  REQUIRE(b1.min().y  == 0.0f);
  REQUIRE(b1.area()   == 0.0f);
  REQUIRE(b1.volume() == 0.0f);
}

TEST_CASE("construct a sphere object", "[constructor]" ) {
  Sphere s2{{50, 40, 30}, 5};
  Sphere s3{{1, 2, 3}, 4};

  REQUIRE(s2.center().x == 50.0f);
  REQUIRE(s2.center().y == 40.0f);
  REQUIRE(s2.center().z == 30.0f);
  REQUIRE(s2.radius()   == 5.0f);
  REQUIRE(s2.area()     == Approx(314.16f));
  REQUIRE(s2.volume()   == Approx(523.6f));
  REQUIRE(s3.center().x == 1.0f);
  REQUIRE(s3.center().y == 2.0f);
  REQUIRE(s3.center().z == 3.0f);
  REQUIRE(s3.radius()   == 4.0f);
  REQUIRE(s3.area()     == Approx(201.06f));
  REQUIRE(s3.volume()   == Approx(268.08f));
}

TEST_CASE("construct a box object", "[constructor]" ) {
  glm::vec3 small{1, 1, 3};
  glm::vec3 big{300.f, 200.f, 300.f};
  glm::vec3 neg{-8, 100.f, -300.3};
  Box b2{small,small};
  Box b3{small,big};
  Box b4{neg, small};

  REQUIRE(b2.max()    == small);
  REQUIRE(b2.min()    == small);
  REQUIRE(b2.max().x  == 1.0f);
  REQUIRE(b2.max().y  == 1.0f);
  REQUIRE(b2.max().z  == 3.0f);
  REQUIRE(b3.min().x  == 1.0f);
  REQUIRE(b3.min().y  == 1.0f);
  REQUIRE(b3.min().z  == 3.0f);
  REQUIRE(b3.area()   == 1590.0f);
  REQUIRE(b3.volume() == 17671796.0f);
  REQUIRE(b4.max().x  == 1.0f);
  REQUIRE(b4.max().y  == 1.0f);
  REQUIRE(b4.max().z  == 3.0f);
  REQUIRE(b4.area()   == Approx(822.6f));
  REQUIRE(b4.volume() == Approx(270240.3f));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
