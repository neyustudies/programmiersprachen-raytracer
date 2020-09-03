#include "box.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include "hitpoint.hpp"
#include "util.hpp"

Box::Box() :
  Shape {"Unnamed Box"},
  min_  {glm::vec3{}},
  max_  {glm::vec3{}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
  Shape {"Unnamed Box"},
  min_  {min},
  max_  {max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name) :
  Shape {name},
  min_  {min},
  max_  {max} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name, std::shared_ptr<Material> const& material) :
  Shape {name,material},
  min_  {min},
  max_  {max} {}

Box::~Box() {}

glm::vec3 Box::min() const {
  return min_;
}

glm::vec3 Box::max() const {
  return max_;
}

float Box::area() const {
  return 2.0f * std::abs(max_.x - min_.x) +
         2.0f * std::abs(max_.y - min_.y) +
         2.0f * std::abs(max_.z - min_.z);
}

float Box::volume() const {
  return std::abs(max_.x - min_.x) *
         std::abs(max_.y - min_.y) *
         std::abs(max_.z - min_.z);
}

HitPoint Box::hitpoint(Ray const& ray) const {
  std::vector<float> distances;

  float minX = (min_.x - ray.origin.x) / ray.direction.x;
  float maxX = (max_.x - ray.origin.x) / ray.direction.x;
  float minY = (min_.y - ray.origin.y) / ray.direction.y;
  float maxY = (max_.y - ray.origin.y) / ray.direction.y;
  float minZ = (min_.z - ray.origin.z) / ray.direction.z;
  float maxZ = (max_.z - ray.origin.z) / ray.direction.z;

  distances.push_back(minX);
  distances.push_back(maxX);
  distances.push_back(minY);
  distances.push_back(maxY);
  distances.push_back(minZ);
  distances.push_back(maxZ);

  std::sort(distances.begin(), distances.end());
  for (auto d : distances) {
    if (!std::isinf(d)) {
      glm::vec3 hitpoint = ray.origin + (d * ray.direction);
      if (  // intersection!
          in_between_epsilon(min_.x, hitpoint.x, max_.x) &&
          in_between_epsilon(min_.y, hitpoint.y, max_.y) &&
          in_between_epsilon(min_.z, hitpoint.z, max_.z)) {
        glm::vec3 normal{};
        if (maxX == d) normal = {1, 0, 0};
        if (minX == d) normal = {-1, 0, 0};
        if (maxY == d) normal = {0, 1, 0};
        if (minY == d) normal = {0, -1, 0};
        if (maxZ == d) normal = {0, 0, 1};
        if (minZ == d) normal = {0, 0, -1};
        return {true, d, name_, material_->ka, hitpoint, ray.direction, normal};
      }
    }
  }
  return {};
}

HitPoint Box::intersect(Ray const& ray) const {
  material_->ks = Color{};  // XXX TODO remove when specular on boxes is fixed

  if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0)
    throw "direction should not be zero";

  Ray tray = transformRay(world_transform_inv_, ray);

  auto hit = hitpoint(ray);

  transformBack(hit, world_transform_, glm::transpose(world_transform_inv_));
  return hit;
}

std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  return os << "Minimum: (" << min_.x << "," << min_.y << "," << min_.z 
            << ")\nMaximum: (" << max_.x << "," << max_.y << "," << max_.z 
            << ")\nArea:    " << area() << "\nVolume:  " << volume() << "\n";
}