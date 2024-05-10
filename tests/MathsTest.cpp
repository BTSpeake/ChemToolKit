#include <gtest/gtest.h>
#include "Maths/Vector3.h"
#include "Maths/Matrix33.h"

TEST(MathsTest, Vector3) {

	using namespace ctkMaths;

	double errThr = 1e-4; // -> Increase this (requries getting better precision for the check values)

	Vector3 v1(1, 2, 3);
	Vector3 v2(2, 3, 4);
	Vector3 v3(v2);

	EXPECT_EQ(v1[0], 1.0);
	EXPECT_EQ(v1[1], 2.0);
	EXPECT_EQ(v1[2], 3.0);

	EXPECT_EQ(dot(v1, v2), 20);
	EXPECT_TRUE(abs(v1.normal() - 3.74166) < errThr);

	v1 *= 4;
	EXPECT_EQ(v1[0], 4);
	v1.normalise();
	EXPECT_TRUE(abs(v1[0] - 0.267261) < errThr);
	EXPECT_TRUE(abs(v1[1] - 0.534522) < errThr);
	EXPECT_TRUE(abs(v1[2] - 0.801784) < errThr);

	v3 += v2;
	Vector3 v4 = v3 - v2;
	EXPECT_EQ(v4[0], v2[0]);
	EXPECT_EQ(v4[1], v2[1]);
	EXPECT_EQ(v4[2], v2[2]);

}

TEST(MathsTest, Matrix33) {

	using namespace ctkMaths;

	Matrix33 eye = identity33();
	EXPECT_EQ(eye[0], 1.0);
	EXPECT_EQ(eye[1], 0.0);
	EXPECT_EQ(eye[4], 1.0);
	EXPECT_EQ(eye.value(2, 2), 1.0);

	Vector3 v2(2, 3, 4);
	Vector3 iv3 = eye * v2;
	EXPECT_EQ(iv3[0], 2.0);
	EXPECT_EQ(iv3[1], 3.0);
	EXPECT_EQ(iv3[2], 4.0);

	Matrix33 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);
	EXPECT_EQ(m1[0], 1.0);
	EXPECT_EQ(m1.value(2, 2), 9.0);

	Matrix33 im1 = eye * m1;

	EXPECT_EQ(im1[0], 1.0);
	EXPECT_EQ(im1[3], 4.0);
	EXPECT_EQ(im1.value(1, 2), 6.0);
	EXPECT_EQ(im1.value(2, 2), 9.0);

	m1 *= 2;
	EXPECT_EQ(m1[0], 2.0);
	EXPECT_EQ(m1.value(2, 2), 18.0);

}
