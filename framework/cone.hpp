#ifndef CONE_HPP
#define CONE_HPP
#include "shape.hpp"

class Cone : public Shape {

  public:
    Cone();
    Cone(glm::vec3 const& base, float r, float h);
    Cone(glm::vec3 const& base, float r, float h, 
         std::string const& name, std::shared_ptr<Material> const& material);
    ~Cone();

    glm::vec3 base() const;
    float radius() const;
    float height() const;

    float area() const override;
    float volume() const override;
    HitPoint intersect(Ray const& ray) const override;

  private:
    glm::vec3 base_;
    float radius_;
    float height_;

};

#endif // CONE_HPP
