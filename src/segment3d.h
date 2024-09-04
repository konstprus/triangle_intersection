#pragma once

#include "point3d.h"
#include "vector3d.h"

namespace ti {

//! Represents a segment object in 3D set by
//! a couple of Point3D 'inP0' and 'inP1'.
class Segment3D {
 public:
  Segment3D() = default;
  Segment3D(const Point3D& inP0, const Point3D& inP1);
  Segment3D(const Segment3D& other);

  //! Return the Point3D P0, so called start point
  //! of the segment.
  const Point3D& P0() const;

  //! Return the Point3D P0, so called end point
  //! of the segment.
  const Point3D& P1() const;

  //! Build the Direction Vector of the segment.
  //! NOTE: This vector is not normalized
  Vector3D DirectionVector() const;

  //! Checks if the segment is zero length.
  //! P0 == P1
  bool IsZero() const;

 private:
  Point3D p0;
  Point3D p1;
};

inline Vector3D Segment3D::DirectionVector() const { return Vector3D(p0, p1); }

}  // namespace ti
