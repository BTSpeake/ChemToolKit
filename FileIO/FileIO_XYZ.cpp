#include "FileIO_XYZ.h"

#include <sstream>
#include <regex>
#include <vector>
#include <iostream>

void FileIO_XYZ::read(Molecule& mol) const {
    std::ifstream file(_fname);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }
    std::string line;
    int nAtoms{ 0 };

    // Parse the number of atoms from the first line in the file 
    if (!getline(file, line)) {
        throw std::runtime_error("Error reading number of atoms");
    }
    std::regex nAtomsRegex(R"(^\d+$)"); // Ensure valid integer
    std::smatch nAtomsMatch;
    if (!std::regex_match(line, nAtomsMatch, nAtomsRegex)) {
        throw std::runtime_error("Invalid number of atoms format");
    }
    nAtoms = std::stoi(nAtomsMatch[0]);

    getline(file, line); // read the comment line 

    // Parse the remaining atom data line by line 
    for (int i = 0; i < nAtoms; ++i) {
        if (!getline(file, line)) {
            throw std::runtime_error("Error reading atom data");
        }

        std::regex dataRegex(R"(^(\w+)\s+(\S+)\s+(\S+)\s+(\S+)$)"); // Match atom symbol, coordinates
        std::smatch dataMatch;
        if (!regex_match(line, dataMatch, dataRegex)) {
            throw std::runtime_error("Invalid atom data format");  
        }
        else {
            mol.addAtom(dataMatch[1], std::stod(dataMatch[2]), std::stod(dataMatch[3]), std::stod(dataMatch[4]));
        }
    }

    if (mol.nAtoms() != nAtoms) {
        throw std::runtime_error("Invalid xyz format - Error in file parse.");
    }


    file.close();
}


void FileIO_XYZ::write(const Molecule& mol) const {

}