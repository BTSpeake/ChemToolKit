#include "FileIO/FileIO_PDB.h"

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>

#include <iostream>

using namespace ctkIO;

bool FileIO_PDB::read(ctkData::Model& mol) {
    std::ifstream file(_fname);
    if (!file.is_open()) {
        _error = "ERROR :: Unable to open file";
        return false;
    }
    
    // Set Regex definitions 
    std::string line; 
    //std::regex headerRe(R"(^TITLE\s+(.*)$)");
    std::regex atomRe(R"(^ATOM\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S+)\s+(\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S+)\s+$)"); 
    std::regex hetAtomRe(R"(^HETATM\s+(\d+)\s+(\S+)\s+(\S+)\s+(\S?)\s+(\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S?\d+\.\d+)\s+(\S+)\s+$)");
    std::regex conectRe(R"(^CONECT\s+(\d+))");

    while (getline(file, line)) {
        std::smatch match;

        // Parse an ATOM line 
        if (std::regex_match(line, match, atomRe)) {
            mol.addAtom(match[11], std::stod(match[6]), std::stod(match[7]), std::stod(match[8]));
            mol.getAtom(mol.nAtoms() - 1)->addLabel("PDB_ATOM");
        }
        else if (std::regex_match(line, match, hetAtomRe)) {
            mol.addAtom(match[11], std::stod(match[6]), std::stod(match[7]), std::stod(match[8]));
            mol.getAtom(mol.nAtoms() - 1)->addLabel("PDB_HETATOM");
        }
        else if (std::regex_search(line, match, conectRe)) {
            int atmi = std::stoi(match[1]) - 1;
            std::regex digitRe(R"((\d+))");
            std::regex_token_iterator<std::string::iterator> rend;
            std::regex_token_iterator<std::string::iterator> a(line.begin(), line.end(), digitRe);
            while (a != rend) {
                int atmj = std::stoi(*a++) - 1;
                if (atmj > atmi) {
                    mol.addBond(atmi, atmj);
                }
            }
        }
    }
    return true;
}

bool FileIO_PDB::write(const ctkData::Model& mol) {
    _error = "ERROR :: Writing to PDB files is currently unsupported!";
    return false;
}
