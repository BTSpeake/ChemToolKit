#pragma once 
#include "FileIO/FileIO.h"

class FileIO_Mol2 : public FileIO {
public:
	void read(Molecule& mol) const;
	void write(const Molecule& mol) const;
};