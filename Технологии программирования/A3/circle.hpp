#ifndef circle_hpp
#define circle_hpp

#include "shape.hpp"

namespace potapova
{
  class Circle : public Shape
  {
  public:
    Circle (const point_t& pos, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void show() const override;
    void scale(double factor) override;
    void rotate(double angle) override;

  private:
    point_t pos_;
    double radius_;
  };
}
#endif /* circle_hpp */
