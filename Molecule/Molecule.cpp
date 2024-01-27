#include "Molecule.h"

Molecule::Molecule() {

}

Molecule::~Molecule() {
	for (Bond* b : _bonds) {
		delete b;
	}
	_bonds.clear();
	for (Atom* a : _atoms) {
		delete a;
	}
	_atoms.clear();
}

void Molecule::addAtom(int a, double x, double y, double z) {
	Atom* nAtm = new Atom(a, x, y, z);
	_atoms.push_back(nAtm);
}

void Molecule::addBond(int i, int j, int bo) {
	Bond* nBond = new Bond(_atoms[i], _atoms[j]);
	nBond->setBondOrder(bo);
	_bonds.push_back(nBond);
}