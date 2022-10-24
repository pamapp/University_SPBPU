#ifndef rectangle_hpp
#define rectangle_hpp

#include "shape.hpp"

namespace potapova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t& rectangle);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void show() const override;
    void scale(double factor) override;
    void rotate(double angle) override;
    point_t getTop(const int index) const;
  private:
    rectangle_t rectangle_;
    point_t top_[3];
  };
}

#endif
