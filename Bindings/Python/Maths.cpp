#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include "Maths/Vector3.h"
#include "Maths/Matrix33.h"

using namespace ctkMaths;

//namespace ctkPyMaths{
//	void vectorSetItem()
//}

PYBIND11_MODULE(ctkPyMaths, m) {

	pybind11::class_<Vector3>(m, "Vector3")
		.def(pybind11::init<>())
		.def(pybind11::init<double, double, double>())
		.def(pybind11::init<const Vector3&>())
		//.def operator= ???
		.def("__assign__", &Vector3::operator=)
		.def("__getitem__", &Vector3::operator[])
		.def("__repr__", &Vector3::toString)


		// Math Operations 
		.def(pybind11::self += pybind11::self)
		.def(pybind11::self -= pybind11::self)
		.def(pybind11::self *= float())
		.def(pybind11::self /= float())
		.def(pybind11::self + pybind11::self)
		.def(pybind11::self - pybind11::self)
		.def(pybind11::self * float())
		.def(float() * pybind11::self)
		.def(pybind11::self / float())
		//.def(pybind11::self * pybind11::self)

		.def("normal", &Vector3::normal)
		.def("normalise", &Vector3::normalise)
		;

	//m.def("dotProduct", &dot);

	pybind11::class_<Matrix33>(m, "Matrix33")
		.def(pybind11::init<>())
		.def(pybind11::init<double, double, double, double, double, double, double, double, double>())
		.def(pybind11::init<const Matrix33&>())
		.def("__assign__", &Matrix33::operator=)
		.def("__getitem__", &Matrix33::operator[])
		.def("__repr__", &Matrix33::toString)

		//Math operations 


		;
}

