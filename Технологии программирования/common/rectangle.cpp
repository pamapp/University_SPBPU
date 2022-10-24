#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

using namespace potapova;

Rectangle::Rectangle(const rectangle_t& rectangle) :
  rectangle_(rectangle),
  top_ { {rectangle.pos.x - rectangle.width / 2, rectangle.pos.y + rectangle.height / 2},
      {rectangle.pos.x + rectangle.width / 2, rectangle.pos.y + rectangle.height / 2},
      {rectangle.pos.x + rectangle.width / 2, rectangle.pos.y - rectangle.height / 2} }
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
  move(point.x - rectangle_.pos.x, point.y - rectangle_.pos.y);
}

void Rectangle::move(double dx, double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
  for (int i = 0; i < 3; i++)
  {
    top_[i].x += dx;
    top_[i].y += dy;
  }
}

void Rectangle::show() const
{
  std::cout << "Central Point: " << "(" << rectangle_.pos.x << ", " << rectangle_.pos.y << ")"
      << "\nWedth: " << rectangle_.width << "\nHeight: " << rectangle_.height << "\nTops: ";
  for (int i = 0; i < 3; i++)
  {
    std::cout << "(" << top_[i].x << ", " << top_[i].y << ") ";
  }
}

void Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale coefficient value!");
  }
  for (int i = 0; i < 3; i++)
  {
    top_[i] = { rectangle_.pos.x + (top_[i].x - rectangle_.pos.x)
        * factor, rectangle_.pos.y + (top_[i].y - rectangle_.pos.y) * factor };
  }
  rectangle_.width *= factor;
  rectangle_.height *= factor;
}

void Rectangle::rotate(double angle)
{
  angle = angle * M_PI / 180;
  double angleCos = cos(angle);
  double angleSin = sin(angle);
  point_t recPos = getFrameRect().pos;
  for (int i = 0; i < 3; i++)
  {
    top_[i] = { recPos.x + (top_[i].x - recPos.x) * angleCos - (top_[i].y - recPos.y)
        * angleSin, recPos.y + (top_[i].y - recPos.y)
        * angleCos + (top_[i].x - recPos.x) * angleSin };
  }
}
