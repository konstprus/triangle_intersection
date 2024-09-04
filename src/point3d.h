#pragma once

#include "base3d.h"

namespace ti {

//! Represents a cartesian point in 3D.
class Point3D : public Base3D {
 public:
  Point3D();
  Point3D(double x, double y, double z);
  Point3D(const Point3D& other);

  Point3D& operator=(const Point3D& other);

  //double SquareDistance(const Point3D& other) const;
  //double Distance(const Point3D& other) const;
};

//double Distance(const Point3D& p1, const Point3D& p2);

}  // namespace ti
