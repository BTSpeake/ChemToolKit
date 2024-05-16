#include "Data/Model.h"

#include "Maths/Vector3.h"

using namespace ctkData;

Model::Model() : _title("New Model") {

}

Model::Model(std::string title) : _title(title) {}

Model::~Model() {
	clearAtoms();
}

Model::Model(const Model& model) {
	// Make all the atoms 
	for (int i = 0; i < model.nAtoms(); i++) {
		Atom* a = model.getAtom(i);
		addAtom(a->getAtomicNumber(), a->getPosition()[0], a->getPosition()[1], a->getPosition()[2]);
	}
	// Connect all the atoms 
	//for (int i = 0; i < model.nAtoms(); i++) {
	//	Atom* ai = model.getAtom(i);
	//	for (Atom* aj : ai->connections()) {

	//	}
	//}
}

// get functions for atoms/bonds
int Model::nAtoms() const { return _atoms.size(); };

int Model::nBonds() const { 
	int n = 0; 
	for (int i = 0; i < _atoms.size(); i++) {
		for (Atom* atm : _atoms[i]->connections()) {
			if (std::find(_atoms.begin(), _atoms.begin() + i, atm) != (_atoms.begin() + i)) {
				n++;
			}
		}
	}
	return n;
}

Atom* Model::getAtom(int i) const { return _atoms[i]; };

std::vector<Atom*>::const_iterator Model::getAtomIt(int i) const { return _atoms.begin() + i; }

// get functions for Model properties 
int Model::getCharge() const { return _charge; };
double Model::getSpinProjection() const { return _spinProj; };
int Model::getMultiplicity() const { return static_cast<int>(round(2 * _spinProj)) + 1; };
const ctkMaths::Vector3& Model::getCoM() const { return CoM; };

void Model::addAtom(int a, double x, double y, double z) {
	Atom* nAtm = new Atom(a, x, y, z);
	_atoms.push_back(nAtm);
}

void Model::addAtom(std::string s, double x, double y, double z) {
	Atom* nAtm = new Atom(s, x, y, z);
	_atoms.push_back(nAtm);
}

void Model::addBond(int i, int j, int bo) {
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

bool Model::connected(const int i, const int j) const {
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

bool Model::connected13(const int i, const int j) const {
	for (Atom* k : _atoms[i]->connections()) {
		if (_atoms[j]->isConnected(k)) {
			return true;
		}
	}
	return false;
}

// set functions properties 
void Model::setCharge(int charge) { _charge = charge; };
void Model::setSpinProjection(double sp) { _spinProj = sp; };
void Model::setMultiplicity(double m) { _spinProj = (m - 1) / 2; };

/*! \todo Update to allow a scale factor to control how the bonds are assigned */
void Model::calculateBonding(const double scale) {
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

void Model::calculateCoM() {
	CoM.setX(0.0);
	CoM.setY(0.0); 
	CoM.setZ(0.0);
	
	for (Atom* atom : _atoms) {
		CoM += atom->getPosition();
	}
	CoM /= nAtoms();
}

void Model::centreOnOrigin() {
	calculateCoM();
	for (Atom* atom : _atoms) {
		atom->getPosition() -= CoM;
	}
}

double Model::calculateNNR() const {
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

// \Todo this should be extended to include other properties 
void Model::reset() {
	clearBonds();
	clearAtoms();
}

void Model::clearAtoms() {
	for (Atom* a : _atoms) {
		delete a;
	}
	_atoms.clear();
}

void Model::clearBonds() {
	for (Atom* a : _atoms) {
		a->resetBonding();
	}
}

std::string Model::toString() const {
	std::string s;
	s += "Model Object\n---------------\n"; 
	s += "No. Atoms: " + std::to_string(nAtoms()) + '\n';
	s += "No. Bonds: " + std::to_string(nBonds()) + '\n';
	s += "Charge:    " + std::to_string(getCharge()) + '\n';
	s += "Spin Proj: " + std::to_string(getSpinProjection()) + "\n\n";
	s += atomsList();
	return s;
}

std::string Model::atomsList() const {
	std::string s = "\nAtoms: ";
	for (Atom* a : _atoms) {
		s += '\n' + a->toString();
	}
	return s;
}

std::string Model::getTitle() const {
	return _title;
}

void Model::setTitle(std::string title) {
	_title = title;
}


std::shared_ptr<VolumeData> Model::getVolumetricDataSet(const int i) {
	if (i >= _gridData.size()) {
		return nullptr;
	}
	else {
		return _gridData[i];
	}
}

void Model::addVolumetricDataSet(std::shared_ptr<VolumeData> data) {
	_gridData.push_back(data);
}