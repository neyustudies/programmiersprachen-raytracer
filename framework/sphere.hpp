#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>

class Sphere : public Shape {

  public:
    Sphere();
    Sphere(glm::vec3 const& ctr, float r);
    Sphere(glm::vec3 const& ctr, float r, std::string const& name);
    Sphere(glm::vec3 const& ctr, float r, std::string const& name, std::shared_ptr<Material> const& material);
    ~Sphere();
    glm::vec3 center() const;
    float radius() const;
    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const override;
    std::ostream& print(std::ostream& os) const override;

  private:
    glm::vec3 center_;
    float radius_;


};

#endif // SPHERE_HPP