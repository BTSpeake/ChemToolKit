#include "FileIO/FileIO_Mol2.h"

#include <regex>
#include <iostream>

void FileIO_Mol2::read(Molecule& mol) const {
	std::ifstream file(_fname);
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file");
	}
	std::string line; 
	std::regex dummyHeaderRe("@<TRIPOS>");
	std::regex atomHeaderRe("@<TRIPOS>ATOM");
	std::regex atomRe(R"((-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+([A-Z,a-z]{1,2}))");

	bool readAtoms = false;

	while (getline(file, line)) {
		std::smatch match;
		if (regex_search(line, match, atomHeaderRe)) {
			readAtoms = true;
			continue;
		}
		else if (regex_search(line, match, dummyHeaderRe)) {
			readAtoms = false;
			continue;
		}
		if (readAtoms) {
			std::smatch match;
			if (regex_search(line, match, atomRe)) {
				//std::cout << match[4] << std::endl;
				mol.addAtom(match[4], std::stod(match[1]), std::stod(match[2]), std::stod(match[3]));
			}
		}
	}
}

void FileIO_Mol2::write(const Molecule& mol) const {

}