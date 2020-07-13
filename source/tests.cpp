#define CATCH_CONFIG_RUNNER
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp" 


TEST_CASE("default constructor sphere", "[default constructor]") {
  Sphere s1 = Sphere{};
  REQUIRE(s1.center().x == 0.0f);
  REQUIRE(s1.center().y == 0.0f);
  REQUIRE(s1.center().z == 0.0f);
  REQUIRE(s1.radius() == 0.0f);
  REQUIRE(s1.area() == 0.0f);
  REQUIRE(s1.volume() == 0.0f);
  REQUIRE(s1.name() == "Unnamed Sphere");
  REQUIRE(s1.color().r == 0.0f);
  REQUIRE(s1.color().g == 0.0f);
  REQUIRE(s1.color().b == 0.0f);
}

TEST_CASE("default constructor box", "[default constructor]") {
  Box b1 = Box{};
  REQUIRE(b1.max().x == 0.0f);
  REQUIRE(b1.max().y == 0.0f);
  REQUIRE(b1.min().x == 0.0f);
  REQUIRE(b1.min().y == 0.0f);
  REQUIRE(b1.area() == 0.0f);
  REQUIRE(b1.volume() == 0.0f);
  REQUIRE(b1.name() == "Unnamed Box");
  REQUIRE(b1.color().r == 0.0f);
  REQUIRE(b1.color().g == 0.0f);
  REQUIRE(b1.color().b == 0.0f);
}

TEST_CASE("construct a sphere object", "[constructor]" ) {
  Sphere s2{{50, 40, 30}, 5};
  Sphere s3{{1, 2, 3}, 4, "Sphery", {0.3f,1.0f,0.2f}};
  REQUIRE(s2.center().x == 50.0f);
  REQUIRE(s2.center().y == 40.0f);
  REQUIRE(s2.center().z == 30.0f);
  REQUIRE(s2.radius() == 5.0f);
  REQUIRE(s2.area() == Approx(314.16f));
  REQUIRE(s2.volume() == Approx(523.6f));
  REQUIRE(s3.center().x == 1.0f);
  REQUIRE(s3.center().y == 2.0f);
  REQUIRE(s3.center().z == 3.0f);
  REQUIRE(s3.radius() == 4.0f);
  REQUIRE(s3.area() == Approx(201.06f));
  REQUIRE(s3.volume() == Approx(268.08f));
  REQUIRE(s3.name() == "Sphery");
  REQUIRE(s3.color().r == 0.3f);
  REQUIRE(s3.color().g == 1.0f);
  REQUIRE(s3.color().b == 0.2f);
}

TEST_CASE("construct a box object", "[constructor]" ) {
  glm::vec3 small{1, 1, 3};
  glm::vec3 big{300.f, 200.f, 300.f};
  glm::vec3 neg{-8, 100.f, -300.3};
  Box b2{small,small};
  Box b3{small,big};
  Box b4{neg, small, "Boxxy", {0.3f,1.0f,0.2f}};
  REQUIRE(b2.max() == small);
  REQUIRE(b2.min() == small);
  REQUIRE(b2.max().x == 1.0f);
  REQUIRE(b2.max().y == 1.0f);
  REQUIRE(b2.max().z == 3.0f);
  REQUIRE(b3.min().x == 1.0f);
  REQUIRE(b3.min().y == 1.0f);
  REQUIRE(b3.min().z == 3.0f);
  REQUIRE(b3.area() == 1590.0f);
  REQUIRE(b3.volume() == 17671796.0f);
  REQUIRE(b4.max().x == 1.0f);
  REQUIRE(b4.max().y == 1.0f);
  REQUIRE(b4.max().z == 3.0f);
  REQUIRE(b4.area() == Approx(822.6f));
  REQUIRE(b4.volume() == Approx(270240.3f));
  REQUIRE(b4.name() == "Boxxy");
  REQUIRE(b4.color().r == 0.3f);
  REQUIRE(b4.color().g == 1.0f);
  REQUIRE(b4.color().b == 0.2f);
}

TEST_CASE("print a shape", "[print]") {
  Sphere default_sphere{};
  Box default_box{};
  Sphere Sun{{30.f,30.f,30.f}, 10.f, "Sun", {0.2f,1.f,0.f}};
  Box Moon{{1.f,5.f,2.f}, {4.3f, 6.f, 3.3f}, "Moon", {0.1f, 0.5f, 0.8f}};
  default_sphere.print(std::cout);
  default_box.print(std::cout);
  Sun.print(std::cout);
  Moon.print(std::cout);
}

TEST_CASE("intersect_ray_sphere", "[intersect]") {
  // Ray
  glm::vec3 ray_origin{0.0f, 0.0f, 0.0f};
  // ray direction has to be normalized !
  // you can use:
  // v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0.0f, 0.0f, 1.0f};

  // Sphere
  glm::vec3 sphere_center{0.0f ,0.0f, 5.0f};
  float sphere_radius{1.0f};
  float distance = 0.0f;
  auto result = glm::intersectRaySphere(
                ray_origin, ray_direction,
                sphere_center,
                sphere_radius * sphere_radius, // squared radius !!!
                distance);
  REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("interect sphere", "[intersect]") {
  Sphere sphere{{1,2,4},2,"Kugel",{1,0.1f,0.2f}};
  Ray ray{{1,0,2},{0,0,2}};
  HitPoint result = sphere.intersect(ray,4);
  REQUIRE(result.isIntersected);
  REQUIRE(result.t == 2.0f);
  REQUIRE(result.name == "Kugel");
  REQUIRE(result.clr.r == 1.0f);
  REQUIRE(result.clr.g == 0.1f);
  REQUIRE(result.clr.b == 0.2f);
  REQUIRE(result.point.x == 1.0f);
  REQUIRE(result.point.y == 0.0f);
  REQUIRE(result.point.z == 6.0f);
  REQUIRE(result.direction.x == 0.0f);
  REQUIRE(result.direction.y == 0.0f);
  REQUIRE(result.direction.z == 2.0f);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
