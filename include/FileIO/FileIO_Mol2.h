#pragma once 
#include "FileIO/FileIO.h"

namespace ctkIO {


	class FileIO_Mol2 : public FileIO {
	public:
		bool read(ctkData::Model& mol);
		bool write(const ctkData::Model& mol);
	};

}