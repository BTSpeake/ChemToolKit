#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "Data/Molecule.h"

using ctkData::Molecule;

class FileIO {

public:
	void setFileName(std::filesystem::path fname) {
		_fname = fname;
	}
	virtual void read(Molecule& mol) const = 0;
	virtual void write(const Molecule& mol) const = 0;;

protected:
	std::filesystem::path _fname;

};