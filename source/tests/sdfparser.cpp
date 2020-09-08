#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfparser.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "cone.hpp"
#include "composite.hpp"


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
    REQUIRE(0.f == mat_red.r);
    auto mat_blue = s.materials.find("blue")->second;
    REQUIRE("blue" == mat_blue.name);
    Color blue{0, 0, 1};
    REQUIRE(mat_blue.ka == blue);
    REQUIRE(mat_blue.kd == blue);
    REQUIRE(mat_blue.ks == blue);
    REQUIRE(1 == mat_blue.m);
    REQUIRE(0.42f == Approx(mat_blue.r));

    REQUIRE(5 == s.shapes.size());
    auto box = std::dynamic_pointer_cast<Box>(s.shapes[0]);
    REQUIRE("rbottom" == box->name());
    glm::vec3 min{-100, -80, -200};
    REQUIRE(min == box->min());
    glm::vec3 max{100, 80, -100};
    REQUIRE(max == box->max());
    REQUIRE(mat_red == *(box->material()));
    auto sphere = std::dynamic_pointer_cast<Sphere>(s.shapes[1]);
    REQUIRE("bsphere" == sphere->name());
    glm::vec3 center{0, 0, -100};
    REQUIRE(center == sphere->center());
    REQUIRE(50 == Approx(sphere->radius()));
    REQUIRE(mat_blue == *(sphere->material()));
    auto triangle = std::dynamic_pointer_cast<Triangle>(s.shapes[2]);
    glm::vec3 triangle_a{-1, -1, -1};
    glm::vec3 triangle_b{4, 4, 4};
    glm::vec3 triangle_c{10, 20, -15};
    REQUIRE(mat_blue == *(triangle->material()));
    REQUIRE(triangle_a == triangle->v0());
    REQUIRE(triangle_b == triangle->v1());
    REQUIRE(triangle_c == triangle->v2());
    REQUIRE(0 == triangle->volume());
    REQUIRE(Approx(110.397) == triangle->area());
    auto cone = std::dynamic_pointer_cast<Cone>(s.shapes[3]);
    glm::vec3 base{0, -50, -20};
    REQUIRE(base.x == cone->base().x);
    REQUIRE(base.y == cone->base().y);
    REQUIRE(base.z == cone->base().z);
    float radius = 400.f;
    float height = 600.f;
    REQUIRE(radius == cone->radius());
    REQUIRE(height == cone->height());
    REQUIRE(mat_red == *(cone->material()));
    auto composite = std::dynamic_pointer_cast<Composite>(s.shapes[4]);
    REQUIRE(Approx(3723598.75) == composite->volume());
    REQUIRE(Approx(32446.32) == composite->area());
    REQUIRE("root" == composite->name());
    REQUIRE(!composite->shapes().empty());
    REQUIRE(3 == composite->shapes().size());

    REQUIRE(1 == s.lights.size());
    auto light = s.lights[0];
    REQUIRE("sun" == light.name);
    glm::vec3 pos{1000, 700, 0};
    REQUIRE(pos == light.pos);
    Color color{.2, .2, .2};
    REQUIRE(color == light.color);
    REQUIRE(100.f == Approx(light.brightness));

    REQUIRE(1 == s.cameras.size());
    auto camera = s.cameras.find("eye")->second;
    REQUIRE("eye" == camera.name());
    glm::vec3 camera_pos{0, 0, 0};
    REQUIRE(camera_pos == camera.eye());
    glm::vec3 camera_direction{0, 0, -1};
    REQUIRE(camera_direction == camera.dir());
    glm::vec3 camera_up{0, 5, 0};
    REQUIRE(camera_up == camera.up());
    REQUIRE(45.f == Approx(camera.fov_x()));

    Color ambient{0.1f, 0.f, 0.1f};
    REQUIRE(ambient == s.ambient);

    REQUIRE(1 == s.renders.size());
    auto render = s.renders[0];
    REQUIRE("eye" == render.camera->name());
    REQUIRE("image.ppm" == render.filename);
    REQUIRE(480 == render.x_res);
    REQUIRE(320 == render.y_res);
    REQUIRE(16 == render.subpixels);
  }
}
