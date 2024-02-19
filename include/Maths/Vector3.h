#pragma once

class Vector3 {
public:
	Vector3() : _x(0.0), _y(0.0), _z(0.0) {};
	Vector3(double x, double y, double z);
	Vector3(const Vector3& vec);
	~Vector3() = default;

	Vector3& operator=(const Vector3& vec);

	// Access functions 
	double operator[](int i) const;

	// Math operations 
	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(const double rhs);
	Vector3& operator/=(const double rhs);
	Vector3 operator+(const Vector3& rhs) const; // I think these could be more efficient
	Vector3 operator-(const Vector3& rhs) const;
	Vector3 operator*(const double rhs) const;
	Vector3 operator/(const double rhs) const;
	friend Vector3 operator*(const double s, const Vector3& vec);
	friend double dot(const Vector3& v1, const Vector3& v2);

	double normal() const;
	void normalise() { *this /= normal(); }

private:
	double _x;
	double _y;
	double _z;
};

// Create a friend function to allow abitrary ordering of components
inline Vector3 operator*(const double s, const Vector3& vec) {
	return (vec * s);
}

// Add this to a namespace?? 
// Does is need to be a friend and can it be in a seperate file??
double dot(const Vector3& v1, const Vector3& v2);


