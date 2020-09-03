#ifndef ANIMATION_HPP
#define ANIMATION_HPP
#include "shape.hpp"
#include <memory>
#include <string>
#include <iostream>
#include <sstream>

class Animation {

  public:
    /* set axis for animation */
    void axis(std::string const& axis);
    /* set start and end of animated scene */
    void frames(std::string const& start, std::string const& end);
    /* return transformation for next frame */
    std::string transformation();  

  protected:
    std::string scaling();
    std::string rotation();
    std::string translation();

  private:
    Axis axis_;
    Transformation type_;
    std::shared_ptr<Shape> shape_;
    unsigned int count_ = 0;
    unsigned int pace_  = 0;
    unsigned int start_ = 0;
    unsigned int end_   = 0;
    
};

enum Transformation {ROTATE, SCALE, TRANSLATE};
enum Axis {X, Y, Z, XY, XZ, YZ, XYZ};

#endif //ANIMATION_HPP