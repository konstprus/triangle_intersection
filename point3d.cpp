#include "point3d.h"

namespace ti {

Point3D::Point3D() : Base3D() {}

Point3D::Point3D(double x, double y, double z) : Base3D(x, y, z) {}

Point3D::Point3D(const Point3D& other) : Base3D(other.x, other.y, other.z) {}

Point3D& Point3D::operator=(const Point3D& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  return *this;
}

//double Point3D::SquareDistance(const Point3D& other) const {
//  double squareDistance = 0;
//  double temp = 0;
//  temp = x - other.x;
//  temp *= temp;
//  squareDistance += temp;
//
//  temp = y - other.y;
//  temp *= temp;
//  squareDistance += temp;
//
//  temp = z - other.z;
//  temp *= temp;
//  squareDistance += temp;
//  return squareDistance;
//}
//
//double Point3D::Distance(const Point3D& other) const { 
//  return sqrt(SquareDistance(other));
//}
//
//double Distance(const Point3D& p1, const Point3D& p2) {
//  return p1.Distance(p2);
//}

}  // namespace ti