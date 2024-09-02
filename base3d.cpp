#include "base3d.h"
#include "global_constants.h"

#include <cmath>

namespace ti {

Base3D::Base3D() : x(0), y(0), z(0) {}

Base3D::Base3D(double inX, double inY, double inZ) : x(inX), y(inY), z(inZ) {}

double Base3D::X() const { return x; }

double Base3D::Y() const { return y; }

double Base3D::Z() const { return z; }

bool Base3D::operator==(const Base3D& other) const {
  if (std::abs(x - other.x) > TOLERANCE) {
    return false;
  }
  if (std::abs(y - other.y) > TOLERANCE) {
    return false;
  }
  if (std::abs(z - other.z) > TOLERANCE) {
    return false;
  }
  return true;
}

bool Base3D::operator!=(const Base3D& other) const { return !(*this == other); }

}  // namespace ti
