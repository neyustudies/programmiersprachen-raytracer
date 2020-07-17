#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>

struct HitPoint {

  bool isIntersected  = false;
  float t             = 0.0f;
  std::string name;
  Color clr;
  glm::vec3 point;
  glm::vec3 direction;

};

#endif // HITPOINT_HPP