#pragma once
#include "FileIO/FileIO.h"

namespace ctkIO {

	class FileIO_XYZ : public FileIO {
	public:
		bool read(ctkData::Model& mol);
		bool write(const ctkData::Model& mol);

	};

}

