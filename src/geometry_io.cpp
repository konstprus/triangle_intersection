#include "geometry_io.h"

#include "point3d.h"
#include "triangle3d.h"

std::ostream& operator<<(std::ostream& os, const ti::Point3D& point) {
  os << point.X() << " " << point.Y() << " " << point.Z();
  return os;
}

std::ostream& operator<<(std::ostream& os, const ti::Triangle3D& triangle) {
  os << triangle.P0() << " " << triangle.P1() << " " << triangle.P2();
  return os;
}

std::istream& operator>>(std::istream& is, ti::Point3D& point) {
  double x, y, z;
  is >> x >> y >> z;
  point = ti::Point3D(x, y, z);
  return is;
}

std::istream& operator>>(std::istream& is, ti::Triangle3D& triangle) {
  ti::Point3D p0, p1, p2;
  is >> p0 >> p1 >> p2;
  triangle = ti::Triangle3D(p0, p1, p2);
  return is;
}
