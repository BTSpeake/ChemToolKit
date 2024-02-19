#pragma once 

#include <vector>

#include "Molecule/Atom.h"
//#include "Bond.h"
//#include "Angle.h"

struct Bond {
	Bond(int i, int j, int o) : _i(i), _j(j), _o(o) {};
	unsigned int _i;
	unsigned int _j; 
	int _o;
};

class Molecule {
public:
	Molecule();
	~Molecule();
	Molecule(const Molecule& mol) = delete;
	Molecule& operator=(const Molecule& mol) = delete;

	// get functions 
	int nAtoms() const { return _atoms.size(); };
	int nBonds() const { return _bonds.size(); };
	Atom* getAtom(int i) const { return _atoms[i]; };
	Bond* getBond(int i) const { return _bonds[i]; };

	// set functions ]
	void addAtom(int a, double x, double y, double z);
	void addAtom(std::string s, double x, double y, double z);
	void addBond(unsigned int i, unsigned int j, int bo = 1) {
		if (i < nAtoms() && j < nAtoms()) { _bonds.push_back(new Bond(i, j, bo)); }
	};

	// processing functions 
	void calculateBonding();

	// Utility functions
	void clearAtoms();
	void clearBonds();

private:
	std::vector<Atom*> _atoms;
	std::vector<Bond*> _bonds;
};