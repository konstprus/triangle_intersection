#include <gtest/gtest.h>
#include <point3d.h>
#include <vector3d.h>
#include <segment3d.h>
#include <triangle3d.h>

TEST(Test_geometry, points_equality) { 
  ti::Point3D p1(4.0, 3.654, 91.0);
  ti::Point3D p2(2.0, -432.5, 2.032);
  ti::Point3D p3 = p1;

  // Check == operator
  ASSERT_NE(p1, p2);
  ASSERT_EQ(p1, p3);
}

TEST(Test_geometry, vectors_scalar_product) {
  ti::Vector3D v0;  // Zero vector
  ti::Vector3D v1(4.0, -1.0, 2.3);
  ti::Vector3D v2(1.0, 2.0, 0.0);
  ti::Vector3D v3(-4.0, 2.0, 10.0);  // Perpendicular to v2

  ASSERT_DOUBLE_EQ(ti::Scalar(v0, v1), 0.0);
  ASSERT_DOUBLE_EQ(ti::Scalar(v1, v2), 2.0);
  ASSERT_DOUBLE_EQ(ti::Scalar(v2, v3), 0.0);
}

TEST(Test_geometry, vectors_cross_product) {
  //main axis
  ti::Vector3D vX(1.0, 0.0, 0.0);
  ti::Vector3D vY(0.0, 1.0, 0.0);
  ti::Vector3D vZ(0.0, 0.0, 1.0);
  ASSERT_EQ(ti::Cross(vX, vY), vZ);

  ti::Vector3D v0;  // Zero vector
  ti::Vector3D v1(4.0, -1.0, 2.3);
  ti::Vector3D v2(1.0, 2.0, 0.0);
  ti::Vector3D v4(-8.0, 2.0, -4.6);  // Parallel to v1

  ASSERT_EQ(ti::Cross(v1, v4), v0);  // Zero vector
  ASSERT_EQ(ti::Cross(v2, v4), ti::Vector3D(-9.2, 4.6, 18.0));
}

TEST(Test_geometry, vectors_plus_minus_product_operations) {
  ti::Vector3D v1(4.0, -1.0, 2.3);
  ti::Vector3D v2(1.0, 2.0, 0.0);
  ti::Vector3D v3(-4.0, 2.0, 10.0); // Perpendicular to v2
  ti::Vector3D v4(-8.0, 2.0, -4.6); // Parallel to v1

  ASSERT_EQ(v1 + v2, ti::Vector3D(5.0, 1.0, 2.3));
  ASSERT_EQ(v1 - v2, ti::Vector3D(3.0, -3.0, 2.3));
  ASSERT_EQ(v1 * 4, ti::Vector3D(16.0, -4.0, 9.2));
  ASSERT_EQ(4 * v1, ti::Vector3D(16.0, -4.0, 9.2));
  ASSERT_EQ(v1 + ti::Point3D(1.0, 2.0, 3.0), ti::Vector3D(5.0, 1.0, 5.3));
  ASSERT_EQ(v1 - ti::Point3D(1.0, 2.0, 3.0), ti::Vector3D(3.0, -3.0, -0.7));
}

TEST(Test_geometry, test_segments) { 
  ti::Segment3D s0;
  ti::Segment3D s1({2.0, 1.0, -1.0}, {1.0, 4.0, 8.0});

  ti::Vector3D v0;  // Zero vector
  ASSERT_EQ(s0.DirectionVector(), v0);
  ASSERT_EQ(s1.DirectionVector(), ti::Vector3D(-1.0, 3.0, 9.0));
}

TEST(Test_geometry, test_triangles) { 
  ti::Point3D p0(0.0, 0.0, 0.0);
  ti::Point3D p1(1.0, 2.0, 2.5);
  ti::Point3D p2(-1.0, -2.0, -2.5);
  ti::Point3D p4(4.0, -2.0, 2.5);

  ti::Triangle3D tr0(p0, p1, p2);  // Degenerated
  ti::Triangle3D tr1(p0, p1, p0);  // Degenerated
  ti::Triangle3D tr2(p0, p1, p4);  // Not Degenerated

  ASSERT_TRUE(tr0.IsDenerated());
  ASSERT_TRUE(tr1.IsDenerated());
  ASSERT_FALSE(tr2.IsDenerated());

}