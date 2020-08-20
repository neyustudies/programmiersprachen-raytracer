#include <iostream>
#include <renderer.hpp>
#include <scene.hpp>
#include <sdfparser.hpp>
#include <window.hpp>

int main(int argc, char *argv[]) {

  if (2 != argc) {
    std::cerr << "RAYTRACER\n"
              << "    Usage: ./raytracer <file.sdf>\n";
  }

  auto scene = read_from_sdf(argv[1]);
  for (auto const& r : scene.renders) {
    std::cerr << "Rendering scene to '" << r.filename << "'...\n";
    Renderer renderer{r.x_res, r.y_res, r.filename};
    renderer.render(scene, r);
  }

  return 0;

  /**
  unsigned const image_width = 800;
  unsigned const image_height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer renderer{image_width, image_height, filename};

  renderer.render();

  Window window{{image_width, image_height}};

  while (!window.should_close()) {
    if (window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      window.close();
    }
    window.show(renderer.color_buffer());
  }

  return 0;
  */
}
