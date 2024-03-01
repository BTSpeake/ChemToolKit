#pragma once

#ifdef _WIN32
#ifdef ctkMaths_EXPORTS
#define VECTOR3_API __declspec(dllexport)
#else
#define VECTOR3_API __declspec(dllimport)
#endif // VECTOR3_EXPORTS 
#else
#define VECTOR3_API
#endif //_WIN32 

#include <iostream>
#include <string>

namespace ctkMaths {


	class VECTOR3_API Vector3 {
	public:
		Vector3();
		Vector3(double x, double y, double z);
		Vector3(const Vector3& vec);
		~Vector3();

		Vector3& operator=(const Vector3& vec);

		// Access functions 
		double operator[](int i) const;

		void setX(double x);
		void setY(double y);
		void setZ(double z);

		// Math operations 
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const double rhs);
		Vector3& operator/=(const double rhs);
		Vector3 operator+(const Vector3& rhs) const; // I think these could be more efficient
		Vector3 operator-(const Vector3& rhs) const;
		Vector3 operator*(const double rhs) const;
		Vector3 operator/(const double rhs) const;
		friend VECTOR3_API Vector3 operator*(double s, const Vector3& vec);
		double operator*(const Vector3& rhs);

		double normal() const;
		void normalise();

		std::string toString() const;

	private:
		double _x;
		double _y;
		double _z;
	};

	//// Create a friend function to allow abitrary ordering of components
	VECTOR3_API Vector3 operator*(double s, const Vector3& vec);

	VECTOR3_API double dot(const Vector3& v1, const Vector3& v2);

}

VECTOR3_API std::ostream& operator<<(std::ostream& os, const ctkMaths::Vector3& v);