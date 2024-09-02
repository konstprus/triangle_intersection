#pragma once

#include "base3d.h"
#include "point3d.h"

namespace ti {

//! Represents a mathematical vector in 3D.
//! Only necessary operations with vectors
//! need for solving Triangle Intersection 
//! Problem were implemented
class Vector3D : public Base3D {
 public:
  Vector3D();
  Vector3D(double x, double y, double z);
  Vector3D(const Vector3D& other);
  Vector3D(const Point3D& p0, const Point3D& p1);
  explicit Vector3D(const Point3D& p);

  Vector3D& operator=(const Vector3D& other);

  //! Scalar(Dot) product with the Vector3D 'other'
  double Scalar(const Vector3D& other) const;

  //! Cross product with the Vector3D 'other'
  Vector3D Cross(const Vector3D& other) const;

  //! Checks if the vector is zero.
  //! It means that all its coordinates are equal to 0
  bool IsZero() const;
};

Vector3D operator+(const Vector3D& leftV, const Vector3D& rightV);
Vector3D operator-(const Vector3D& leftV, const Vector3D& rightV);
Vector3D operator-(const Point3D& lastP, const Point3D& firstP);
Vector3D operator*(const Vector3D& vector, double number);
Vector3D operator*(double number, const Vector3D& vector);
Vector3D operator+(const Vector3D& vector, const Point3D& point);
Vector3D operator+(const Point3D& point, const Vector3D& vector);
Vector3D operator-(const Vector3D& vector, const Point3D& point);
Vector3D operator-(const Point3D& point, const Vector3D& vector);

double Scalar(const Vector3D& leftV, const Vector3D& rightV);
Vector3D Cross(const Vector3D& leftV, const Vector3D& rightV);

inline double Vector3D::Scalar(const Vector3D& other) const {
  return x * other.x + y * other.y + z * other.z;
}

inline Vector3D Vector3D::Cross(const Vector3D& other) const {
  double newX = y * other.z - z * other.y;
  double newY = z * other.x - x * other.z;
  double newZ = x * other.y - y * other.x;
  return Vector3D(newX, newY, newZ);
}

}  // namespace ti
