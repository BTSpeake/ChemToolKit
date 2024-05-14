#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include "Data/Model.h"

namespace ctkIO {

	class FileIO {

	public:
		void setFileName(std::filesystem::path fname) {
			_fname = fname;
		}
		virtual bool read(ctkData::Model& mol) = 0;
		virtual bool write(const ctkData::Model& mol) = 0;
		const std::string& getErrorMessage() const { return _error; };

	protected:
		std::filesystem::path _fname;
		std::string _error;
	};

}