#pragma once 
#include "FileIO/FileIO.h"

namespace ctkIO {


	class FileIO_Mol2 : public FileIO {
	public:
		void read(ctkData::Molecule& mol) const;
		void write(const ctkData::Molecule& mol) const;
	};

}