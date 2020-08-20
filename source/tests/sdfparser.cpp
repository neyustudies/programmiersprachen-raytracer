#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfparser.hpp"
#include "box.hpp"
#include "sphere.hpp"


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
    glm::vec3 camera_up{0, 1, 0};
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
  }
}
