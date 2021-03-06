#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {

  public:
   Box();
   Box(glm::vec3 const& min, glm::vec3 const& max);
   Box(glm::vec3 const& min, glm::vec3 const& max, std::string const& name);
   Box(glm::vec3 const& min,
       glm::vec3 const& max,
       std::string const& name,
       std::shared_ptr<Material> const& material);
   ~Box();
   glm::vec3 min() const;
   glm::vec3 max() const;
   float area() const override;
   float volume() const override;
   HitPoint intersect(Ray const& ray) const override;
   std::ostream& print(std::ostream& os) const override;

  private:
    glm::vec3 min_;
    glm::vec3 max_;
    HitPoint hitpoint(Ray const& ray) const;

};

#endif // BOX_HPP
