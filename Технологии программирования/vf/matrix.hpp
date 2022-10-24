#include "shape.hpp"
#include <cstdlib>
#include <memory>
#ifndef matrix_hpp
#define matrix_hpp

using namespace potapova;
class Matrix
{
public:
  Matrix();
  Matrix(const Shape *shape);
  Matrix (const Matrix &other);
  ~Matrix() = default;
  void addShape(const Shape *shape);
  void print() const;
private:
  std::unique_ptr<const Shape*[]> matrix_;
  size_t lines_, columns_;
  bool isOverlap(const Shape *shape1, const Shape *shape2) const;
};
#endif

