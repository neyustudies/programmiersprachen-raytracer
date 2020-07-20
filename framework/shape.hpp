#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "color.hpp"
#include <string>

class Shape {

  public:
    Shape();
    Shape(std::string const& name);
    Shape(std::string const& name, Color const& clr);
    virtual ~Shape();
    std::string name() const;
    Color color() const;
    virtual std::ostream& print(std::ostream& os) const;
    virtual float area() const = 0;
    virtual float volume() const = 0;

  protected:
    std::string name_;
    Color color_;

};

#endif // SHAPE_HPP