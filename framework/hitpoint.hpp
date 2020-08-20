#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>

struct HitPoint {

  bool did_intersect = false;
  float t             = 0.0f;
  std::string name    = "";
  Color clr           = {0.0f, 0.0f, 0.0f};
  glm::vec3 point     = {0.0f, 0.0f, 0.0f};
  glm::vec3 direction = {0.0f, 0.0f, 0.0f};

};

#endif // HITPOINT_HPP
