#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>

CompositeShape::CompositeShape() :
  possibleAmount_(0),
  amount_(0),
  shapeArray_(nullptr)
{
}

CompositeShape::CompositeShape(const CompositeShape& other) :
  possibleAmount_(other.possibleAmount_),
  amount_(other.amount_),
  shapeArray_(new std::shared_ptr<Shape>[other.possibleAmount_])
{
  for (size_t i = 0; i < other.amount_; i++)
  {
    shapeArray_[i] = other.shapeArray_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape&& other) :
  possibleAmount_(0),
  amount_(0),
  shapeArray_(nullptr)
{
  *this = std::move(other);
}

CompositeShape& CompositeShape::operator= (const CompositeShape &shape)
{
  if (this != &shape)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> tempArray(new std::shared_ptr<Shape>[shape.possibleAmount_]);
    for (size_t i = 0; i < shape.amount_; i++)
    {
      tempArray[i] = shape.shapeArray_[i];
    }
    shapeArray_.swap(tempArray);
    amount_ = shape.amount_;
    possibleAmount_ = shape.possibleAmount_;
  }
  return *this;
}

CompositeShape& CompositeShape::operator= (CompositeShape&& shape)
{
  if (this != &shape)
  {
    possibleAmount_ = shape.possibleAmount_;
    amount_ = shape.amount_;
    shapeArray_.swap(shape.shapeArray_);
    shapeArray_.reset();
    shape.amount_= 0;
    shape.possibleAmount_ = 0;
  }
  return *this;
}

std::shared_ptr<Shape> &CompositeShape::operator[](size_t index)
{
  if (index >= possibleAmount_)
  {
    throw std::out_of_range("Index out of range!");
  }
  return shapeArray_[index];
}

std::shared_ptr<Shape> CompositeShape::operator[](size_t index) const
{
  if (index >= possibleAmount_)
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
  if (amount_ == possibleAmount_)
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp_array(new std::shared_ptr<Shape>[possibleAmount_ + 5]);
    possibleAmount_ += 5;
    for (size_t i = 0; i < amount_; i++)
    {
      temp_array[i] = shapeArray_[i];
    }
    shapeArray_.swap(temp_array);
  }
  shapeArray_[amount_++] = shape;
}

void CompositeShape::removeShape(size_t index)
{
  if (index >= amount_)
  {
    throw std::out_of_range("Out of size range!");
  }
  shapeArray_[index].reset();
  for (size_t i = index; i < amount_ - 1; i++)
  {
    shapeArray_[i] = shapeArray_[i + 1];
  }
  shapeArray_[amount_--].reset();
}

double CompositeShape::getArea() const noexcept
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
  if (amount_ == 0)
  {
    return{ {0, 0}, 0, 0 };
  }
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
  if (factor <= 0)
  {
    throw std::invalid_argument("Invalid scale factor!");
  }
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i]->move(getFrameRect().pos.x + factor * (shapeArray_[i]->getFrameRect().pos.x
        - getFrameRect().pos.x), getFrameRect().pos.y + factor
        * (shapeArray_[i]->getFrameRect().pos.y - getFrameRect().pos.y));
    shapeArray_[i]->scale(factor);
  }
}

void CompositeShape::rotate(double angle)
{
  for (size_t i = 0; i < amount_; i++)
  {
    shapeArray_[i]->rotate(angle);
  }
}

void CompositeShape::show() const
{
  std::cout << "Composite Shapes:";
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
