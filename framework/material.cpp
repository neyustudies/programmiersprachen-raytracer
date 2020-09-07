#include "material.hpp"

Material::Material()
    : name{"Unnamed Material"},
      ka{0.0f, 0.0f, 0.0f},
      kd{0.0f, 0.0f, 0.0f},
      ks{0.0f, 0.0f, 0.0f},
      m{1.0f},
      r{0.f} {}

Material::Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m, float r) :
  name {name},
  ka   {ka},
  ks   {ks},
  kd   {kd},
  m    {m},
  r    {r} {}

bool Material::operator==(Material const& rhs) {
  return (name == rhs.name) && (ka == rhs.ka) && (kd == rhs.kd) &&
         (ks == rhs.ks) && (m == rhs.m) && (r == rhs.r);
}
