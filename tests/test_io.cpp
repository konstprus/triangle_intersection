#include <gtest/gtest.h>
#include <geometry_io.h>
#include <point3d.h>
#include <triangle3d.h>
#include <string>
#include <iostream>

TEST(Test_io, read_points) { 
  std::stringstream str;
  str << "2.0 1 -43";

  ti::Point3D p;
  str >> p;
  ASSERT_EQ(p, ti::Point3D(2.0, 1.0, -43.0));
}

TEST(Test_io, write_points) {
  ti::Point3D p1(32.0321, -43.0421, 0.0);
  std::stringstream out_str;
  out_str << p1;
  ASSERT_STREQ(out_str.str().c_str(), "32.0321 -43.0421 0");
}

TEST(Test_io, read_triangles) {
  std::stringstream str;
  str << "2.0 1 -43 3 6 7 -1.0021 0 55";

  ti::Triangle3D tr;
  str >> tr;
  ASSERT_EQ(tr.P0(), ti::Point3D(2.0, 1.0, -43.0));
  ASSERT_EQ(tr.P1(), ti::Point3D(3.0, 6.0, 7.0));
  ASSERT_EQ(tr.P2(), ti::Point3D(-1.0021, 0.0, 55.0));
}

TEST(Test_io, write_triangles) {
  ti::Triangle3D tr2({0, 0, 0}, {1, -432, 12}, {3, 0, -3});
  std::stringstream out_str;
  out_str << tr2;
  ASSERT_STREQ(out_str.str().c_str(), "0 0 0 1 -432 12 3 0 -3");
}