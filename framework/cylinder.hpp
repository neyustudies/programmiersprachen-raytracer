#ifndef CYLINDER_HPP
#define CYLINDER_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <vector>
#include <math.h>

class Cylinder : public Shape {

  public:
    Cylinder();
    Cylinder(glm::vec3 const& point_1, glm::vec3 const& point_2, float r);
    Cylinder(glm::vec3 const& point_1, glm::vec3 const& point_2, float r, std::string const& name, std::shared_ptr<Material> const& material);
    ~Cylinder();
    float height() const;
    float volume() const override;
    float area() const override;
    HitPoint intersect(Ray const& ray) const override;

  private:
    glm::vec3 point_1_;
    glm::vec3 point_2_;
    float radius_;
};

#endif // CYLINDER_HPP