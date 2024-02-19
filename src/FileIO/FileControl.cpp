#include "FileIO/FileControl.h"

#include "FileIO/FileIO_XYZ.h"
#include "FileIO/FileIO_PDB.h"

#include <iostream>

bool FileControl::read(std::filesystem::path fpath, std::filesystem::path ext, Molecule& mol) {
	if (setFileType(ext) && fileExists(fpath)) {
		_fileIO->setFileName(fpath);
		_fileIO->read(mol);
		return true;
	}
	return false;
}

bool FileControl::write(std::filesystem::path fpath, std::filesystem::path ext, const Molecule& mol) {
	if (setFileType(ext)) {
		if (ext != fpath.extension()) {
			fpath.replace_extension(ext);
		}
		if (!fileExists(fpath)) { // change this to a user check or just overwrite (this could be dangerous)
			_fileIO->setFileName(fpath);
			_fileIO->write(mol);
			return true;
		}
	}
	return false;
}

bool FileControl::setFileType(std::filesystem::path ext) {
	if (_fileIO != 0) {
		delete _fileIO;
		_fileIO = 0;
	}
	
	if (ext == ".xyz") {
		_fileIO = new FileIO_XYZ();
	}
	else if (ext == ".pdb") {
		_fileIO = new FileIO_PDB();
	}
	else {
		return false;
	}
	return true;
}