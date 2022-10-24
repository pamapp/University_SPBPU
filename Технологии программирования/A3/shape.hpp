#ifndef shape_h
#define shape_h
#include "base-types.hpp"
namespace potapova
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void show() const = 0;
    virtual void scale(double factor) = 0;
    virtual void rotate(double angle) = 0;
  };
}
#endif /* shape_h */
