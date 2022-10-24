#include "matrix.hpp"
#include <iostream>
#include <cmath>

Matrix::Matrix() :
  matrix_(nullptr),
  columns_(0),
  lines_(0)
{
}

Matrix::Matrix(const Shape *shape) :
  matrix_(new const Shape*[1]),
  lines_(1),
  columns_(1)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Object doesn't exist!");
  }
  matrix_[0] = shape;
}

Matrix::Matrix(const Matrix &other) :
  matrix_(new const Shape*[other.lines_ * other.columns_]),
  lines_(other.lines_),
  columns_(other.columns_)
{
  for (int i = 0; i < (lines_ * columns_); i++)
  {
    matrix_[i] = other.matrix_[i];
  }
}


void Matrix::addShape(const Shape *shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Object doesn't exist!");
  }
  for (int i = 0; i < (lines_ * columns_); i++)
  {
    if (matrix_[i] == shape)
    {
      throw std::invalid_argument("Matrix already contain this shape!");
    }
  }
  size_t i = lines_;
  size_t j = columns_ - 1;
  while ((i != 0) && (!isOverlap(matrix_[(i - 1) * columns_ + j], shape)))
  {
    while (j != 0)
    {
      j--;
    }
    i--;
  }
  if (j == lines_)
  {
    lines_++;
    std::unique_ptr <const Shape*[]> new_matrix(new const Shape*[columns_ * lines_]);
    j = 0;
    while (j < (lines_- 1) * columns_)
    {
      new_matrix[j] = matrix_[j];
      j++;
    }
    new_matrix[j++] = shape;
    while (j < columns_ * lines_)
    {
      new_matrix[j++]=nullptr;
    }
    matrix_.swap(new_matrix);
  }
  else
  {
    j = 0;
    while ((j < columns_) && (matrix_[i * columns_ + j] != nullptr))
    {
      j++;
    }
    if (j == columns_)
    {
      ++columns_;
      std::unique_ptr <const Shape*[]> new_matrix(new const Shape*[columns_ * lines_]);
      j = 0;
      size_t iter = 0;
      while(j < columns_ * lines_)
      {
        if((j + 1) % columns_ == 0)
        {
          if((i + 1) == ((j + 1) / columns_))
          {
            new_matrix[j] = shape;
          }
          else
          {
            new_matrix[j] = nullptr;
          }
        }
        else
        {
          new_matrix[j] = matrix_[iter++];
        }
        j++;
      }
      matrix_.swap(new_matrix);
    }
    else
    {
      matrix_[i * columns_ + j] = shape;
    }
  }
}

void Matrix::print() const
{
  std::cout << "Lines: " << lines_ << "\nColumns: " << columns_ << '\n';

  for (size_t j = 0; j < lines_; j++)
  {
    std::cout << "\nLayer " << ( j + 1) <<":\n-----------\n";
    for (size_t i = 0; i < columns_; i++)
    {
      if (matrix_[j * columns_ + i] != nullptr)
      {
        std::cout << "\nShape " << ( i + 1 ) << ":\n";
        matrix_[j * columns_ + i]->show();
        std::cout << '\n';
      }
    }
  }
}

bool Matrix::isOverlap(const Shape *shape1, const Shape *shape2) const
{
  if (shape1 == nullptr || shape2 == nullptr)
  {
    return false;
  }
  return ((fabs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x)
        < ((shape1->getFrameRect().width / 2) + (shape2->getFrameRect().width / 2)))
      && ((fabs(shape1->getFrameRect().pos.y - shape2->getFrameRect().pos.y)
        < ((shape1->getFrameRect().height / 2) + (shape2->getFrameRect().height / 2)))));
}
