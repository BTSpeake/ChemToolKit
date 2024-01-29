#pragma once 

#include <vector>

#include "Atom.h"
#include "Bond.h"
#include "Angle.h"

class Molecule {
public:
	Molecule();
	~Molecule();
	Molecule(const Molecule& mol) = delete;
	Molecule& operator=(const Molecule& mol) = delete;

	// get functions 
	int nAtoms() { return _atoms.size(); };
	int nBonds() { return _bonds.size(); };
	Atom* getAtom(int i) const { return _atoms[i]; };
	Bond* getBond(int i) const { return _bonds[i]; };

	// set functions ]
	void addAtom(int a, double x, double y, double z);
	void addBond(int i, int j, int bo = 1);

	// Clean up functions
	void clearAtoms();
	void clearBonds();

private:
	std::vector<Atom*> _atoms;
	std::vector<Bond*> _bonds;
};