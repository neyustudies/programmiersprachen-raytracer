#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light {

  Light(std::string const& name, glm::vec3 const& pos, Color const& clr, float brightness) :
    name  (name),
    pos   (pos),
    color (clr),
    brightness (brightness) {}

  std::string name;
  glm::vec3   pos;
  Color       color;
  float       brightness;

};

#endif // LIGHT_HPP
