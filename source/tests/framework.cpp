#define CATCH_CONFIG_RUNNER
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include "material.hpp"


TEST_CASE("default constructor sphere", "[default constructor]") {
  Sphere s1 = Sphere{};
  REQUIRE(s1.center().x == 0.0f);
  REQUIRE(s1.center().y == 0.0f);
  REQUIRE(s1.center().z == 0.0f);
  REQUIRE(s1.radius() == 1.0f);
  REQUIRE(s1.area() == Approx(12.5664f));
  REQUIRE(s1.volume() == Approx(4.1888f));
  REQUIRE(s1.name() == "Unnamed Sphere");
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
}

TEST_CASE("construct a sphere object", "[constructor]" ) {
  Sphere s2{{50, 40, 30}, 5};
  Sphere s3{{1, 2, 3}, 4, "Sphery"};
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
}

TEST_CASE("construct a box object", "[constructor]" ) {
  glm::vec3 small{1, 1, 3};
  glm::vec3 big{300.f, 200.f, 300.f};
  glm::vec3 neg{-8, 100.f, -300.3};
  Box b2{small,small};
  Box b3{small,big};
  Box b4{neg, small, "Boxxy"};
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
  REQUIRE(b4.max().y == 100.f);
  REQUIRE(b4.max().z == 3.0f);
  REQUIRE(b4.area() == Approx(822.6f));
  REQUIRE(b4.volume() == Approx(270240.3f));
  REQUIRE(b4.name() == "Boxxy");
}

TEST_CASE("print a shape", "[print]") {
  Sphere default_sphere{};
  Box default_box{};
  Sphere Sun{{30.f,30.f,30.f}, 10.f, "Sun"};
  Box Moon{{1.f,5.f,2.f}, {4.3f, 6.f, 3.3f}, "Moon"};
  /* default_sphere.print(std::cout);
  default_box.print(std::cout);
  Sun.print(std::cout);
  Moon.print(std::cout); */
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

TEST_CASE("intersect sphere", "[intersect]") {
  auto m1 = std::make_shared<Material>("Test", Color{0.2f, 0.3f, 0.8f}, 
                                               Color{0.1f, 0.4f, 0.9f}, 
                                               Color{0.0f, 0.5f, 0.6f},
                                               10.0f, 42.f, 1.f, 1.f);
  SECTION("intersected sphere") {
    Sphere sphere{{0,0,5},1,"Kugel", m1};
    Ray ray{{0,0,0},{0,0,1}};
    HitPoint result = sphere.intersect(ray);
    REQUIRE(result.did_intersect);
    REQUIRE(result.t == Approx(4.0f));
    REQUIRE(result.name == "Kugel");
    REQUIRE(result.point.x == 0.0f);
    REQUIRE(result.point.y == 0.0f);
    REQUIRE(result.point.z == 4.0f);
    REQUIRE(result.direction.x == 0.0f);
    REQUIRE(result.direction.y == 0.0f);
    REQUIRE(result.direction.z == 1.0f);
  }
  SECTION("intersected sphere 2") {
    Sphere noname{{1,2,4},2, "Sphere", m1};
    Ray ray{{1,0,2},{0,0,2}};
    HitPoint hit = noname.intersect(ray);
    REQUIRE(hit.did_intersect);
    REQUIRE(hit.t == 2.0f);
    REQUIRE(hit.name == "Sphere");
    REQUIRE(hit.point.x == 1.0f);
    REQUIRE(hit.point.y == 0.0f);
    REQUIRE(hit.point.z == 4.0f);
    REQUIRE(hit.direction.x == 0.0f);
    REQUIRE(hit.direction.y == 0.0f);
    //REQUIRE(hit.direction.z == 2.0f);
  }
  SECTION("sphere that is not hit") {
    Sphere sphere{{1,2,4},2,"Kugel", m1};
    Ray ray{{1,8,2},{0,0,2}};
    HitPoint nohit = sphere.intersect(ray);
    REQUIRE_FALSE(nohit.did_intersect);
  }
}

TEST_CASE("intersect sphere2", "[intersect]") {
  auto m1 = std::make_shared<Material>("Test", Color{0.2f, 0.3f, 0.8f}, 
                                               Color{0.1f, 0.4f, 0.9f}, 
                                               Color{0.0f, 0.5f, 0.6f},
                                               10.0f, 42.f, 1.f, 1.f);
  Sphere s1{glm::vec3{1, 1, 1}, 2.0f, "h", m1};
  Ray ray{{1, 1, 1}, {-1, -1, -1}};
  HitPoint hit = s1.intersect(ray);
  REQUIRE(hit.did_intersect);
}

TEST_CASE("example code, dynamic vs static", "[task 5.7]") {
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>(position, 1.2f, "sphere0");
  std::shared_ptr<Shape> s2 = std::make_shared<Sphere>(position, 1.2f, "sphere1");
  //s1->print(std::cout); 
  //s2->print(std::cout);
}

TEST_CASE("example code, destructor", "[task 5.8]") {
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  Sphere* s1 = new Sphere{position, 1.2f,  "sphere0"}; 
  Shape* s2 = new Sphere{position, 1.2f, "sphere1"};
  //s1->print(std::cout); 
  //s2->print(std::cout);
  delete s1; 
  delete s2;
}

TEST_CASE("material constructor", "[material]") {
  SECTION("default material") {
    Material m1{};
    REQUIRE(m1.name.compare("Unnamed Material") == 0);
    REQUIRE(m1.ka.r == 0.0f);
    REQUIRE(m1.ka.g == 0.0f);
    REQUIRE(m1.ka.b == 0.0f);
    REQUIRE(m1.kd.r == 0.0f);
    REQUIRE(m1.kd.g == 0.0f);
    REQUIRE(m1.kd.b == 0.0f);
    REQUIRE(m1.ks.r == 0.0f);
    REQUIRE(m1.ks.g == 0.0f);
    REQUIRE(m1.ks.b == 0.0f);
    REQUIRE(m1.m    == 1.0f);
    REQUIRE(m1.r    == 0.0f);
    REQUIRE(m1.opacity == 1.0f);
    REQUIRE(m1.n    == 1.5f);
  }
  SECTION("material with given values") {
    Material m2{"Test", {0.7f, 0.1f, 0.2f}, {1.0f, 0.9f, 1.1f}, {0.0f, 0.1f, 0.2f}, 10.0f, 42.f, 0.6f, 1.4f};
    REQUIRE(m2.name.compare("Test") == 0);
    REQUIRE(m2.ka.r == 0.7f);
    REQUIRE(m2.ka.g == 0.1f);
    REQUIRE(m2.ka.b == 0.2f);
    REQUIRE(m2.kd.r == 1.0f);
    REQUIRE(m2.kd.g == 0.9f);
    REQUIRE(m2.kd.b == 1.1f);
    REQUIRE(m2.ks.r == 0.0f);
    REQUIRE(m2.ks.g == 0.1f);
    REQUIRE(m2.ks.b == 0.2f);
    REQUIRE(m2.m    == 10.0f);
    REQUIRE(m2.r    == 42.0f);
    REQUIRE(m2.opacity == .6f);
    REQUIRE(m2.n    == 1.4f);
  }
}

 TEST_CASE("shapes with material", "[shapes]") {
  auto m1 = std::make_shared<Material>("Test", Color{0.2f, 0.3f, 0.8f}, 
                                               Color{0.1f, 0.4f, 0.9f}, 
                                               Color{0.0f, 0.5f, 0.6f},
                                               10.0f, 42.f, 1.f, 1.f);
  SECTION("box constructor with material") {
    Box b1{};
    REQUIRE(b1.material() == nullptr);
    Box b2{{}, {}, "Box", m1};
    REQUIRE(b2.name().compare("Box") == 0);
    REQUIRE(b2.material()->ka.r == 0.2f);
    REQUIRE(b2.material()->ka.g == 0.3f);
    REQUIRE(b2.material()->ka.b == 0.8f);
    REQUIRE(b2.material()->kd.r == 0.1f);
    REQUIRE(b2.material()->kd.g == 0.4f);
    REQUIRE(b2.material()->kd.b == 0.9f);
    REQUIRE(b2.material()->ks.r == 0.0f);
    REQUIRE(b2.material()->ks.g == 0.5f);
    REQUIRE(b2.material()->ks.b == 0.6f);
    REQUIRE(b2.material()->m    == 10.0f);
    REQUIRE(b2.material()->name.compare("Test") == 0);
  }
  SECTION("sphere constructor with material") {
    Sphere s1{};
    REQUIRE(s1.material() == nullptr);
    Sphere s2{{}, {}, "Kugel", m1};
    REQUIRE(s2.name().compare("Kugel") == 0);
    REQUIRE(s2.material()->ka.r == 0.2f);
    REQUIRE(s2.material()->ka.g == 0.3f);
    REQUIRE(s2.material()->ka.b == 0.8f);
    REQUIRE(s2.material()->kd.r == 0.1f);
    REQUIRE(s2.material()->kd.g == 0.4f);
    REQUIRE(s2.material()->kd.b == 0.9f);
    REQUIRE(s2.material()->ks.r == 0.0f);
    REQUIRE(s2.material()->ks.g == 0.5f);
    REQUIRE(s2.material()->ks.b == 0.6f);
    REQUIRE(s2.material()->m    == 10.0f);
    REQUIRE(s2.material()->name.compare("Test") == 0);
  }
}

TEST_CASE("intersect Box", "[intersect]") {
  /*
  auto m1 = std::make_shared<Material>("Test", Color{0.2f, 0.3f, 0.8f}, 
                                               Color{0.1f, 0.4f, 0.9f}, 
                                               Color{0.0f, 0.5f, 0.6f},
                                               10.0f, 42.f, 1.f, 1.f);
  Box b1{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, "Box", m1};
  // testing ray inside
  HitPoint h1 = b1.intersect(Ray{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}});
  REQUIRE(h1.did_intersect);
  REQUIRE(h1.t == -1.0f);

  // testing sides
  HitPoint h2 = b1.intersect(Ray{{2.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}});
  HitPoint h3 = b1.intersect(Ray{{-2.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
  HitPoint h4 = b1.intersect(Ray{{0.0f, 2.0f, 0.0f}, {0.0f, -1.0f, 0.0f}});
  HitPoint h5 = b1.intersect(Ray{{0.0f, -2.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
  HitPoint h6 = b1.intersect(Ray{{0.0f, 0.0f, 2.0f}, {0.0f, 0.0f, -1.0f}});
  HitPoint h7 = b1.intersect(Ray{{0.0f, 0.0f, -2.0f}, {0.0f, 0.0f, 1.0f}}); 
  REQUIRE(h2.did_intersect); 
  REQUIRE(h3.did_intersect);
  REQUIRE(h3.t == 1.0f);
  REQUIRE(h4.did_intersect);
  REQUIRE(h5.did_intersect);
  REQUIRE(h5.t == 1.0f);
  REQUIRE(h6.did_intersect);
  REQUIRE(h7.did_intersect);
  REQUIRE(h7.t == 1.0f);

  // testing parallel ray, intersection should be false
  HitPoint h8 = b1.intersect(Ray{{2.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}});
  HitPoint h9 = b1.intersect(Ray{{2.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
  HitPoint h10 = b1.intersect(Ray{{0.0f, 2.0f, 0.0f}, {1.0f, 0.0f, 0.0f}});
  HitPoint h11 = b1.intersect(Ray{{0.0f, 2.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});
  HitPoint h12 = b1.intersect(Ray{{0.0f, 0.0f, 2.0f}, {0.0f, 1.0f, 0.0f}});
  HitPoint h13 = b1.intersect(Ray{{0.0f, 0.0f, 2.0f}, {1.0f, 0.0f, 0.0f}});
  REQUIRE(!h8.did_intersect);
  REQUIRE(!h9.did_intersect);
  REQUIRE(!h10.did_intersect);
  REQUIRE(!h11.did_intersect);
  REQUIRE(!h12.did_intersect);
  REQUIRE(!h13.did_intersect);
  */
}
