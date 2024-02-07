#pragma once
#include "FileIO.h"

class FileIO_XYZ : public FileIO {
public:
	void read(Molecule& mol) const;
	void write(const Molecule& mol) const;

};

