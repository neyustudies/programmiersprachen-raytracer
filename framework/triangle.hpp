#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle : public Shape {

  public:
    Triangle();
    Triangle(glm::vec3 const& v0, glm::vec3 const& v1, glm::vec3 const& v2);
    Triangle(glm::vec3 const& v0, glm::vec3 const& v1, glm::vec3 const& v2, 
             std::string const& name, std::shared_ptr<Material> const& material);
    ~Triangle();

    glm::vec3 v0() const;
    glm::vec3 v1() const;
    glm::vec3 v2() const;

    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const override;

   private:
    glm::vec3 v0_;
    glm::vec3 v1_;
    glm::vec3 v2_;

};

#endif // TRIANGLE_HPP