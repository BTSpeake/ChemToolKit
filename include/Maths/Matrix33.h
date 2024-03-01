#pragma once 

#ifdef _WIN32
#ifdef ctkMaths_EXPORTS
#define MATRIX33_API __declspec(dllexport)
#else
#define MATRIX33_API __declspec(dllimport)
#endif // VECTOR3_EXPORTS 
#else 
#define MATRIX33_API
#endif // _WIN32 

#include <iostream>
#include <string>
#include "Maths/Vector3.h"

namespace ctkMaths {

	class MATRIX33_API Matrix33 {
	public:
		Matrix33();
		~Matrix33();

		// custom constructors 
		Matrix33(double v00, double v01, double v02, double v10, double v11, double v12, double v20, double v21, double v22);

		Matrix33(const Matrix33& rhs);
		Matrix33& operator=(const Matrix33& rhs);

		// Math Operations 
		Matrix33& operator+=(const Matrix33& rhs);
		//Matrix33 operator+(const Matrix33& rhs) const;
		Matrix33& operator-=(const Matrix33& rhs);
		//Matrix33 operator-(const Matrix33& rhs) const;
		Matrix33& operator*=(const double& s);
		//Matrix33 operator*(const double s) const;
		Matrix33& operator/=(const double& s);
		Vector3 operator*(const Vector3& v) const;
		Matrix33 operator*(const Matrix33& rhs) const;

		// Access functions 
		double value(int i, int j) const;
		double operator[](int i) const;

		std::string toString() const;

	private:
		double _v00, _v01, _v02;
		double _v10, _v11, _v12;
		double _v20, _v21, _v22;
	};

	MATRIX33_API Matrix33 identity33();
	
}

MATRIX33_API std::ostream& operator<<(std::ostream& os, const ctkMaths::Matrix33& m); // Make friend?