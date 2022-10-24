#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace potapova;

void printGetFrameResult(const rectangle_t& rectangle)
{
  std::cout << "\nFrame rect figure data:" << '\n' << "Central Point: "
      << "(" << rectangle.pos.x << ", " << rectangle.pos.y << ")"
      << '\n' << "Wedth: " << rectangle.width
      << '\n' << "Height: " << rectangle.height;
}
void printShape(const Shape& shape, const char* name)
{
  std::cout << "Figure name: " << name << std::endl;
  std::cout << "============================" << std::endl;
  shape.show();
  std::cout << '\n' <<std::endl;
  std::cout << name << " area: " << shape.getArea();
  std::cout << '\n' <<std::endl;
  printGetFrameResult(shape.getFrameRect());
  std::cout << '\n' <<std::endl;
}

int main()
{
  try
  {
    size_t index = 0;
    double scaleValue = 4.0;
    double moveOx = 2.0;
    double moveOy = 4.0;
    point_t movePoint{4, 6};
    potapova::Circle test_circle({3, 3}, 1);
    potapova::Rectangle test_rectangle({{5, 5}, 10, 5});

    printShape(test_circle, "Circle");

    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):" << std::endl;
    test_circle.move(movePoint);
    test_circle.show();
    std::cout << "\n\n";

    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":" << std::endl;
    test_circle.move(moveOx, moveOy);
    test_circle.show();
    std::cout << "\n\n";

    std::cout << "'" << scaleValue << "' scaling result: " << std::endl;
    test_circle.scale(scaleValue);
    test_circle.show();
    std::cout << "\n\n";

    printShape(test_rectangle, "Rectangle");

    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):" << std::endl;
    test_rectangle.move(movePoint);
    test_rectangle.show();
    std::cout << "\n\n";

    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":" << std::endl;
    test_rectangle.move(moveOx, moveOy);
    test_rectangle.show();
    std::cout << '\n' << std::endl;

    std::cout << "'" << scaleValue << "' scaling result: " << std::endl;
    test_rectangle.scale(scaleValue);
    test_rectangle.show();
    std::cout << "\n\n";

    std::cout << "Composite shapes:\n" << "===================";
    std::shared_ptr<Shape> test_rectangle1 = std::make_shared<Rectangle>(Rectangle({{2, 2}, 10, 5}));
    std::shared_ptr<Shape> test_circle1 = std::make_shared<Circle>(Circle({3, 3}, 1));
    potapova::CompositeShape shapes;
    shapes.addShape(test_rectangle1);
    shapes.addShape(test_circle1);
    shapes.show();
    std::cout << "\n\nArea:\n" << "===================";
    std::cout << '\n' << shapes.getArea() << '\n';
    std::cout << "-------------------------";
    printGetFrameResult(shapes.getFrameRect());
    std::cout << '\n';
    std::cout << "\n\nAfter move in point (4, 6):\n" << "===========================";
    shapes.move(movePoint);
    shapes.show();
    std::cout << "\n\nAfter move Ox = 2 and Oy = 4:\n" << "===========================";
    shapes.move(moveOx, moveOy);
    shapes.show();
    std::cout << "\n\nAfter scaling (х2):\n" << "===================";
    shapes.scale(2);
    shapes.show();
    std::cout << "\n\nComposite shapes after deleting first shape (rectangle):";
    shapes.removeShape(index);
    shapes.show();
    std::cout << '\n';
    
    potapova::Rectangle test_rectangle5({{7, 5}, 6, 5});
     potapova::Rectangle test_rectangle6({{5, 8}, 2, 3});
     potapova::Rectangle test_rectangle7({{15, 4}, 10, 35});
     potapova::Rectangle test_rectangle8({{5, 5}, 15, 5});
     
    
    std::cout << "\nMatrix:\n" << "===================\n";
    potapova::Matrix matrix;
    matrix.addShape(&test_rectangle);
    matrix.addShape(&test_rectangle5);
//    matrix.addShape(&test_rectangle6);
//    matrix.addShape(&test_rectangle7);
//    matrix.addShape(&test_rectangle8);
    matrix.print();
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << std::endl;
    return -1;
  }
  return 0;
}
