#include "Maths/Vector3.h"
#include <cmath>

using namespace ctkMaths;

// Constructors
Vector3::Vector3() : _x(0.0), _y(0.0), _z(0.0) {}

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

// Destructor 
Vector3::~Vector3() {}

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

void Vector3::setX(double x) { _x = x; };
void Vector3::setY(double y) { _y = y; };
void Vector3::setZ(double z) { _z = z; };

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

double Vector3::operator*(const Vector3& rhs) { return dot(*this, rhs); }

double Vector3::normal() const {
	//double norm = dot(*this, *this); 
	double norm = (_x * _x) + (_y * _y) + (_z * _z);
	return sqrt(norm);
}

void Vector3::normalise() { *this /= normal(); }

std::string Vector3::toString() const {
	std::string s = "[" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + "]";
	return s;
}

Vector3 ctkMaths::operator*(double s, const Vector3& vec) {
	return vec * s;
}
//
double ctkMaths::dot(const Vector3& v1, const Vector3& v2) {
	return (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]);
};


std::ostream& operator<<(std::ostream& os, const Vector3& v) {
	os << v.toString();
	return os;
}