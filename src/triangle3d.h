#pragma once

#include "point3d.h"
#include "vector3d.h"

namespace ti {

//! Represent a triangle object in 3D set by three 
//! 'p0', 'p1', 'p2' Points3D
class Triangle3D {
 public:
  Triangle3D() = default;
  Triangle3D(const Point3D& inP0, const Point3D& inP1, const Point3D& inP2);
  Triangle3D(const Triangle3D& other);

  const Point3D& P0() const;
  const Point3D& P1() const;
  const Point3D& P2() const;

  //! Build Vecto3D(p0, p1) object
  Vector3D Direction01() const;

  //! Build Vecto3D(p0, p1) object
  Vector3D Direction02() const;

  //! Checks if the triangle is degenerated
  bool IsDenerated() const;

  Triangle3D& operator=(const Triangle3D& other);

 private:
  Point3D p0;
  Point3D p1;
  Point3D p2;
};

inline Vector3D Triangle3D::Direction01() const { return Vector3D(p0, p1); }

inline Vector3D Triangle3D::Direction02() const { return Vector3D(p0, p2); }

}  // namespace ti