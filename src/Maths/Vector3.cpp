#include "Maths/Vector3.h"
#include <cmath>

Vector3::Vector3(double x, double y, double z)
	: _x(x), _y(y), _z(z) {
}

// Copy constructor 
Vector3::Vector3(const Vector3& vec) {
	_x = vec[0];
	_y = vec[1];
	_z = vec[2];
}

// Assignement operator 
Vector3& Vector3::operator=(const Vector3& vec) {
	Vector3 v(vec);
	return v;
}

double Vector3::operator[](int i) const {
	switch (i) {
	case 0:
		return _x;
	case 1:
		return _y;
	case 2:
		return _z;
	default:
		return 0.0; // TODO -> This should throw an error 
	}
}

Vector3& Vector3::operator+=(const Vector3& rhs) {
	_x += rhs[0];
	_y += rhs[1];
	_z += rhs[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs) {
	_x -= rhs[0];
	_y -= rhs[1];
	_z -= rhs[2];
	return *this;
}

Vector3& Vector3::operator*=(const double rhs) {
	_x *= rhs;
	_y *= rhs;
	_z *= rhs;
	return *this;
}

Vector3& Vector3::operator/=(const double rhs) {
	_x /= rhs;
	_y /= rhs;
	_z /= rhs;
	return *this;
}

Vector3 Vector3::operator+(const Vector3& rhs) const {
	Vector3 v(*this);
	return v += rhs;
}
Vector3 Vector3::operator-(const Vector3& rhs) const {
	Vector3 v(*this);
	return v -= rhs;
}

Vector3 Vector3::operator*(const double rhs) const {
	Vector3 v(*this);
	return v *= rhs;
}

Vector3 Vector3::operator/(const double rhs) const {
	Vector3 v(*this);
	return v /= rhs;
}

double Vector3::normal() const {
	double norm = dot(*this, *this);
	return sqrt(norm);
}

// Add this to a namespace?? 
// Does is need to be a friend and can it be in a seperate file??
double dot(const Vector3& v1, const Vector3& v2) {
	return (v1._x * v2._x) + (v1._y * v2._y) + (v1._z * v2._z);
}