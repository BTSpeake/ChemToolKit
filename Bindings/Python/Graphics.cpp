#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include "GUI/RenderWindow.h"

PYBIND11_MODULE(ctkPyGraphics, m) {
	using namespace ctkGraphics;

	pybind11::module_::import("ctkPyDataObjs");

	pybind11::class_<RenderWindow>(m, "RenderWindow")
		.def(pybind11::init<>())
		.def("setModel", pybind11::overload_cast<const ctkData::Model&>(&RenderWindow::setModel))
		.def("updateRendering", &RenderWindow::updateRendering)
		.def("render", &RenderWindow::render)
		.def("resize", &RenderWindow::resize)
		.def("finalise", &RenderWindow::finalise)
		;
}