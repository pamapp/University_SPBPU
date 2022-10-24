#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"

namespace potapova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle (const rectangle_t& rectangle);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void show() const override;
    void scale(double factor) override;
    
  private:
    rectangle_t rectangle_;
  };
}

#endif
