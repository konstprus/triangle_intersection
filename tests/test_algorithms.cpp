#include <gtest/gtest.h>
#include <intersection_algorithms.h>
#include <segment3d.h>
#include <triangle3d.h>

TEST(Test_algorithms, point_point) { 
  ti::Point3D p1;
  ti::Point3D p2(1, 2, 5);
  ti::Point3D p3 = p2;
  ASSERT_TRUE(ti::IsIntersect(p2, p3));
  ASSERT_FALSE(ti::IsIntersect(p1, p3));
}

TEST(Test_algorithms, point_segment) {
  ti::Point3D p0;
  ti::Segment3D s1({1, 2, 3}, {4, 6, 9});
  ti::Point3D p1(2, 3, 4);

  ASSERT_FALSE(ti::IsIntersect(p0, s1));
  ASSERT_TRUE(ti::IsIntersect(p1, s1));
}

TEST(Test_algorithms, segment_segment_parallel_no_interserction) {
  ti::Segment3D s1({0, 0, 0}, {1, 1, 1});
  ti::Segment3D s2({1, 1, 1}, {1, 1, 2});
  ASSERT_FALSE(ti::IsIntersect(s1, s2));
}

TEST(Test_algorithms, segment_segment_skew_no_interserction) {
  ti::Segment3D s1({0, 0, 0}, {1, 1, 1});
  ti::Segment3D s2({0, 0, 1}, {-1, -1, 2});
  ASSERT_FALSE(ti::IsIntersect(s1, s2));
}

TEST(Test_algorithms, segment_segment_same_line_no_interserction) {
  ti::Segment3D s1({0, 0, 0}, {1, 1, 1});
  ti::Segment3D s2({2, 2, 2}, {4, 4, 4});
  ASSERT_FALSE(ti::IsIntersect(s1, s2));
}

TEST(Test_algorithms, segment_segment_interserction) {
  ti::Segment3D s1({0, 0, 0}, {2, 2, 2});
  ti::Segment3D s2({-2, 0, 0}, {4, 2, 2});
  ASSERT_FALSE(ti::IsIntersect(s1, s2));
}

TEST(Test_algorithms, segment_triangle_parallel_no_intersection) {
  ti::Triangle3D tr({0, 0, 0}, {0, 1, 3}, {0, 3, 1});
  ti::Segment3D s1({1, 0, 0}, {1, 2, 5});
  ASSERT_FALSE(ti::IsIntersect(s1, tr));
}

TEST(Test_algorithms, segment_triangle_perpendicular_no_intersection) {
  ti::Triangle3D tr({0, 0, 0}, {0, 1, 3}, {0, 3, 1});
  ti::Segment3D s1({1, -1, -1}, {-1, -1, -1});
  ASSERT_FALSE(ti::IsIntersect(s1, tr));
}

TEST(Test_algorithms, segment_triangle_same_plane_no_intersection) {
  ti::Triangle3D tr({0, 0, 0}, {0, 1, 3}, {0, 3, 1});
  ti::Segment3D s1({0, -4, 1}, {0, -3, -1});
  ASSERT_FALSE(ti::IsIntersect(s1, tr));
}

TEST(Test_algorithms, segment_triangle_intersection) {
  ti::Triangle3D tr({0, 0, 0}, {0, 1, 3}, {0, 3, 1});
  ti::Segment3D s1({1, 1, 1}, {-2, 2, 1});
  ASSERT_TRUE(ti::IsIntersect(s1, tr));
}

TEST(Test_algorithms, triangle_triangle_1) {
  ti::Triangle3D tr1({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
  ti::Triangle3D tr2({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
  ASSERT_TRUE(ti::IsIntersect(tr1, tr2));
}

TEST(Test_algorithms, triangle_triangle_2) {
  ti::Triangle3D tr1({1, 0, 1}, {2, 0, 1}, {1, 1, 1});
  ti::Triangle3D tr2({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
  ASSERT_FALSE(ti::IsIntersect(tr1, tr2));
}

TEST(Test_algorithms, triangle_triangle_3) {
  ti::Triangle3D tr1({0, 0, 0}, {1, 0, 0}, {0, 1, 0});
  ti::Triangle3D tr2({0, 0, -1}, {1, 0, 1}, {0, 1, 1});
  ASSERT_TRUE(ti::IsIntersect(tr1, tr2));
}

TEST(Test_algorithms, triangle_triangle_4) {
  ti::Triangle3D tr1({0, 0, 0}, {0, 0, 5}, {5, 5, 5});
  ti::Triangle3D tr2({5, 0, 0}, {5, 0, 5}, {0, 5, 5});
  ASSERT_TRUE(ti::IsIntersect(tr1, tr2));
}

TEST(Test_algorithms, triangle_triangle_5) {
  ti::Triangle3D tr1({0, 0, 0}, {10, 0, 0}, {0, 10, 0});
  ti::Triangle3D tr2({1, 1, 0}, {1, 1, 0}, {1, 1, 0});
  ASSERT_TRUE(ti::IsIntersect(tr1, tr2));
}

TEST(Test_algorithms, triangle_triangle_5b) {
  ti::Triangle3D tr1({0, 0, 0}, {10, 0, 0}, {0, 10, 0});
  ti::Triangle3D tr2({1, 1, 0}, {1, 1, 0}, {1, 1, 0});
  ASSERT_TRUE(ti::IsIntersect(tr2, tr1));
}

TEST(Test_algorithms, triangle_triangle_one_is_inside_another) {
  ti::Triangle3D tr1({0, 0, 0}, {10, 0, 0}, {0, 10, 0});
  ti::Triangle3D tr2({1, 1, 0}, {9, 1, 0}, {1, 9, 0});
  ASSERT_TRUE(ti::IsIntersect(tr2, tr1));
}
