#ifndef CYLINDER_HPP
#define CYLINDER_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include <vector>
#include <math.h>

class Cylinder : public Shape {

  public:
    Cylinder();
    Cylinder(glm::vec3 const& v0, float r, float h);
    Cylinder(glm::vec3 const& v0, float r, float h, std::string const& name, 
             std::shared_ptr<Material> const& material);
    ~Cylinder();
    float height() const;
    float radius() const;
    float volume() const override;
    float area() const override;
    HitPoint intersect(Ray const& ray) const override;

  private:
    glm::vec3 v0_;
    float radius_;
    float height_;
};

#endif // CYLINDER_HPP