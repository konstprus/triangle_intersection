#pragma once

#include <iostream>

//! Contains operator << and >> for input/output of Point3D and Triangle3D object 
//! to/from streams

namespace ti {

class Point3D;
class Segment3D;
class Triangle3D;

}  // namespace ti

std::ostream& operator<<(std::ostream& os, const ti::Point3D& point);
std::ostream& operator<<(std::ostream& os, const ti::Triangle3D& triangle);

std::istream& operator>>(std::istream& is, ti::Point3D& point);
std::istream& operator>>(std::istream& is, ti::Triangle3D& triangle);
