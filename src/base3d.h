#pragma once

namespace ti {

//! Base3D is a base class for Point3D and Vector3D.
//! It stores three double values 'x', 'y', 'z' and
//! provides the public methods for getting their 
//! values.
//! Also it provides operator== for comparison
//! All contructors are protected to prohibite
//! the creation of object of this class. Contructors
//! are used only in derived (Point3D and Vector3D) classes
class Base3D {
 public:
  virtual ~Base3D() {}

  double X() const;
  double Y() const;
  double Z() const;

  bool operator==(const Base3D& other) const;
  bool operator!=(const Base3D& other) const;

 protected:
  Base3D();
  Base3D(double inX, double inY, double inZ);

  double x;
  double y;
  double z;
};

}  // namespace ti
