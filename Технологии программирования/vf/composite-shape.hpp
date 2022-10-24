#ifndef composite_shape_hpp
#define composite_shape_hpp

#include "shape.hpp"
#include <cstdlib>
#include <memory>

using namespace potapova;

namespace potapova
{
  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape &shape);
    CompositeShape(CompositeShape &&object);
    ~CompositeShape() = default;
    
    CompositeShape& operator=(const CompositeShape &shape);
    std::shared_ptr<Shape> &operator[](size_t index) const;
    
    void addShape(const std::shared_ptr<Shape> &shape);
    void removeShape(size_t index);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &pos) override;
    void scale(double factor) override;
    void show() const override;
    
  private:
    size_t amount_;
    std::unique_ptr<std::shared_ptr<Shape>[]> shapeArray_;
  };
}
#endif /* composite_shape_hpp */
