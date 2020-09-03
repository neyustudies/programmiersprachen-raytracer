#include "animation.hpp"

std::string Animation::transformation() {
  ++count_;
  std::string transform = "define transform";
  if(shape_ != nullptr) {
    transform += shape_->name() + " ";
    if(type_ == ROTATE) {
      transform += "rotate " + rotation();
    } else if(type_ == SCALE) {
      transform += "scale " + scaling();
    } else if(type_ == TRANSLATE) {
      transform += "translate " + translation();
    } else {
      std::cerr << "transformation type is not valid";}
  }
}


std::string Animation::rotation() {
  float angle = pace_ * count_;
  std::string rotate = std::to_string(angle) + " ";
  if(axis_ == X) {
    rotate += "1 0 0";
  } else if(axis_ == Y) {
    rotate += "0 1 0";
  } else if(axis_ == Z) {
    rotate += "0 0 1";
  } else if(axis_ == XY) {
    rotate += "1 1 0";
  } else if(axis_ == XZ) {
    rotate += "1 0 1";
  } else if(axis_ == YZ) {
    rotate += "0 1 1";
  } else if(axis_ == XYZ) {
    rotate += "1 1 1";
  } else {
    std::cerr << "rotating error";
  }
  return rotate;
};


std::string Animation::scaling() {
  std::string factor;
  std::string scale;
  /* either shrink or grow a shape */
  if(pace_ < 1.0f) {
    factor = std::to_string(1.0f - ((pace_ * count_) / 10.0f));
  } else {
    factor = std::to_string(1.0f + ((pace_ * count_) / 10.0f));
  }
  if(axis_ == X) {
    scale += factor + " 0 0";
  } else if(axis_ == Y) {
    scale += "0 " + factor + " 0";
  } else if(axis_ == Z) {
    scale += "0 0 " + factor;
  } else if(axis_ == XY) {
    scale += factor + " " + factor + " 0";
  } else if(axis_ == XZ) {
    scale += factor + " 0 " + factor;
  } else if(axis_ == YZ) {
    scale += "0 " + factor + " " + factor;
  } else if(axis_ == XYZ) {
    scale += factor + " " + factor + " " + factor;
  } else {
    std::cerr << "scaling error";
  }
  return scale;
};


std::string Animation::translation() {
  std::string factor;
  std::string translate;
  factor = std::to_string(pace_ * count_);
  if(axis_ == X) {
    translate += factor + " 0 0";
  } else if(axis_ == Y) {
    translate += "0 " + factor + " 0";
  } else if(axis_ == Z) {
    translate += "0 0 " + factor;
  } else if(axis_ == XY) {
    translate += factor + " " + factor + " 0";
  } else if(axis_ == XZ) {
    translate += factor + " 0 " + factor;
  } else if(axis_ == YZ) {
    translate += "0 " + factor + " " + factor;
  } else if(axis_ == XYZ) {
    translate += factor + " " + factor + " " + factor;
  } else {
    std::cerr << "translating error";
  }
  return translate;
};



void Animation::axis(std::string const& axis) {
  if(axis == "X" || axis == "x") {
    axis_ = X;
  } else if(axis == "Y" || axis == "y") {
    axis_ = Y;
  } else if(axis == "Z" || axis == "z") {
    axis_ = Z;
  } else if(axis == "XY" || axis == "xy") {
    axis_ = XY;
  } else if(axis == "XZ" || axis == "xz") {
    axis_ = XZ;
  } else if(axis == "XYZ" || axis == "xyz") {
    axis_ = XYZ;
  } else {
    std::cerr << "axis type is not valid";}
}


void Animation::frames(std::string const& start, std::string const& end) {
  unsigned int frame;
  std::istringstream start_string(start);
  start_string >> frame;
  start_ = frame;
  std::istringstream end_string(end);
  end_ = frame;
}