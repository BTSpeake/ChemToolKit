#include "Molecule.h"

#include "../Maths/Vector3.h"

Molecule::Molecule() {

}

Molecule::~Molecule() {
	clearAtoms();
	clearBonds();
}

void Molecule::addAtom(int a, double x, double y, double z) {
	Atom* nAtm = new Atom(a, x, y, z);
	_atoms.push_back(nAtm);
}

void Molecule::addAtom(std::string s, double x, double y, double z) {
	Atom* nAtm = new Atom(s, x, y, z);
	_atoms.push_back(nAtm);
}

void Molecule::calculateBonding() {
	clearBonds();
	for (int i = 0; i < nAtoms(); i++) {
		for (int j = (i + 1); j < nAtoms(); j++) {
			Vector3 bv = _atoms[i]->getPosition() - _atoms[j]->getPosition();
			double r = bv.normal();
			double thr = 1.25 * (_atoms[i]->getCovalentRadii() + _atoms[j]->getCovalentRadii());
			if (r < thr) {
				_bonds.push_back(new Bond(i, j, 1));
				_atoms[i]->addSingleBond();
				_atoms[j]->addSingleBond();
			}
		}
	}
}


void Molecule::clearAtoms() {
	for (Atom* a : _atoms) {
		delete a;
	}
	_atoms.clear();
}

void Molecule::clearBonds() {
	for (Atom* a : _atoms) {
		a->resetBonding();
	}
	for (Bond* b : _bonds) {
		delete b;
	}
	_bonds.clear();
}

