#include "cone.hpp"

Cone::Cone() :
  Shape   {"Unnamed Cone", nullptr},
  base_   {glm::vec3{}},
  radius_ {0.0f},
  height_ {0.0f} {}

Cone::Cone(glm::vec3 const& base, float r, float h) :
  Shape   {"Unnamed Cone", nullptr},
  base_   {base},
  radius_ {r},
  height_ {h} {}

Cone::Cone(glm::vec3 const& base, float r, float h,
           std::string const& name, std::shared_ptr<Material> const& material) :
  Shape   {name, material},
  base_   {base},
  radius_ {r},
  height_ {h} {}

Cone::~Cone() {}

glm::vec3 Cone::base() const {
  return base_;
}

float Cone::radius() const {
  return radius_;
}

float Cone::height() const {
  return height_;
}

float Cone::area() const {
  float slant_height = powf(radius_, 2.0f) + sqrtf(powf(height_, 2.0f));
  return M_PI * (1.0f / 3.0f) * (slant_height + radius_);
}

float Cone::volume() const {
  return M_PI * (1.0f / 3.0f) * powf(radius_, 2.0f) * height_;
}

HitPoint Cone::intersect(Ray const& ray) const {
  HitPoint hit;
  Ray tray = transformRay(world_transform_inv_, ray);
  tray.direction = glm::normalize(tray.direction);
  glm::vec3 d = glm::vec3(base_.x - tray.origin.x,
                          base_.y - tray.origin.y + height_,
                          base_.z - tray.origin.z);
  
  float a = powf(tray.direction.x, 2.0f) + 
            powf(tray.direction.y, 2.0f) + 
            powf(tray.direction.z, 2.0f);

  float b = d.x * tray.direction.x + 
            d.y * (volume() / height_) * tray.direction.y + 
            d.z * tray.direction.z;

  float c = powf(d.x, 2.0f) + 
            powf(d.y, 2.0f) + 
            powf(d.z, 2.0f);

  /* Todo: find closest point of intersection */

  if(hit.did_intersect) {}

  transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));
  return hit;
}