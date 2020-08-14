#include "material.hpp"

Material::Material() :
  name {"Unnamed Material"},
  ka   {0.0f, 0.0f, 0.0f},
  kd   {0.0f, 0.0f, 0.0f},
  ks   {0.0f, 0.0f, 0.0f},
  m    {1.0f} {}

Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m) :
  name {name},
  ka   {ka},
  ks   {ks},
  kd   {kd},
  m    {m} {}
  