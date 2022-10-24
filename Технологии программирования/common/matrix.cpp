#include "matrix.hpp"
#include <cmath>
#include <stdexcept>
#include <iostream>

Matrix::Matrix() :
  matrix_(nullptr),
  lines_(0),
  columns_(0)
{
}

Matrix::Matrix(const Shape *shape) :
  matrix_(new const Shape*[1]),
  lines_(1),
  columns_(1)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("No object to add!");
  }
  matrix_[0] = shape;
}

Matrix::Matrix(const Matrix& other) :
  matrix_(new const Shape*[other.columns_ * other.lines_]),
  lines_(other.lines_),
  columns_(other.columns_)
{
  for (size_t i = 0; i < (other.lines_ * other.columns_); i++)
  {
    matrix_[i] = other.matrix_[i];
  }
}

Matrix& Matrix::operator= (const Matrix& matrix)
{
  if (this != &matrix)
  {
    std::unique_ptr <const Shape*[]> temp_matrix(new const Shape*[matrix.columns_ * matrix.lines_]);
    for (size_t i = 0; i < (matrix.columns_ * matrix.lines_); i++)
    {
      temp_matrix[i] = matrix.matrix_[i];
    }
    matrix_.swap(temp_matrix);
    lines_ = matrix.lines_;
    columns_ = matrix.columns_;
  }
  return *this;
}

Matrix& Matrix::operator= (Matrix&& matrix)
{
  if (this != &matrix)
  {
    lines_ = matrix.lines_;
    columns_ = matrix.columns_;
    matrix_.swap(matrix.matrix_);
    matrix_.reset();
    matrix.lines_ = 0;
    matrix.columns_ = 0;
  }
  return *this;
}

const Shape** Matrix::operator [](const size_t &index) const
{
  if (index > lines_)
  {
    throw std::invalid_argument("Index out of range!");
  }
  return(matrix_.get() + index * columns_);
}

void Matrix::addShape(const Shape *shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("The added shape does not exist!");
  }
  for (size_t i = 0; i < columns_ * lines_; i++)
  {
    if (matrix_[i] == shape)
    {
      throw std::invalid_argument("Matrix already contain this shape!");
    }
  }
  size_t size = lines_ * columns_;
  size_t temp_lines = lines_;
  size_t temp_columns = columns_;
  size_t num_line = 1;
  size_t empty_columns = 0;
  while (size > 0)
  {
    size--;

    if (isOverlap(matrix_[size], shape))
    {
      num_line = (size / columns_) + 2;
    }
  }
  if (num_line > lines_)
  {
    temp_lines++;
    empty_columns = columns_;
  }
  else
  {
    size_t i = (num_line - 1) * columns_;
    while (i < (num_line * columns_))
    {
      if (matrix_[i] == nullptr)
      {
        empty_columns++;
      }
      i++;
    }
    if (empty_columns == 0)
    {
      temp_columns++;
      empty_columns = 1;
    }
  }
  std::unique_ptr <const Shape*[]> temp_matrix(new const Shape*[temp_columns * temp_lines]);
  for (size_t i = 0; i < temp_lines; i++)
  {
    for (size_t j = 0; j < temp_columns; j++)
    {
      if (i >= lines_ || j >= columns_)
      {
        temp_matrix[i * temp_columns + j] = nullptr;
        continue;
      }
      temp_matrix[i * temp_columns + j] = matrix_[i * columns_ + j];
    }
  }
  temp_matrix[num_line * temp_columns - empty_columns] = shape;
  matrix_.swap(temp_matrix);
  lines_ = temp_lines;
  columns_ = temp_columns;
}

void Matrix::show() const
{
  std::cout << "Lines: " << lines_ << '\n';
  std::cout << "Columns: " << columns_;
  for (size_t j = 0; j < lines_; j++)
  {
    std::cout << "\n\n----------------------";
    for (size_t i = 0; i < columns_; i++)
    {
      if (matrix_[j * columns_ + i] != nullptr)
      {
        std::cout << "\n\n";
        matrix_[j * columns_ + i]->show();
      }
    }
  }
}

bool Matrix::isOverlap(const Shape *shape1, const Shape *shape2) const noexcept
{
  if((shape1 == nullptr) || (shape2 == nullptr))
  {
    return false;
  }
  return ((fabs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x)
      < ((shape1->getFrameRect().height / 2) + (shape2->getFrameRect().height / 2)))
      && ((fabs(shape1->getFrameRect().pos.y - shape2->getFrameRect().pos.y)
      < ((shape1->getFrameRect().width / 2) + (shape2->getFrameRect().width / 2)))));
}
