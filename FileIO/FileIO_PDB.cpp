#include "FileIO_PDB.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>

#include <iostream>

void FileIO_PDB::read(Molecule& mol) const {
    std::ifstream file(_fname);
    if (!file.is_open()) {
        return;
    }
    
    // Set Regex definitions 
    std::string line; 
    //std::regex headerRe(R"(^TITLE\s+(.*)$)");
    std::regex atomRe(R"(^ATOM\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S+)\s+$)"); 
    std::regex hetAtomRe(R"(^HETATOM\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S+)\s+$)");

    while (getline(file, line)) {
        std::smatch match;

        // Parse an ATOM line 
        if (std::regex_match(line, match, atomRe)) {
            mol.addAtom(match[11], std::stod(match[6]), std::stod(match[7]), std::stod(match[8]));
        }
        else if (std::regex_match(line, match, hetAtomRe)) {
            mol.addAtom(match[11], std::stod(match[6]), std::stod(match[7]), std::stod(match[8]));
        }
        
    }
}

void FileIO_PDB::write(const Molecule& mol) const {
    throw std::runtime_error("Writing to PDB files is currently unsupported!");
}
