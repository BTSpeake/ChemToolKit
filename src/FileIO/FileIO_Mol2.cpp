#include "FileIO/FileIO_Mol2.h"

#include <regex>

#include <iostream>

using namespace ctkIO;

void FileIO_Mol2::read(ctkData::Model& mol) const {
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

void FileIO_Mol2::write(const ctkData::Model& mol) const {
	std::ofstream file(_fname);
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file");
		return;
	}
	// Write the header 
	file << "# Name: Unknown\n";
	file << "# Created by: ChemToolKit\n";
	file << "# Created: \n"; // Add the current data/time here 
	
	// Write the MOLECULE section 
	file << "@<TRIPOS>MOlECULE\n";
	file << "unknown\n"; 
	file << "  " << mol.nAtoms() << "  " << mol.nBonds() << "  0  0  0\n";
	file << "SMALL\n";
	file << "NO_CHARGES\n";
	file << "****\n"; 
	
	// Write the ATOM section 
	file << "@<TRIPOS>ATOM\n";
	for (int i = 0; i < mol.nAtoms(); i++) {
		file << '\t' << i << "  " << mol.getAtom(i)->getSymbol() << "\t\t";
		file << mol.getAtom(i)->getPosition().toSimpleStr() << '\t';
		file << mol.getAtom(i)->getSYBYL() << '\n';
	}

	// Write the BOND section 
	file << "@<TRIPOS>BOND\n";
	int bi = 0; // simple bond index counter
	auto atmEndIt = mol.getAtomIt(mol.nAtoms());
	auto atmBegIt = mol.getAtomIt(0);
	for (int i = 0; i < (mol.nAtoms() - 1); i++) {
		ctkData::Atom* atmi = mol.getAtom(i);
		for (ctkData::Atom* atmj : atmi->connections()) {
			auto atmIt = std::find((mol.getAtomIt(i) + 1), atmEndIt, atmj);
			if (atmIt == atmEndIt) {
				continue;
			}
			int j = std::distance(atmBegIt, atmIt);

			file << '\t' << bi << '\t';
			file << i << '\t' << j << '\t'; 
			if (atmi->isAromatic() && mol.getAtom(j)->isAromatic()) {
				file << "ar\n";
			}
			else if (atmi->isDouble(mol.getAtom(j))) {
				file << "2\n";
			}
			else {
				file << "1\n";
			}
			bi++;
		}
	}

}