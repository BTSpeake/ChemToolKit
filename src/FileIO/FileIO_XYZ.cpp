#include "FileIO/FileIO_XYZ.h"

#include <sstream>
#include <regex>

using namespace ctkIO;

bool FileIO_XYZ::read(ctkData::Model& mol) {
    std::ifstream file(_fname);
    if (!file.is_open()) {
        _error = "ERROR :: Unable to open file!";
        return false;
    }
    std::string line;
    int nAtoms{ 0 };

    // Parse the number of atoms from the first line in the file 
    if (!getline(file, line)) {
        _error = "ERROR :: file is empty!";
        file.close();
        return false;
    }
    std::regex nAtomsRegex(R"(^\d+$)"); // Ensure valid integer
    std::smatch nAtomsMatch;
    if (!std::regex_match(line, nAtomsMatch, nAtomsRegex)) {
        _error = "ERROR :: Invalid line format found for line 1 (number of atoms line)!";
        file.close();
        return false;
    }
    nAtoms = std::stoi(nAtomsMatch[0]);

    getline(file, line); // read the comment line 

    // Define the regex variables
    std::regex dataRegex(R"(^(\w+)\s+(\S+)\s+(\S+)\s+(\S+)$)"); // Match atom symbol, coordinates
    std::smatch dataMatch;

    // Parse the remaining atom data line by line 
    for (int i = 0; i < nAtoms; ++i) {
        if (!getline(file, line)) {
            _error = "ERROR :: Invalid atom data entry on line " + std::to_string(i);
            mol.reset();
            file.close();
            return false;
        }
        if (regex_match(line, dataMatch, dataRegex)) {
            mol.addAtom(dataMatch[1], std::stod(dataMatch[2]), std::stod(dataMatch[3]), std::stod(dataMatch[4]));
        }
    }

    if (mol.nAtoms() != nAtoms) {
        _error = "ERROR :: Invalid XYZ format -> total number of atoms not matched!";
        mol.reset();
        file.close();
        return false;
    }


    file.close();

    // Calculate bonding as default for xyz files
    mol.calculateBonding();
    
    return true;
}


bool FileIO_XYZ::write(const ctkData::Model& mol) {
    std::ofstream file(_fname);
    if (!file.is_open()) {
        _error = "ERROR :: Unable to open file!";
        return false;
    }
    const int nAtms = mol.nAtoms();
    file << nAtms << std::endl; 
    //file << "COMMENT::Generated by ChemToolKit written by Dr B.T Speake" << std::endl; 
    file << std::endl;
    for (int i = 0; i < nAtms; i++) {
        ctkData::Atom* atm = mol.getAtom(i);
        file << atm->getSymbol() << "    " << atm->getPosition()[0] << "    " << atm->getPosition()[1] << "    " << atm->getPosition()[2] << std::endl;
    }
    file.close();
    return true;
}