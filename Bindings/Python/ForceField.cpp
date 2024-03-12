#include "ForceField/UFF.h"
#include "Data/Molecule.h"
#include <pybind11/pybind11.h>

PYBIND11_MODULE(ctkPyForceField, m) {

	pybind11::module_::import("ctkPyDataObjs");

	pybind11::class_<UFF>(m, "UFF")
		.def(pybind11::init<ctkData::Molecule&>())
		.def("setupTerms", &UFF::setupTerms)
		.def("run", &UFF::runSteps)
		.def("calculateEnergy", &UFF::calculateEnergy)
		.def("energy", &UFF::energy)
		;

}