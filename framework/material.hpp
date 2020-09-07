#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"

struct Material {

  Material();
  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m, float r);

  std::string name;
  Color ka;         // Reflection factor for ambient light
  Color kd;         // Reflection factor for diffuse light
  Color ks;         // Reflection factor for specular light
  float m;          // Exponent for describing the surface properties
  float r;          // Reflectiveness, ranging from 0-1 where 1 is a mirror

  bool operator==(Material const& rhs);
};


#endif // MATERIAL_HPP
