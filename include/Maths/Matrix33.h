#pragma once 

#include "Maths/Vector3.h"

namespace ctkMaths {

	class Matrix33 {
	public:
		Matrix33()
			: _v00(0.0), _v01(0.0), _v02(0.0), _v10(0.0), _v11(0.0), _v12(0.0), _v20(0.0), _v21(0.0), _v22(0.0)
		{};
		~Matrix33() = default;

		// custom constructors 
		Matrix33(double v00, double v01, double v02, double v10, double v11, double v12, double v20, double v21, double v22)
			: _v00(v00), _v01(v01), _v02(v02), _v10(v10), _v11(v11), _v12(v12), _v20(v20), _v21(v21), _v22(v22)
		{};

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
		double value(int i, int j) const {
			return operator[]((3 * i) + j);
		}
		double operator[](int i) const;

	private:
		double _v00, _v01, _v02;
		double _v10, _v11, _v12;
		double _v20, _v21, _v22;
	};

	inline Matrix33 identity33() {
		return Matrix33(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0
		);
	}

}