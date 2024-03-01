#include "FileIO/FileControl.h"

#include "FileIO/FileIO_XYZ.h"
#include "FileIO/FileIO_PDB.h"
#include "FileIO/FileIO_Mol2.h"

#include <iostream>

using namespace ctkIO;

bool FileControl::_read(std::filesystem::path fpath, std::string ftype, ctkData::Molecule& mol) {
	if (!fileExists(fpath)) {
		std::cout << "File not found!" << std::endl;
	}
	
	if (setFileType(ftype)) {
		std::cout << "found file and checked extension" << std::endl;
		_fileIO->setFileName(fpath);
		_fileIO->read(mol);
		return true;
	}
	return false;
}

bool FileControl::_write(std::filesystem::path fpath, std::string ftype, const ctkData::Molecule& mol) {
	std::cout << "Entering write function" << std::endl;
	std::cout << "ftype = " << ftype << std::endl;
 	if (setFileType(ftype)) {
		std::filesystem::path ext = getFileExtension(ftype);
		if (ext != fpath.extension()) {
			fpath.replace_extension(ext);
		}
		std::cout << fpath << std::endl;
		if (!fileExists(fpath)) { // change this to a user check or just overwrite (this could be dangerous)
			_fileIO->setFileName(fpath);
			_fileIO->write(mol);
			return true;
		}
	}
	return false;
}

bool FileControl::setFileType(std::string ftype) {
	if (_fileIO != 0) {
		delete _fileIO;
		_fileIO = 0;
	}
	
	if (ftype == "xyz") {
		_fileIO = new FileIO_XYZ();
	}
	else if (ftype == "pdb") {
		_fileIO = new FileIO_PDB();
	}
	else if (ftype == "ml2") {
		_fileIO = new FileIO_Mol2();
	}
	else {
		return false;
	}
 	return true;
}

std::string FileControl::determineFileType(std::filesystem::path ext) {
	if (ext == ".xyz") {
		return "xyz";
	}
	else if(ext == ".pdb") {
		return "pdb";
	}
	else if (ext == ".mol2") {
		return "ml2";
	}
	else {
		return "";
	}
}

std::filesystem::path FileControl::getFileExtension(std::string ftype) {
	if (ftype == "xyz") {
		return std::filesystem::path(".xyz");
	}
	else if (ftype == "pdb") {
		return std::filesystem::path(".pdb");
	}
	else if (ftype == "ml2") {
		return std::filesystem::path(".mol2");
	}
	else {
		return std::filesystem::path("");
	}
}