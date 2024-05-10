#pragma once
#include "FileIO/FileIO.h"

namespace ctkIO {

	class FileIO_PDB : public FileIO {
	public:
		void read(ctkData::Model& mol) const;
		void write(const ctkData::Model& mol) const;
	};

}