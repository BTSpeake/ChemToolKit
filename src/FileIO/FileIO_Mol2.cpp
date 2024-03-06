#include "FileIO/FileIO_Mol2.h"

#include <regex>
#include <iostream>

using namespace ctkIO;

void FileIO_Mol2::read(ctkData::Molecule& mol) const {
	std::ifstream file(_fname);
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file");
	}
	std::string line; 
	std::regex dummyHeaderRe("^@<TRIPOS>");
	std::regex atomHeaderRe("^@<TRIPOS>ATOM");
	std::regex bondHeaderRe("^@<TRIPOS>BOND");
	std::regex atomRe(R"((-?\d+\.\d+)\s+(-?\d+\.\d+)\s+(-?\d+\.\d+)\s+([A-Z,a-z]{1,2}))");
	std::regex bondRe(R"(\S+\s+(\d+)\s+(\d+)\s+(\S+))");

	bool readAtoms = false;
	bool readBonds = false;
	std::smatch match;
	std::vector<int> amideAtoms; 
	std::vector<int> aromaticAtoms;

	while (getline(file, line)) {
		
		if (readAtoms) {
			
			if (regex_search(line, match, atomRe)) {
				mol.addAtom(match[4], std::stod(match[1]), std::stod(match[2]), std::stod(match[3]));
			}
			else if (regex_search(line, bondHeaderRe)) {
				readAtoms = false; 
				readBonds = true;
			}
			else if (regex_search(line, dummyHeaderRe)) {
				readAtoms = false;
			}
		}
		else if (readBonds) {
			if (regex_search(line, match, bondRe)) {
				int bo; 
				if (match[3] == "1") {
					bo = 1;
				}
				else if (match[3] == "2") {
					bo = 2;
				}
				else if (match[3] == "3") {
					bo = 3;
				}
				else if (match[3] == "ar") {
					bo = 1;
					aromaticAtoms.push_back(std::stoi(match[1]));
					aromaticAtoms.push_back(std::stoi(match[2]));
				}
				else if (match[3] == "am") {
					bo = 1;
					amideAtoms.push_back(std::stoi(match[1]));
					amideAtoms.push_back(std::stoi(match[2]));
				}
				else if (match[3] == "un") {
					continue;
				}
				else {
					bo = 1;
				}
				mol.addBond(std::stoi(match[1]), std::stoi(match[2]), bo);
			}
			else if (regex_search(line, atomHeaderRe)) {
				readBonds = false; 
				readAtoms = true;
			}
			else if (regex_search(line, dummyHeaderRe)) {
				readBonds = false;
			}
		}
		else {
			if (regex_search(line, atomHeaderRe)) {
				readAtoms = true;
				continue;
			}
			else if (regex_search(line, bondHeaderRe)) {
				readBonds = true;
				std::cout << "Found Bond Header" << std::endl;
			}
		}	
	}

	// Set all the amide/aromatic atoms 
	for (int i : amideAtoms) {
		mol.getAtom(i)->isAmide(true);
	}
	for (int i : aromaticAtoms) {
		mol.getAtom(i)->isAromatic(true);
	}

}

void FileIO_Mol2::write(const ctkData::Molecule& mol) const {

}