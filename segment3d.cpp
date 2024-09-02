#include "segment3d.h"

namespace ti {

Segment3D::Segment3D(const Point3D& inP0, const Point3D& inP1)
    : p0(inP0), p1(inP1) {}

Segment3D::Segment3D(const Segment3D& other) : Segment3D(other.p0, other.p1) {}

const Point3D& Segment3D::P0() const { return p0; }

const Point3D& Segment3D::P1() const { return p1; }

bool Segment3D::IsZero() const { return p0 == p1; }

}  // namespace ti
