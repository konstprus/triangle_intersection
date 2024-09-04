#include "triangle3d.h"
#include "global_constants.h"

#include <limits>
#include <cmath>


namespace ti {

Triangle3D::Triangle3D(const Point3D& intP0, const Point3D& inP1, const Point3D& inP2)
    : p0(intP0), p1(inP1), p2(inP2) {}

Triangle3D::Triangle3D(const Triangle3D& other)
    : Triangle3D(other.p0, other.p1, other.p2) {}

const Point3D& Triangle3D::P0() const { return p0; }

const Point3D& Triangle3D::P1() const { return p1; }

const Point3D& Triangle3D::P2() const { return p2; }

bool Triangle3D::IsDenerated() const {
  auto n = Cross(Direction01(), Direction02());
  return n.IsZero();
}

Triangle3D& Triangle3D::operator=(const Triangle3D& other) {
  p0 = other.p0;
  p1 = other.p1;
  p2 = other.p2;
  return *this;
}

}  // namespace ti
