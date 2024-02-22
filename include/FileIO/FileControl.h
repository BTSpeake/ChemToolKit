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
		return _read(fpath, determineFileType(fpath.extension()), mol);
	}
	bool read(std::string fname, Molecule& mol, const char* ext) {
		return _read(std::filesystem::path(fname), ext, mol);
	}
	bool read(const char* fname, Molecule& mol) {
		std::filesystem::path fpath(fname);
		return _read(fpath, determineFileType(fpath.extension()), mol);
	}
	bool read(const char* fname, Molecule& mol, const char* ext) {
		return _read(std::filesystem::path(fname), ext, mol);
	}

	// Write file accessor funtions
	bool write(std::string fname, const Molecule& mol) {
		std::filesystem::path fpath(fname);
		return _write(fpath, determineFileType(fpath.extension()), mol);
	}
	bool write(std::string fname, const Molecule& mol, const char* ext) {
		return _write(std::filesystem::path(fname), ext, mol);
	}
	bool write(const char* fname, const Molecule& mol) {
		std::filesystem::path fpath(fname);
		return _write(fpath, determineFileType(fpath.extension()), mol);
	}
	bool write(const char* fname, const Molecule& mol, const char* ext) {
		return _write(std::filesystem::path(fname), ext, mol);
	}

private:
	FileIO* _fileIO = 0;
	
	// utility functions
	bool setFileType(std::string ftype);
	bool fileExists(std::filesystem::path fpath) {
		return std::filesystem::exists(fpath);
	}
	std::string determineFileType(std::filesystem::path ext);
	std::filesystem::path getFileExtension(std::string ftype);

	// Main read function 
	bool _read(std::filesystem::path fpath, std::string ftype, Molecule& mol);
	// Main write function 
	bool _write(std::filesystem::path fpath, std::string ftype, const Molecule& mol);
};