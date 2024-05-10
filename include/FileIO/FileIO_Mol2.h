#pragma once 
#include "FileIO/FileIO.h"

namespace ctkIO {


	class FileIO_Mol2 : public FileIO {
	public:
		void read(ctkData::Model& mol) const;
		void write(const ctkData::Model& mol) const;
	};

}