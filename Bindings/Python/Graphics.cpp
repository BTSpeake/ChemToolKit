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
		.def("setBackground", &RenderWindow::setBackground)
		.def("showAxes", &RenderWindow::showAxes)
		.def("normaliseCamera", &RenderWindow::normaliseCamera)
		.def("setDefaultCamera", &RenderWindow::setDefaultCamera)
		.def("setWinId", &RenderWindow::setWinId)
		//.def("timerEvent", &RenderWindow::timerEvent)
		.def("setEventInformation", &RenderWindow::setEventInformation)
		.def("enterEvent", &RenderWindow::enterEvent)
		.def("leaveEvent", &RenderWindow::leaveEvent)
		.def("buttonPressEvent", &RenderWindow::buttonPressEvent)
		.def("buttonReleaseEvent", &RenderWindow::buttonReleaseEvent)
		.def("mouseMoveEvent", &RenderWindow::mouseMoveEvent)
		.def("wheelEvent", &RenderWindow::wheelEvent)
		.def("setBondColour", &RenderWindow::setBondColour)
		.def("setBondRadius", &RenderWindow::setBondRadius)
		.def("lightSwitch", &RenderWindow::lightSwitch)
		;
}