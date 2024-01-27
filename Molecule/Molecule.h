#pragma once 

#include <vector>

#include "Atom.h"
#include "Bond.h"

class Molecule {
public:
	Molecule();
	~Molecule();
	Molecule(const Molecule& mol) = delete;
	Molecule& operator=(const Molecule& mol) = delete;

	// get functions 
	int nAtoms() { return _atoms.size(); };
	int nBonds() { return _bonds.size(); };

	// set functions ]
	void addAtom(int a, double x, double y, double z);
	void addBond(int i, int j, int bo = 1);

private:
	std::vector<Atom*> _atoms;
	std::vector<Bond*> _bonds;
};