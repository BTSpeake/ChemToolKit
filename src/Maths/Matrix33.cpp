#include "Maths/Matrix33.h"

using namespace ctkMaths;

Matrix33::Matrix33()
	: _v00(0.0), _v01(0.0), _v02(0.0), _v10(0.0), _v11(0.0), _v12(0.0), _v20(0.0), _v21(0.0), _v22(0.0)
{};

Matrix33::Matrix33(double v00, double v01, double v02, double v10, double v11, double v12, double v20, double v21, double v22)
	: _v00(v00), _v01(v01), _v02(v02), _v10(v10), _v11(v11), _v12(v12), _v20(v20), _v21(v21), _v22(v22)
{}

Matrix33::~Matrix33() {}

Matrix33::Matrix33(const Matrix33& rhs) 
	: _v00(rhs[0]), _v01(rhs[1]), _v02(rhs[2]), _v10(rhs[3]), _v11(rhs[4]), _v12(rhs[5]), _v20(rhs[6]), _v21(rhs[7]), _v22(rhs[8])
{}

Matrix33& Matrix33::operator=(const Matrix33& rhs) {
	_v00 = rhs[0]; _v01 = rhs[1]; _v02 =rhs[2]; _v10 = rhs[3]; _v11 = rhs[4]; _v12 = rhs[5]; _v20 = rhs[6]; _v21 = rhs[7]; _v22 = rhs[8];
	return *this;
}

// Math Operations 

Matrix33& Matrix33::operator+=(const Matrix33& rhs) {
	_v00 += rhs[0];
	_v01 += rhs[1];
	_v02 += rhs[2];
	_v10 += rhs[3];
	_v11 += rhs[4];
	_v12 += rhs[5];
	_v20 += rhs[6];
	_v21 += rhs[7];
	_v22 += rhs[8];
	return *this;
}

Matrix33& Matrix33::operator-=(const Matrix33& rhs) {
	_v00 -= rhs[0];
	_v01 -= rhs[1];
	_v02 -= rhs[2];
	_v10 -= rhs[3];
	_v11 -= rhs[4];
	_v12 -= rhs[5];
	_v20 -= rhs[6];
	_v21 -= rhs[7];
	_v22 -= rhs[8];
	return *this;
}

Matrix33& Matrix33::operator*=(const double& s) {
	_v00 *= s;
	_v01 *= s;
	_v02 *= s;
	_v10 *= s;
	_v11 *= s;
	_v12 *= s;
	_v20 *= s;
	_v21 *= s;
	_v22 *= s;
	return *this;
}

Matrix33& Matrix33::operator/=(const double& s) {
	_v00 /= s;
	_v01 /= s;
	_v02 /= s;
	_v10 /= s;
	_v11 /= s;
	_v12 /= s;
	_v20 /= s;
	_v21 /= s;
	_v22 /= s;
	return *this;
}

Vector3 Matrix33::operator*(const Vector3& v) const {
	double x, y, z;

	x = (_v00 * v[0]) + (_v01 * v[1]) + (_v02 * v[2]);
	y = (_v10 * v[0]) + (_v11 * v[1]) + (_v12 * v[2]);
	z = (_v20 * v[0]) + (_v21 * v[1]) + (_v22 * v[2]);

	return Vector3(x, y, z);
}

Matrix33 Matrix33::operator*(const Matrix33& rhs) const {
	return Matrix33(
		(_v00 * rhs[0]) + (_v01 * rhs[3]) + (_v02 * rhs[6]),
		(_v00 * rhs[1]) + (_v01 * rhs[4]) + (_v02 * rhs[7]),
		(_v00 * rhs[2]) + (_v01 * rhs[5]) + (_v02 * rhs[8]),

		(_v10 * rhs[0]) + (_v11 * rhs[3]) + (_v12 * rhs[6]),
		(_v10 * rhs[1]) + (_v11 * rhs[4]) + (_v12 * rhs[7]),
		(_v10 * rhs[2]) + (_v11 * rhs[5]) + (_v12 * rhs[8]),

		(_v20 * rhs[0]) + (_v21 * rhs[3]) + (_v22 * rhs[6]),
		(_v20 * rhs[1]) + (_v21 * rhs[4]) + (_v22 * rhs[7]),
		(_v20 * rhs[2]) + (_v21 * rhs[5]) + (_v22 * rhs[8])
	);
}

// Access functions 
double Matrix33::value(int i, int j) const {
	if (i >= 0 && i < 3 && j >= 0 && j < 3) {
		return operator[]((3 * i) + j);
	}
	else {
		return 0.0;
	}
}

double Matrix33::operator[](int i) const {

	switch (i) {
	case 0:
		return _v00;
	case 1:
		return _v01;
	case 2:
		return _v02;
	case 3:
		return _v10;
	case 4:
		return _v11; 
	case 5:
		return _v12; 
	case 6:
		return _v20;
	case 7:
		return _v21;
	case 8:
		return _v22;
	default:
		return 0.0;
	}
}

Matrix33 ctkMaths::identity33() {
	return Matrix33(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	);
}

std::ostream& operator<<(std::ostream& os, const Matrix33 & m) {
	os << "["; 
	os << "[" << m[0] << ", " << m[1] << ", " << m[2] << "]\n";
	os << " [" << m[3] << ", " << m[4] << ", " << m[5] << "]\n";
	os << " [" << m[6] << ", " << m[7] << ", " << m[8] << "]]";
	os << std::endl;
	return os;
}