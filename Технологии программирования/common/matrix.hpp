#ifndef matrix_hpp
#define matrix_hpp

#include <cstdlib>
#include <memory>
#include "shape.hpp"

using namespace potapova;

class Matrix
{
public:
  Matrix();
  Matrix(const Shape *shape);
  Matrix(const Matrix &other);
  ~Matrix() = default;
  Matrix& operator= (const Matrix& matrix);
  Matrix& operator= (Matrix&& matrix);
  const Shape** operator [](const size_t &index) const;
  void addShape(const Shape *shape);
  void show() const;
private:
  std::unique_ptr<const Shape*[]> matrix_;
  size_t lines_;
  size_t columns_;
  bool isOverlap(const Shape *shape1, const Shape *shape2) const noexcept;
};

#endif /* matrix_hpp */
