#include <pybind11/pybind11.h>
#include "FileIO/FileControl.h"
#include "Data/Molecule.h"

using namespace ctkIO;

PYBIND11_MODULE(ctkPyFileIO, m) {

	pybind11::module_::import("ctkPyDataObjs");

	pybind11::class_<FileControl>(m, "FileControl")
		.def(pybind11::init<>())
		.def("read", pybind11::overload_cast<std::string, ctkData::Molecule&>(&FileControl::read),
			"Overload function for reading a molecule data object from a given file. The file type will be determined from the file's extension.")
		.def("read", pybind11::overload_cast<std::string, ctkData::Molecule&, const char*>(&FileControl::read), 
			"Overload function for reading a molecule data object from a given file. The file type is specified as a paramter.")
		.def("write", pybind11::overload_cast<std::string, const ctkData::Molecule&>(&FileControl::write),
			"Overload function for writing a molecule data object to a given file. The file type will be determined from the file's extension.")
		.def("write", pybind11::overload_cast<std::string, const ctkData::Molecule&, const char*>(&FileControl::write),
			"Overload function for writing a molecule data object to a given file. The file type is specified as a paramter.")
		;
}