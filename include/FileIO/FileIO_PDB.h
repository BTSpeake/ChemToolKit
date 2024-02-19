#pragma once
#include "FileIO/FileIO.h"

class FileIO_PDB : public FileIO {
public:
	void read(Molecule& mol) const;
	void write(const Molecule& mol) const;
};