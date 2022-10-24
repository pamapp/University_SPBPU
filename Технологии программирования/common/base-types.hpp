#ifndef base_types_h
#define base_types_h

namespace potapova
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width;
    double height;
  };
}
#endif /* base_types_h */
