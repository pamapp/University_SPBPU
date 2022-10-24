#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <memory>
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

using namespace potapova;

BOOST_AUTO_TEST_SUITE(testMatrixAndRotate)

BOOST_AUTO_TEST_CASE(invalid_matrix_constructor_parameter)
{
  BOOST_CHECK_THROW (Matrix(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_matrix_adding_empty_shape)
{
  Matrix matrix;
  BOOST_CHECK_THROW (matrix.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_matrix_adding_already_available_shape)
{
  Circle test_circle({3, 4}, 1);
  Matrix matrix(&test_circle);
  BOOST_CHECK_THROW (matrix.addShape(&test_circle), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(check_matrix_copy_constructor)
{
  Circle test_circle({3, 4}, 4);
  Matrix matrix(&test_circle);
  BOOST_CHECK(matrix[1][1] = &test_circle);
}

BOOST_AUTO_TEST_CASE(check_adding_first_shape)
{
  Circle test_circle({3, 4}, 4);
  Matrix matrix;
  matrix.addShape(&test_circle);
  BOOST_CHECK(matrix[1][1] = &test_circle);
}

BOOST_AUTO_TEST_CASE(check_adding_not_overlap_shape)
{
  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({20, 20}, 1));
  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{18, 19}, 1, 2}));
  Circle test_circle1({3, 4}, 4);
  Rectangle test_rectangle1({{10, 16}, 1, 1});
  CompositeShape comp_shapes;
  comp_shapes.addShape(test_circle);
  comp_shapes.addShape(test_rectangle);
  Matrix matrix(&test_circle1);
  matrix.addShape(&test_rectangle1);
  matrix.addShape(&comp_shapes);
  BOOST_CHECK(matrix[1][1] = &test_circle1);
  BOOST_CHECK(matrix[1][2] = &test_rectangle1);
  BOOST_CHECK(matrix[1][3] = &comp_shapes);
}

BOOST_AUTO_TEST_CASE(check_adding_overlap_shape)
{
  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({1, 2}, 7));
  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{18, 19}, 1, 2}));
  Circle test_circle1({3, 4}, 4);
  Rectangle test_rectangle1({{5, 5}, 7, 7});
  CompositeShape comp_shapes;
  Matrix matrix(&test_circle1);
  matrix.addShape(&test_rectangle1);
  matrix.addShape(&comp_shapes);
  BOOST_CHECK(matrix[1][1] = &test_circle1);
  BOOST_CHECK(matrix[2][1] = &test_rectangle1);
  BOOST_CHECK(matrix[2][2] = &comp_shapes);
}

BOOST_AUTO_TEST_CASE(const_rectangle_width_and_height_and_area_after_rotating)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double rectangle_area = test_rectangle.getArea();
  const double rectangle_width = test_rectangle.getFrameRect().width;
  const double rectangle_height = test_rectangle.getFrameRect().height;
  double angle = 90;
  test_rectangle.rotate(angle);
  BOOST_CHECK_CLOSE(rectangle_area, test_rectangle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(rectangle_width, test_rectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(rectangle_height, test_rectangle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(const_circle_width_and_height_and_area_after_rotating)
{
  Circle test_circle({5, 5}, 2);
  const double circle_area = test_circle.getArea();
  const double circle_width = test_circle.getFrameRect().width;
  const double circle_height = test_circle.getFrameRect().height;
  double angle = 90;
  test_circle.rotate(angle);
  BOOST_CHECK_CLOSE(circle_area, test_circle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(circle_width, test_circle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(circle_height, test_circle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(const_composite_shape_width_and_height_and_area_after_rotating)
{
  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
  CompositeShape composite_shape;
  composite_shape.addShape(test_circle);
  composite_shape.addShape(test_rectangle);
  const double composite_shape_area = composite_shape.getArea();
  const double composite_shape_width = composite_shape.getFrameRect().width;
  const double composite_shape_height = composite_shape.getFrameRect().height;
  double angle = 90;
  composite_shape.rotate(angle);
  BOOST_CHECK_CLOSE(composite_shape_area, composite_shape.getArea(), epsilon);
  BOOST_CHECK_CLOSE(composite_shape_width, composite_shape.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(composite_shape_height, composite_shape.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
