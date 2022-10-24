#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace potapova;

Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle)
{
  if (rectangle.width <= 0 || rectangle.height <= 0)
  {
    throw std::invalid_argument("Invalid rectangle parameters!");
  }
}

double Rectangle::getArea() const
{
  return (rectangle_.height * rectangle_.width);
}

rectangle_t Rectangle::getFrameRect() const
{
  return {rectangle_.pos, rectangle_.width, rectangle_.height};
}

void Rectangle::move(const point_t& point)
{
  rectangle_.pos = point;
}

void Rectangle::move(double dx, double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void Rectangle::show() const
{
  std::cout << "Central Point: " << "(" << rectangle_.pos.x << ", " << rectangle_.pos.y << ")"
      << '\n' << "Wedth: " << rectangle_.width << '\n'
        << "Height: " << rectangle_.height;
}

void Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale coefficient value!");
  }
  rectangle_.width *= factor;
  rectangle_.height *= factor;
}
