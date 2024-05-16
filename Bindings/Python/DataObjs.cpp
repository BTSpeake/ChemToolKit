#include "Data/Model.h"
#include "Data/Atom.h"
#include "Data/Surface.h"
#include "Data/VolumeData.h"
#include <pybind11/pybind11.h>

using namespace ctkData;

PYBIND11_MODULE(ctkPyDataObjs, m) {

	pybind11::module_::import("ctkPyMaths");

	pybind11::class_<Model>(m, "Model")
		.def(pybind11::init<>())
		.def("__repr__", &Model::toString)

		.def("nAtoms", &Model::nAtoms, "Returns the total number of atoms contained within the model.")
		.def("nBonds", &Model::nBonds, "Returns the total number of bonds contained within the model.")
		.def_property("charge", &Model::getCharge, &Model::setCharge)
		.def_property("spinProjection", &Model::getSpinProjection, &Model::setSpinProjection)
		.def_property("multiplicity", &Model::getMultiplicity, &Model::setMultiplicity)
		.def("addAtom", pybind11::overload_cast<int, double, double, double>(&Model::addAtom))
		.def("addAtom", pybind11::overload_cast<std::string, double, double, double>(&Model::addAtom))
		.def("addBond", &Model::addBond)
		.def("calculateBonding", &Model::calculateBonding)
		.def("calculateCoM", &Model::calculateCoM)
		.def("centreOnOrigin", &Model::centreOnOrigin)
		.def("clearAtoms", &Model::clearAtoms)
		.def("clearBonds", &Model::clearBonds)
		.def("getAtom", &Model::getAtom, pybind11::return_value_policy::reference)
		;

	pybind11::class_<Atom>(m, "Atom")
		.def(pybind11::init<int, double, double, double>())
		.def(pybind11::init<std::string, double, double, double>())
		.def(pybind11::init<const Atom&>())

		.def("__repr__", &Atom::toString)

		
		.def_property("atomicNumber", &Atom::getAtomicNumber, &Atom::setAtomicNumber)
		.def("coordinates", pybind11::overload_cast<>(&Atom::getPosition))
		.def("symbol", &Atom::getSymbol)
		.def("coordination", &Atom::coordination)
		.def("isAromatic", pybind11::overload_cast<>(&Atom::isAromatic, pybind11::const_))
		.def("isAmide", pybind11::overload_cast<>(&Atom::isAmide, pybind11::const_))
		.def("getCovRadii", &Atom::getCovalentRadii)
		;

	pybind11::class_<VolumeData>(m, "VolumeData")
		.def(pybind11::init<int*>())
		.def("addNewValue", pybind11::overload_cast<const double, const double, const double, const double>(&VolumeData::addNewValue))
		.def("addNewValue", pybind11::overload_cast<const double>(&VolumeData::addNewValue))
		.def("setValue", pybind11::overload_cast<const int, const double, const double, const double, const double>(&VolumeData::setValue))
		.def("setValue", pybind11::overload_cast<const int, const double>(&VolumeData::setValue))
		.def("getGridX", &VolumeData::getGridX)
		.def("getGridY", &VolumeData::getGridY)
		.def("getGridZ", &VolumeData::getGridZ)
		;

	pybind11::class_<Surface>(m, "Surface")
		.def(pybind11::init<const VolumeData&>())
		.def("MarchingCubes", &Surface::MarchingCubes)
		.def("laplcianSmoothing", &Surface::laplacianSmoothing)
		.def("calculateVertexNormals", &Surface::calculateVertexNormals)
		.def("subdivide", &Surface::subdivide)
		.def("nFaces", &Surface::nFaces)
		;
}