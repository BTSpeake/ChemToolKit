#pragma once
#include "FileIO/FileIO.h"

namespace ctkIO {

	class FileIO_XYZ : public FileIO {
	public:
		void read(ctkData::Molecule& mol) const;
		void write(const ctkData::Molecule& mol) const;

	};

}

