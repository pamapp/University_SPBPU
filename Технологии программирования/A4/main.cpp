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
  std::cout << "Figure name: " << name << '\n';
  std::cout << "============================\n";
  shape.show();
  std::cout << "\n\n";
  std::cout << name << " area: " << shape.getArea();
  std::cout << "\n\n";
  printGetFrameResult(shape.getFrameRect());
  std::cout << "\n\n";
}

int main()
{
  try
  {
    size_t index = 0;
    double angle = 90;
    double scaleValue = 4.0;
    double moveOx = 2.0;
    double moveOy = 4.0;
    point_t movePoint{4, 6};
    potapova::Circle test_circle({3, 3}, 1);
    potapova::Rectangle test_rectangle({{5, 5}, 10, 5});

    printShape(test_circle, "Circle");

    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):\n";
    test_circle.move(movePoint);
    test_circle.show();
    std::cout << "\n\n";

    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":\n";
    test_circle.move(moveOx, moveOy);
    test_circle.show();
    std::cout << "\n\n";

    std::cout << "'" << scaleValue << "' scaling result:\n";
    test_circle.scale(scaleValue);
    test_circle.show();
    std::cout << "\n\n";

    std::cout << "Rotate (90):\n";
    test_circle.rotate(angle);
    test_circle.show();
    std::cout << "\n\n";
    
    printShape(test_rectangle, "Rectangle");
    
    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):\n";
    test_rectangle.move(movePoint);
    test_rectangle.show();
    std::cout << "\n\n";

    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":\n";
    test_rectangle.move(moveOx, moveOy);
    test_rectangle.show();
    std::cout << "\n\n";

    std::cout << "'" << scaleValue << "' scaling result:\n";
    test_rectangle.scale(scaleValue);
    test_rectangle.show();
    std::cout << "\n\n";
    
    std::cout << "Rotate (90):\n";
    test_rectangle.rotate(angle);
    test_rectangle.show();
    std::cout << "\n\n";

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
    std::cout << "\nAfter move in point (4, 6):\n" << "===========================\n";
    shapes.move(movePoint);
    shapes.show();
    std::cout << "\n\nAfter move Ox = 2 and Oy = 4:\n" << "===========================\n";
    shapes.move(moveOx, moveOy);
    shapes.show();
    std::cout << "\n\nAfter scaling (х2):\n" << "===================\n";
    shapes.scale(2);
    shapes.show();
    std::cout << "\n\nAfter rotating (90):\n" << "===================\n";
    shapes.rotate(90);
    shapes.show();
    std::cout << "\n\nAfter deleting № " << index << " shape:\n" << "=========================\n";
    shapes.removeShape(index);
    shapes.show();
    std::cout << '\n';

    potapova::Rectangle test_rectangle5({{10, 10}, 8, 8});
    potapova::Rectangle test_rectangle6({{10, 22}, 8, 8});
    potapova::Circle test_circle7({28, 20}, 2);
    potapova::Rectangle test_rectangle8({{16, 16}, 8, 8});
    potapova::Circle test_circle8({28, 18}, 2);

    std::cout << "\nMatrix:\n" << "===================\n";
    Matrix matrix(&test_rectangle5);
    matrix.addShape(&test_rectangle8);
    matrix.addShape(&test_circle7);
    matrix.addShape(&test_rectangle6);
    matrix.addShape(&test_circle8);
    matrix.addShape(&shapes);
    matrix.show();
    std::cout << "\n\n";
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << std::endl;
    return -1;
  }
  return 0;
}
