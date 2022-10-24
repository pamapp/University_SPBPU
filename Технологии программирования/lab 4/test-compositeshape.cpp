//#define BOOST_TEST_MAIN
//#include <boost/test/included/unit_test.hpp>
//#include <cmath>
//#include <memory>
//#include "composite-shape.hpp"
//#include "circle.hpp"
//#include "rectangle.hpp"
//
//using namespace potapova;
//
//const double epsilon = 0.001;
//
//BOOST_AUTO_TEST_SUITE(testCompositeShape)
//
//BOOST_AUTO_TEST_CASE(invalid_add_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  CompositeShape shapes;
//  shapes.addShape(test_circle);
//  BOOST_CHECK_THROW(shapes.addShape(nullptr), std::invalid_argument);
//}
//
//BOOST_AUTO_TEST_CASE(invalid_index_of_remove_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  size_t index = 1;
//  CompositeShape shapes;
//  shapes.addShape(test_circle);
//  BOOST_CHECK_THROW(shapes.removeShape(index), std::out_of_range);
//}
//
//BOOST_AUTO_TEST_CASE(add_shapes_in_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_circle);
//  shapes.addShape(test_rectangle);
//  BOOST_CHECK(shapes[0] == test_circle);
//  BOOST_CHECK(shapes[1] == test_rectangle);
//}
//
//BOOST_AUTO_TEST_CASE(remove_shape_in_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_circle);
//  shapes.addShape(test_rectangle);
//  shapes.removeShape(0);
//  BOOST_CHECK(shapes[0] == test_rectangle);
//}
//
//BOOST_AUTO_TEST_CASE(const_composite_shape_parameters_and_area_after_move_dx_dy)
//{
//  CompositeShape shapes;
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  const double rectangle_area = test_rectangle->getArea();
//  const double circle_area = test_circle->getArea();
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  shapes.move(2, 4);
//  BOOST_CHECK_CLOSE(shapes.getArea(), rectangle_area + circle_area, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, 10, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, 5.5, epsilon);
//}
//
//BOOST_AUTO_TEST_CASE(const_composite_shape_parameters_and_area_after_move_point)
//{
//  CompositeShape shapes;
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{2, 2}, 10, 5}));
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  const double rectangle_area = test_rectangle->getArea();
//  const double circle_area = test_circle->getArea();
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  shapes.move({2, 4});
//  BOOST_CHECK_CLOSE(shapes.getArea(), rectangle_area + circle_area, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, 10, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, 5, epsilon);
//}
//
//BOOST_AUTO_TEST_CASE(invalid_scale_parameter_for_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  const double factor = 0;
//  BOOST_CHECK_THROW (shapes.scale(factor), std::invalid_argument);
//}
//
//BOOST_AUTO_TEST_CASE(scale_frame_rect_pos_for_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  const double factor = 2;
//  shapes.scale(factor);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, 5, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, 5, epsilon);
//}
//
//BOOST_AUTO_TEST_CASE(scale_frame_rect_width_and_height_for_composite_shape)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  const double factor = 2;
//  shapes.scale(factor);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, 20, epsilon);
//  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, 10, epsilon);
//}
//
//BOOST_AUTO_TEST_CASE(composite_shape_quadratic_area_change_after_scaling)
//{
//  std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({3, 3}, 1));
//  std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{5, 5}, 10, 5}));
//  CompositeShape shapes;
//  shapes.addShape(test_rectangle);
//  shapes.addShape(test_circle);
//  double area = shapes.getArea();
//  double factor = 3;
//  shapes.scale(factor);
//  BOOST_CHECK_CLOSE(shapes.getArea(), area * factor * factor, epsilon);
//}
//
//BOOST_AUTO_TEST_CASE(invalid_amount_of_composite_shapes_for_scaling_)
//{
//  CompositeShape shapes;
//  const double factor = 2;
//  BOOST_CHECK_THROW (shapes.scale(factor), std::logic_error);
//}
//
//BOOST_AUTO_TEST_SUITE_END()
