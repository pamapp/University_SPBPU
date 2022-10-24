//
//  matrix.hpp
//  lab3
//
//  Created by Alina Potapova on 23.05.2020.
//  Copyright © 2020 Pamapp. All rights reserved.
//
#include "shape.hpp"
#include <cstdlib>
#include <memory>
#ifndef matrix_hpp
#define matrix_hpp

class Matrix
{
public:
  Matrix();
  Matrix(const Shape *shape);
  Matrix (const Matrix &other);
  ~Matrix();
  void addShape(const Shape *shape);
  void print() const;
private:
  std::unique_ptr<const Shape*[]> matrix_;
  size_t lines_, columns_;
  bool isOverlap(const Shape *shape1, const Shape *shape2) const;
};
#endif
