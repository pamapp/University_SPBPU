#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace potapova;

Circle::Circle(const point_t& pos, double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid circle parameter!");
  }
}
double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t& point)
{
  pos_ = point;
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::show() const
{
  std::cout << "Central Point: " << "(" << pos_.x << ", " << pos_.y << ")"
      << '\n' << "Radius: " << radius_;
}

void Circle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale coefficient value!");
  }
  radius_ *= factor;
}

void Circle::rotate(double angle)
{
}
