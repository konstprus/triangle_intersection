#include "intersection_algorithms.h"

#include <cmath>
#include <utility>

#include "global_constants.h"
#include "iostream"

namespace ti {

namespace {

//! Helper function for getting a pair x, y, or z non zero components 
//! from two vectors. F.e. if both x components of vector1 and vector2
//! the function returns the pair of v1x and v2x. It not it check y 
//! components and so on 
std::pair<double, double> GetCoordCandidates(const Vector3D& vector1,
                                             const Vector3D& vector2) {
  std::pair<double, double> result;
  if (std::abs(vector2.X()) > TOLERANCE) {
    result = std::make_pair<double, double>(vector1.X(), vector2.X());
    if (std::abs(vector1.X()) > TOLERANCE) {
      return result;
    }
  }
  if (std::abs(vector2.Y()) > TOLERANCE) {
    result = std::make_pair<double, double>(vector1.Y(), vector2.Y());
    if (std::abs(vector1.Y()) > TOLERANCE) {
      return result;
    }
  }
  if (std::abs(vector2.Z()) > TOLERANCE) {
    result = std::make_pair<double, double>(vector1.Z(), vector2.Z());
  }
  return result;
}

//! Checks if two segments lying on the same plane intersect. The segments'
//! plane is set by 'normal' vector. 
//! ONLY FOR INTERNAL USE
//! We should checks if segments belongs two same plane before the function call
//! Returns incorrect result if the segments are skew
bool IsIntersect(const Segment3D& segment1, const Segment3D& segment2,
                 const Vector3D& normal) {
  Vector3D a = segment1.P0() - segment2.P0();
  Vector3D u = segment1.DirectionVector();
  Vector3D v = segment2.DirectionVector();
  Vector3D v_ = Cross(normal, v);
  double av_ = Scalar(a, v_);
  double uv_ = Scalar(u, v_);
  if (std::abs(uv_) < TOLERANCE) {
    // segments are parallel
    if (std::abs(av_) < TOLERANCE) {
      // segments are on the same line
      auto candidates = GetCoordCandidates(a, v);
      double t = candidates.first / candidates.second;
      return t >= 0 && t <= 1;
    }
    return false;
  }
  double t = av_ / uv_;
  return t >= 0 && t <= 1;
}

//! Helper function checks if a point is inside a triangle. The point is
//! set by a vector 'm' with the beginning in the vertex 'P0' of the triangle
//! and the triangle is set by two direction vectors 'u' and 'v' which are
//! u = P1 - P0 and v = P2 - P0. In this function we don't need to check
//! the correctness of input data, because it's ONLY FOR INTERNAL USE and
//! all checks should be done before the function call
bool IsInside(const Vector3D& m, const Vector3D& u, const Vector3D& v) {
  double mu = Scalar(m, u);
  double mv = Scalar(m, v);
  double vu = Scalar(v, u);
  double vv = Scalar(v, v);
  double uu = Scalar(u, u);
  double D = vu * vu - uu * vv;
  double t1c = (mu * vu - mv * uu) / D;
  double t2c = (mv * vu - mu * vv) / D;
  if (t1c < 0 || t2c < 0 || t1c + t2c > 1) {
    return false;
  }
  return true;
}

//! Checks if the point intersect the triangle. We don't need to check if 
//! the triangle is denerated, because it's ONLY FOR INTERNAL USE, and all
//! checks should be done befor the function call
bool IsIntersect(const Point3D& point, const Triangle3D& triangle) {
  Vector3D u = triangle.Direction01();  // triangle.P1() - triangle.P0();
  Vector3D v = triangle.Direction02();  // triangle.P2() - triangle.P0();
  Vector3D n = Cross(u, v);

  Vector3D a = point - triangle.P0();
  double scalNA = Scalar(a, n);
  if (std::abs(scalNA) < TOLERANCE) {
    return IsInside(a, u, v);
    
  }
  // the point doen'st belong to the triangle plane
  return false;
}

//! Calculates the longest segments for a denerated triangle if P0P1 and
//! P0P2 vectors are non zero and colinear, and before call the this function
//! we should be sure that it is.
//! ONLY FOR INTERNAL USE
Segment3D CalculateTheLongestSegment(const Triangle3D& triangle) {
  const auto& p0 = triangle.P0();
  const auto& p1 = triangle.P1();
  const auto& p2 = triangle.P2();
  Point3D candidateP0 = p0;
  Point3D candidateP1 = p1;
  Vector3D candidateDir = p1 - p0;
  Vector3D p2p1 = p2 - p1;
  auto candidates = GetCoordCandidates(p2p1, candidateDir);
  double t = candidates.first / candidates.second;
  if (t < 0) {
    candidateP0 = p2;
  } else if (t > 1) {
    candidateP1 = p2;
  }
  return Segment3D(candidateP0, candidateP1);
}

//! Checks if two triangles intersect in the case if the first one is degenerated.
//! Befor call this function we should be sure if the first triangle is denerated.
//! It analyzes to what geometry is generated: point or segment and call the appropriate
//! function point-triangle or segment-triangle call
//! ONLY FOR INTERNAL USE
bool IsIntersectWidthDenerated(const Triangle3D& deneratedTriangle,
                               const Triangle3D& triangle) {
  // 'deneratedTriangle' is degenerated.
  // We should check if degenerates to point or segment
  Vector3D u = deneratedTriangle.Direction01();
  Vector3D v = deneratedTriangle.Direction02();
  if (u.IsZero()) {
    if (v.IsZero()) {
      // deneratedTriangle degenerates to point;
      return IsIntersect(deneratedTriangle.P0(), triangle);
    }
    // deneratedTriangle degenerates to Segment(P0, P2)
    return IsIntersect(
        Segment3D(deneratedTriangle.P0(), deneratedTriangle.P2()), triangle);
  }
  if (v.IsZero()) {
    // deneratedTriangle degenerates to Segment(P0, P1)
    return IsIntersect(
        Segment3D(deneratedTriangle.P0(), deneratedTriangle.P1()), triangle);
  }
  // u and v vectors are collinear. We should calculate the longest
  // segment the triangle degenerates  to.
  auto segmentTr = CalculateTheLongestSegment(triangle);
  return IsIntersect(segmentTr, triangle);
}

}  // namespace

bool IsIntersect(const Point3D& point1, const Point3D& point2) {
  return point1 == point2;
}

bool IsIntersect(const Point3D& point, const Segment3D& segment) {
  if (segment.IsZero()) {
    // segment is degenerated. We should check only if the point is equal to P0
    // or P1 of the segment
    return IsIntersect(point, segment.P0());
  }
  Vector3D a = point - segment.P0();
  if (a.IsZero()) {
    // point is equal to P0 point of the segment
    return true;
  }
  Vector3D dir = segment.DirectionVector();
  Vector3D crossADir = Cross(a, dir);

  if (std::abs(Scalar(crossADir, segment.DirectionVector())) > TOLERANCE) {
    // point doesn't belong to the line of the segment
    return false;
  }
  auto candidates = GetCoordCandidates(a, dir);
  double t = candidates.first / candidates.second;
  return t >= 0 && t <= 1;
}

bool IsIntersect(const Segment3D& segment1, const Segment3D& segment2) {
  Vector3D u = segment1.DirectionVector();
  Vector3D v = segment2.DirectionVector();
  Vector3D a = segment1.P0() - segment2.P0();
  if (a.IsZero()) {
    return true;
  }
  Vector3D n = Cross(u, v);
  Vector3D au = Cross(a, u);
  if (n.IsZero()) {
    // Segments are parallel
    if (au.IsZero()) {
      // Segments belongs to the same line
      auto candidates = GetCoordCandidates(a, v);
      double t = candidates.first / candidates.second;
      return t >= 0 && t <= 1;
    }
    return IsIntersect(segment1, segment2, au);
  }
  if (Cross(n, au).IsZero()) {
    // Segments are skew. They cannot intersect
    return false;
  }
  return IsIntersect(segment1, segment2, au);
}

bool IsIntersect(const Segment3D& segment, const Triangle3D& triangle) {
  Vector3D u = triangle.Direction01();  // triangle.P1() - triangle.P0();
  Vector3D v = triangle.Direction02();  // triangle.P2() - triangle.P0();
  Vector3D n = Cross(u, v);
  if (n.IsZero()) {
    // triangle is denegerated;
    if (u.IsZero()) { 
      if (v.IsZero()) {
       // triangle degenerates to point;
        return IsIntersect(triangle.P0(), segment);
      }
      // triangle degenerates to Segment(P0, P2)
      return IsIntersect(segment, Segment3D(triangle.P0(), triangle.P2()));
    }
    if (v.IsZero()) {
      // triangle degenerates to Segment(P0, P1)
      return IsIntersect(segment, Segment3D(triangle.P0(), triangle.P1()));
    }
    // u and v vectors are collinear. We should calculate the longest 
    // segment the triangle degenerates  to.
    auto segmentTr = CalculateTheLongestSegment(triangle);
    return IsIntersect(segment, segmentTr);
  }

  Vector3D d = segment.DirectionVector();
  Vector3D a = segment.P0() - triangle.P0();
  if (a.IsZero()) {
    // P0 point of segment is equal to P0 point of the triangle
    return true;
  }
  Vector3D b = segment.P1() - triangle.P0();
  if (b.IsZero()) {
    // P1 point of segment is equal to P0 point of the triangle
    return true;
  }

  double scalNA = Scalar(n, a);
  double scalNB = Scalar(n, b);
  if (std::abs(scalNB) > TOLERANCE && std::abs(scalNA) > TOLERANCE) {
    if (scalNB * scalNA > 0) {
      // points P0 and P1 of segment are on the same side of the triangle plane
      return false;
    }
  }

  double scalND = Scalar(n, d);
  // check if triangle planes are parallel
  if (std::abs(scalND) < TOLERANCE) {
    if (d.IsZero()) {
      // segment degenrates to point
      return IsIntersect(segment.P0(), triangle);
    }
    // check if triangle planes are the same
    if (std::abs(scalNA) < TOLERANCE) {
      // triangle planes are the same
      if (IsIntersect(segment.P0(), triangle) || 
          IsIntersect(segment.P1(), triangle)) {
        // check if one point of the segment is inside the triangle
        return true;
      }
      Segment3D tr1(triangle.P0(), triangle.P1());
      Segment3D tr2(triangle.P0(), triangle.P2());
      Segment3D tr3(triangle.P1(), triangle.P2());
      return IsIntersect(segment, tr1, n) || 
             IsIntersect(segment, tr2, n) ||
             IsIntersect(segment, tr3, n);
    } 
    else {
      // not interserction because the triangles planes are
      // parallel but not the same
      return false;
    }
  }

  double tc = -scalNA / scalND;
  if (tc < 0 || tc > 1) {
    // no intersection
    return false;
  }

  // intersect point of the segment and triangle plane
  Vector3D Pc = segment.P0() + d * tc;
  Vector3D m = Pc - triangle.P0();

  return IsInside(m, u, v);
  //double mu = Scalar(m, u);
  //double mv = Scalar(m, v);
  //double vu = Scalar(v, u);
  //double vv = Scalar(v, v);
  //double uu = Scalar(u, u);
  //double D = vu * vu - uu * vv;
  //double t1c = (mu * vu - mv * uu) / D;
  //double t2c = (mv * vu - mu * vv) / D;
  //if (t1c < 0 || t2c < 0 || t1c + t2c > 1) {
  //  return false;
  //}
  //return true;
}

bool IsIntersect(const Triangle3D& triangle1, const Triangle3D& triangle2) {
  if (triangle1.IsDenerated()) {
    return IsIntersectWidthDenerated(triangle1, triangle2);
  }
  if (triangle2.IsDenerated()) {
    return IsIntersectWidthDenerated(triangle2, triangle1);
  }
  // triangle1 and triangle2 are not degenerated. 
  // two triangles intersect if at least of one edge of one triangle
  // intersect the other one.
  Segment3D S1(triangle1.P0(), triangle1.P1());
  Segment3D S2(triangle1.P0(), triangle1.P2());
  Segment3D S3(triangle1.P1(), triangle1.P2());
  auto result = IsIntersect(S1, triangle2) || 
                    IsIntersect(S2, triangle2) ||
                    IsIntersect(S3, triangle2);
  if (!result) {
    // we also should check intersection of triangle2's edge with triangle1
    Segment3D S1(triangle2.P0(), triangle2.P1());
    Segment3D S2(triangle2.P0(), triangle2.P2());
    Segment3D S3(triangle2.P1(), triangle2.P2());
    result = IsIntersect(S1, triangle1) || 
             IsIntersect(S2, triangle1) ||
             IsIntersect(S3, triangle1);
  }
  return result;
}

}  // namespace ti
