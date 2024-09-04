#include "vector3d.h"

#include <cmath>

namespace ti {

Vector3D::Vector3D() : Base3D() {}

Vector3D::Vector3D(double x, double y, double z) : Base3D(x, y, z) {}

Vector3D::Vector3D(const Vector3D& other) : Base3D(other.x, other.y, other.z) {}

Vector3D::Vector3D(const Point3D& p0, const Point3D& p1)
    : Base3D(p1.X() - p0.X(), p1.Y() - p0.Y(), p1.Z() - p0.Z()) {}

Vector3D::Vector3D(const Point3D& p) : Base3D(p.X(), p.Y(), p.Z()) {}

Vector3D& Vector3D::operator=(const Vector3D& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  return *this;
}

bool Vector3D::IsZero() const { return *this == Vector3D(); }

Vector3D operator+(const Vector3D& leftV, const Vector3D& rightV) {
  return Vector3D(leftV.X() + rightV.X(), 
                  leftV.Y() + rightV.Y(),
                  leftV.Z() + rightV.Z());
}

Vector3D operator-(const Vector3D& leftV, const Vector3D& rightV) {
  return Vector3D(leftV.X() - rightV.X(), 
                  leftV.Y() - rightV.Y(),
                  leftV.Z() - rightV.Z());
}

Vector3D operator-(const Point3D& lastP, const Point3D& firstP) {
  return Vector3D(firstP, lastP);
}

Vector3D operator*(const Vector3D& vector, double number) {
  return Vector3D(vector.X() * number, 
                  vector.Y() * number,
                  vector.Z() * number);
}

Vector3D operator*(double number, const Vector3D& vector) {
  return vector * number;
}

Vector3D operator+(const Vector3D& vector, const Point3D& point) {
  return vector + Vector3D(point);
}

Vector3D operator+(const Point3D& point, const Vector3D& vector) {
  return vector + point;
}

Vector3D operator-(const Vector3D& vector, const Point3D& point) {
  return vector - Vector3D(point);
}

Vector3D operator-(const Point3D& point, const Vector3D& vector) {
  return Vector3D(point) - vector;
}

double Scalar(const Vector3D& leftV, const Vector3D& rightV) {
  return leftV.Scalar(rightV);
}

Vector3D Cross(const Vector3D& leftV, const Vector3D& rightV) {
  return leftV.Cross(rightV);
}

}  // namespace ti
