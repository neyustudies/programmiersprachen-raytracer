#include "box.hpp"
#include "hitpoint.hpp"
#include <cmath>
#include <vector>
#include <algorithm>

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

bool Box::did_intersect(Ray const& ray, float t) const {
  bool result = false;
  glm::vec3 hitpoint;
  if(ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0) {
    throw "direction should not be zero";
  } else {
    std::vector<float> distance;

    float minX = (min_.x - ray.origin.x) / ray.direction.x;
    float maxX = (max_.x - ray.origin.x) / ray.direction.x;
    float minY = (min_.y - ray.origin.y) / ray.direction.y;
    float maxY = (max_.y - ray.origin.y) / ray.direction.y;
    float minZ = (min_.z - ray.origin.z) / ray.direction.z;
    float maxZ = (max_.z - ray.origin.z) / ray.direction.z;

    distance.push_back(minX);
    distance.push_back(maxX);
    distance.push_back(minY);
    distance.push_back(maxY);
    distance.push_back(minZ);
    distance.push_back(maxZ);

    std::sort(distance.begin(), distance.end());
    for(auto i : distance) {
      if(!std::isinf(i)) {
        hitpoint = ray.origin + (i * ray.direction);
        if((hitpoint.x <=max_.x && hitpoint.x >= min_.x) &&
           (hitpoint.y <=max_.y && hitpoint.y >= min_.y) &&
           (hitpoint.z <=max_.z && hitpoint.z >= min_.z)) {
             t = i;
             result = true;
           }
      }
    }
  } return result;
}

HitPoint Box::intersect(Ray const& ray, float t) const {
  glm::vec3 hitpoint;
  glm::vec3 vec = hitpoint - ray.origin;
  float d = std::sqrt(std::pow(vec.x, 2) +
                      std::pow(vec.y, 2) +
                      std::pow(vec.z, 2));
  return HitPoint{
      did_intersect(ray, t),
      d,
      name_,
      material_->ka,
      hitpoint,
      ray.direction
  };
}


std::ostream& Box::print(std::ostream& os) const {
  Shape::print(os);
  return os << "Minimum: (" << min_.x << "," << min_.y << "," << min_.z 
            << ")\nMaximum: (" << max_.x << "," << max_.y << "," << max_.z 
            << ")\nArea:    " << area() << "\nVolume:  " << volume() << "\n";
}