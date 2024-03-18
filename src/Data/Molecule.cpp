#include "Data/Molecule.h"

#include "Maths/Vector3.h"

using namespace ctkData;

// Bond -> This should eventually move to a seperate file 
Bond::Bond(int i, int j, int o) : _i(i), _j(j), _o(o) {};

Molecule::Molecule() {

}

Molecule::~Molecule() {
	clearAtoms();
	clearBonds();
}

// get functions for atoms/bonds
int Molecule::nAtoms() const { return _atoms.size(); };
int Molecule::nBonds() const { return _bonds.size(); };
Atom* Molecule::getAtom(int i) const { return _atoms[i]; };
Bond* Molecule::getBond(int i) const { return _bonds[i]; };

// get functions for molecule properties 
int Molecule::getCharge() const { return _charge; };
double Molecule::getSpinProjection() const { return _spinProj; };
int Molecule::getMultiplicity() const { return static_cast<int>(round(2 * _spinProj)) + 1; };
const ctkMaths::Vector3& Molecule::getCoM() const { return CoM; };

void Molecule::addAtom(int a, double x, double y, double z) {
	Atom* nAtm = new Atom(a, x, y, z);
	_atoms.push_back(nAtm);
}

void Molecule::addAtom(std::string s, double x, double y, double z) {
	Atom* nAtm = new Atom(s, x, y, z);
	_atoms.push_back(nAtm);
}

void Molecule::addBond(int i, int j, int bo) {
	_bonds.push_back(new Bond(i, j, bo));
	if (i < _atoms.size() && j < _atoms.size()) {
		switch (bo) {
		case 1:
			_atoms[i]->addConnection(_atoms[j]);
			_atoms[j]->addConnection(_atoms[i]);
			break;
		case 2:
			_atoms[i]->addConnection(_atoms[j], 2);
			_atoms[j]->addConnection(_atoms[i], 2);
			break;
		case 3:
			_atoms[i]->addConnection(_atoms[j], 3);
			_atoms[j]->addConnection(_atoms[i], 3);
			break;
		}
	}
	return;
};

bool Molecule::connected(const int i, const int j) const {
	if (j < 0 || j >= _atoms.size()) {
		return false;
	}
	else if (i < 0 || i >= _atoms.size()) {
		return false;
	}
	else {
		return _atoms[i]->isConnected(_atoms[j]);
	}
}

bool Molecule::connected13(const int i, const int j) const {
	for (Atom* k : _atoms[i]->connections()) {
		if (_atoms[j]->isConnected(k)) {
			return true;
		}
	}
	return false;
}

// set functions properties 
void Molecule::setCharge(int charge) { _charge = charge; };
void Molecule::setSpinProjection(double sp) { _spinProj = sp; };
void Molecule::setMultiplicity(double m) { _spinProj = (m - 1) / 2; };

void Molecule::calculateBonding() {
	clearBonds();
	for (int i = 0; i < nAtoms(); i++) {
		for (int j = (i + 1); j < nAtoms(); j++) {
			ctkMaths::Vector3 bv = _atoms[i]->getPosition() - _atoms[j]->getPosition();
			double r = bv.normal();
			double thr = 1.25 * (_atoms[i]->getCovalentRadii() + _atoms[j]->getCovalentRadii());
			if (r < thr) {
				addBond(i, j);
			}
		}
	}
}

void Molecule::calculateCoM() {
	CoM.setX(0.0);
	CoM.setY(0.0); 
	CoM.setZ(0.0);
	
	for (Atom* atom : _atoms) {
		CoM += atom->getPosition();
	}
	CoM /= nAtoms();
}

void Molecule::centreOnOrigin() {
	calculateCoM();
	for (Atom* atom : _atoms) {
		atom->getPosition() -= CoM;
	}
}

double Molecule::calculateNNR() const {
	double nnr{ 0.0 };
	for (int i = 0; i < _atoms.size(); i++) {
		for (int j = (i + 1); j < _atoms.size(); j++) {
			ctkMaths::Vector3 rij = _atoms[i]->getPosition() - _atoms[j]->getPosition();
			double nrij = rij.normal();
			nnr += (_atoms[i]->getAtomicNumber() * _atoms[j]->getAtomicNumber()) / nrij;
		}
	}
	return nnr;
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

std::string Molecule::toString() const {
	std::string s;
	s += "Molecule Object\n---------------\n"; 
	s += "No. Atoms: " + std::to_string(nAtoms()) + '\n';
	s += "No. Bonds: " + std::to_string(nBonds()) + '\n';
	s += "Charge:    " + std::to_string(getCharge()) + '\n';
	s += "Spin Proj: " + std::to_string(getSpinProjection()) + "\n\n";
	s += atomsList();
	return s;
}

std::string Molecule::atomsList() const {
	std::string s = "\nAtoms: ";
	for (Atom* a : _atoms) {
		s += '\n' + a->toString();
	}
	return s;
}