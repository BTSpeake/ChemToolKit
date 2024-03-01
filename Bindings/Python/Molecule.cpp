#include "Molecule/Molecule.h"
#include "Molecule/Atom.h"
#include <pybind11/pybind11.h>


PYBIND11_MODULE(ctkPyMolecule, m) {

	pybind11::module_::import("ctkPyMaths");

	pybind11::class_<Molecule>(m, "Molecule")
		.def(pybind11::init<>())
		.def("__repr__", &Molecule::toString)

		.def("nAtoms", &Molecule::nAtoms, "Returns the total number of atoms contained within the molecule.")
		.def("nBonds", &Molecule::nBonds, "Returns the total number of bonds contained within the molecule.")
		.def_property("charge", &Molecule::getCharge, &Molecule::setCharge)
		.def_property("spinProjection", &Molecule::getSpinProjection, &Molecule::setSpinProjection)
		.def_property("multiplicity", &Molecule::getMultiplicity, &Molecule::setMultiplicity)
		.def("addAtom", pybind11::overload_cast<int, double, double, double>(&Molecule::addAtom))
		.def("addAtom", pybind11::overload_cast<std::string, double, double, double>(&Molecule::addAtom))
		.def("addBond", &Molecule::addBond)
		.def("calculateBonding", &Molecule::calculateBonding)
		.def("calculateCoM", &Molecule::calculateCoM)
		.def("centreOnOrigin", &Molecule::centreOnOrigin)
		.def("clearAtoms", &Molecule::clearAtoms)
		.def("clearBonds", &Molecule::clearBonds)
		.def("getAtom", &Molecule::getAtom, pybind11::return_value_policy::reference)
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
		.def("isAromatic", &Atom::isAromatic)
		.def("getCovRadii", &Atom::getCovalentRadii)
		;

}