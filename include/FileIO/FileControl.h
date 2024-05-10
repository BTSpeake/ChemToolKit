#pragma once

#ifdef _WIN32 
#ifdef ctkFileIO_EXPORTS
#define FILECONTROL_API __declspec(dllexport)
#else
#define FILECONTROL_API __declspec(dllimport)
#endif
#else
#define FILECONTROL_API
#endif // _WIN32

#include <string>
#include <filesystem>
#include "FileIO/FileIO.h"
#include "Data/Model.h"

namespace ctkIO {

	class FILECONTROL_API FileControl {
	public:
		FileControl() = default;
		~FileControl() = default;
		FileControl(const FileControl&) = delete;
		FileControl& operator=(const FileControl&) = delete;

		// Read file accessor functions 
		bool read(std::string fname, ctkData::Model& mol);
		bool read(std::string fname, ctkData::Model& mol, const char* ext);
		bool read(const char* fname, ctkData::Model& mol);
		bool read(const char* fname, ctkData::Model& mol, const char* ext);

		// Write file accessor funtions
		bool write(std::string fname, const ctkData::Model& mol);
		bool write(std::string fname, const ctkData::Model& mol, const char* ext);
		bool write(const char* fname, const ctkData::Model& mol);
		bool write(const char* fname, const ctkData::Model& mol, const char* ext);

	private:
		FileIO* _fileIO = 0;

		// utility functions
		bool setFileType(std::string ftype);
		bool fileExists(std::filesystem::path fpath);
		std::string determineFileType(std::filesystem::path ext);
		std::filesystem::path getFileExtension(std::string ftype);

		// Main read function 
		bool _read(std::filesystem::path fpath, std::string ftype, ctkData::Model& mol);
		// Main write function 
		bool _write(std::filesystem::path fpath, std::string ftype, const ctkData::Model& mol);
	};

}