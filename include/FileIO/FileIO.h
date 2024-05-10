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
		virtual void read(ctkData::Model& mol) const = 0;
		virtual void write(const ctkData::Model& mol) const = 0;;

	protected:
		std::filesystem::path _fname;

	};

}