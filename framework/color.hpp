// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(float f, Color const& a) {
    auto tmp{a};
    tmp.r = f * a.r;
    tmp.g = f * a.g;
    tmp.b = f * a.b;
    return tmp;
  }

  friend Color operator*(Color const& a, float f) {
    return f * a;
  }

  friend Color operator*(Color const& a, Color const& b) {
    auto tmp{a};
    tmp.r = a.r * b.r;
    tmp.g = a.g * b.g;
    tmp.b = a.b * b.b;
    return tmp;
  }

  friend bool operator==(Color const &a, Color const &b) {
    return (a.r == b.r) && (a.g == b.g) && (a.b == b.b);
  }


  float r;
  float g;
  float b;
};

#endif //#define BUW_COLOR_HPP
