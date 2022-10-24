#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>

CompositeShape::CompositeShape() :
  amount_(0),
  shapeArray_(nullptr)
{
}

CompositeShape::CompositeShape(const CompositeShape& other) :
  amount_(1),
  shapeArray_(nullptr)
{
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i] = other.shapeArray_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape&& other)
{
  shapeArray_.swap(other.shapeArray_);
  other.shapeArray_.release();
  amount_ = other.amount_;
  other.amount_ = 0;
}

CompositeShape& CompositeShape::operator= (const CompositeShape &shape)
{
  if (this != &shape)
  {
    if (shape.amount_ == 0)
    {
      shapeArray_ = nullptr;
      amount_ = 0;
    }
    else
    {
      amount_ = shape.amount_;
      shapeArray_.swap(shapeArray_);
    }
  }
  return *this;
}

std::shared_ptr<Shape> &CompositeShape::operator[](size_t index) const
{
  if (index >= amount_)
  {
    throw std::out_of_range("Index out of range!");
  }
  return shapeArray_[index];
}

void CompositeShape::addShape(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("The added shape does not exist!");
  }
  for (size_t i = 0; i < amount_; i++)
  {
    if (shapeArray_[i] == shape)
    {
      throw std::invalid_argument("Composite Shape already contain this shape!");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> temp_array(new std::shared_ptr<Shape>[amount_ + 1]);
  for (size_t i = 0; i < amount_; i++)
  {
    temp_array[i] = shapeArray_[i];
  }
  temp_array[amount_++] = shape;
  shapeArray_.swap(temp_array);
}

void CompositeShape::removeShape(size_t index)
{
  if (index >= amount_)
  {
    throw std::out_of_range("Out of size range!");
  }
  for (size_t i = index; i < amount_ - 1; i++)
  {
    shapeArray_[i] = shapeArray_[i + 1];
  }
  amount_--;
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < amount_; i++)
  {
    area += shapeArray_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  const rectangle_t signalFrame = shapeArray_[0]->getFrameRect();
  double minX = signalFrame.pos.x - signalFrame.width / 2;
  double maxX = signalFrame.pos.x + signalFrame.width / 2;
  double minY = signalFrame.pos.y - signalFrame.height / 2;
  double maxY = signalFrame.pos.y + signalFrame.height / 2;
  for (size_t i = 0; i < amount_; i++)
  {
    const rectangle_t frame = shapeArray_[i]->getFrameRect();
    maxX = std::max(maxX, frame.pos.x + frame.width / 2);
    minX = std::min(minX, frame.pos.x - frame.width / 2);
    maxY = std::max(maxY, frame.pos.y + frame.height / 2);
    minY = std::min(minY, frame.pos.y - frame.height / 2);
  }
  return{ {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2}, maxX - minX, maxY - minY };
}

void CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i]->move(dx, dy);
  }
}

void CompositeShape::move(const point_t& point)
{
  point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i]->move(point.x - pos.x, point.y - pos.y);
  }
}

void CompositeShape::scale(double factor)
{
  if (amount_ == 0)
  {
    throw std::logic_error("Empty object!");
  }
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i]->scale(factor);
  }
}

void CompositeShape::show() const
{
  for (size_t i = 0; i < amount_; i++)
  {
    std::cout << '\n' << '\n' << "Shape № " << i + 1 << '\n' << "---------" << '\n';
    shapeArray_[i]->show();
    std::cout << "\nArea: " << shapeArray_[i]->getArea();
    std::cout << "\n\nFrame rect figure data:\n" << "Central Point: "
        << "(" << shapeArray_[i]->getFrameRect().pos.x
        << ", " << shapeArray_[i]->getFrameRect().pos.y << ")"
        << '\n' << "Wedth: " << shapeArray_[i]->getFrameRect().width
        << '\n' << "Height: " << shapeArray_[i]->getFrameRect().height;
  }
}
