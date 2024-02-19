#pragma once

#include "FileIO/FileIO.h"
#include "Molecule/Molecule.h"

#include <string>


class FileControl {
public:
	FileControl() = default;
	~FileControl() = default;
	FileControl(const FileControl&) = delete;
	FileControl& operator=(const FileControl&) = delete;

	// Read file accessor functions 
	bool read(std::string fname, Molecule& mol) {
		std::filesystem::path fpath(fname);
		return read(fpath, fpath.extension(), mol);
	}
	bool read(std::string fname, Molecule& mol, const char* ext) {
		return read(std::filesystem::path(fname), std::filesystem::path(ext), mol);
	}
	bool read(const char* fname, Molecule& mol) {
		std::filesystem::path fpath(fname);
		return read(fpath, fpath.extension(), mol);
	}
	bool read(const char* fname, Molecule& mol, const char* ext) {
		return read(std::filesystem::path(fname), std::filesystem::path(ext), mol);
	}

	// Write file accessor funtions
	bool write(std::string fname, const Molecule& mol) {
		std::filesystem::path fpath(fname);
		return write(fpath, fpath.extension(), mol);
	}
	bool write(std::string fname, const Molecule& mol, const char* ext) {
		return write(std::filesystem::path(fname), std::filesystem::path(ext), mol);
	}
	bool write(const char* fname, const Molecule& mol) {
		std::filesystem::path fpath(fname);
		return write(fpath, fpath.extension(), mol);
	}
	bool write(const char* fname, const Molecule& mol, const char* ext) {
		return write(std::filesystem::path(fname), std::filesystem::path(ext), mol);
	}

private:
	FileIO* _fileIO = 0;
	
	// utility functions
	bool setFileType(std::filesystem::path ext);
	bool fileExists(std::filesystem::path fpath) {
		return std::filesystem::exists(fpath);
	}
	// Main read function 
	bool read(std::filesystem::path fpath, std::filesystem::path ext, Molecule& mol);
	// Main write function 
	bool write(std::filesystem::path fpath, std::filesystem::path ext, const Molecule& mol);
};