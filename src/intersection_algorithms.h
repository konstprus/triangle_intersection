#pragma once

#include "segment3d.h"
#include "triangle3d.h"

namespace ti {

bool IsIntersect(const Point3D& point1, const Point3D& point2);
bool IsIntersect(const Point3D& point, const Segment3D& segment);
bool IsIntersect(const Segment3D& segment1, const Segment3D& segment2);
bool IsIntersect(const Segment3D& segment, const Triangle3D& triangle);
bool IsIntersect(const Triangle3D& triangle1, const Triangle3D& triangle2);

}  // namespace ti
