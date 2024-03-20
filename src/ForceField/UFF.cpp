#include "ForceField/UFF.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <format>



UFF::UFF(ctkData::Molecule& mol) : ForceField(mol) {
	setParameters();
}

UFF::~UFF() {
	for (auto p : _params) {
		delete p.second;
		p.second = 0;
	}
	_params.clear();
	clearBonds();
	clearAngles();
	clearTorsions();
	clearInversions();
	clearNonBonded();
}

void UFF::setParameters() {

	std::ifstream prmFile("./Resources/UFF.prm");
	if (!prmFile.is_open()) {
		std::cout << "Unable to read param file" << std::endl;
		return;
	}
	std::string line;
	std::vector<std::string> vals;
	vals.reserve(12);
	const std::regex re("\t");
	while (std::getline(prmFile, line)) {
		double params[11];
		vals.clear();
		std::copy(
			std::sregex_token_iterator(
				line.begin(), line.end(), re, -1
			),
			std::sregex_token_iterator(),
			std::back_inserter(vals)
		);

		for (int i = 1; i < 12; i++) {
			params[i - 1] = stod(vals[i]);
		}
		_params.insert(std::pair<std::string, UFFParameters*>(vals[0], new UFFParameters(vals[0], params)));
	}
	prmFile.close();
}

void UFF::setupTerms() {
	// Precompute all required constants and determine all 
	// required terms for the energy sums
	
	// Clear any old terms 
	clearBonds();
	clearAngles();
	
	std::string keyi; 
	std::string keyj;
	std::string keyk;

	for (int i = 0; i < _mol.nAtoms(); i++) {
		for (int j = (i + 1); j < _mol.nAtoms(); j++) {
			if (_mol.connected(i, j)) {
				// Set ip BondCalc
				keyi = getAtomKey(_mol.getAtom(i));
				keyj = getAtomKey(_mol.getAtom(j));
				BondCalc* bnd = new BondCalc(_mol.getAtom(i), _mol.getAtom(j));
				bnd->calculateConstants(_params[keyi], _params[keyj]);
				_bonds.push_back(bnd);
				
				// Search in tree 
				for (ctkData::Atom* ak : _mol.getAtom(j)->connections()) {
					if (ak == _mol.getAtom(i)) { continue; }
					// Not currently setup up to do angles -> TODO
					
					// Search for torsion with altered ordering al->ai->aj->ak
					for (ctkData::Atom* al : _mol.getAtom(i)->connections()) {
						if (al != _mol.getAtom(j)) {
							// Setup TorsionCalc 
							TorsionCalc* tor = new TorsionCalc(al, _mol.getAtom(i), _mol.getAtom(j), ak);
							if (tor->setupConstants(_params[keyi], _params[keyj])) {
								_torsions.push_back(tor);
							}
							else {
								delete tor;
							}
							
						}
					}
				}
			}
			else if (!_mol.connected13(i, j)) {
				// Setup up non bonded interaction terms 
				keyi = getAtomKey(_mol.getAtom(i));
				keyj = getAtomKey(_mol.getAtom(j));
				NonBond* vdw = new NonBond(_mol.getAtom(i), _mol.getAtom(j));
				vdw->setupTerms(_params[keyi], _params[keyj], false);
				_nonBonded.push_back(vdw);
			}
		}
	}
	for (int i = 0; i < _bonds.size(); i++) {
		for (int j = (i + 1); j < _bonds.size(); j++) {
			if (_bonds[i]->isAtomInBond(_bonds[j]->getAtomi()) || _bonds[i]->isAtomInBond(_bonds[j]->getAtomj())) {
				// Create A-B-C angle calc
				AngleCalc* angle = new AngleCalc(_bonds[i], _bonds[j]);
				keyi = getAtomKey(angle->getAtomi());
				keyj = getAtomKey(angle->getAtomj());
				keyk = getAtomKey(angle->getAtomk());
				angle->calculateConstants(_params[keyi], _params[keyj], _params[keyk]);
				_angles.push_back(angle);
			}
		}
	}
}

void UFF::runSteps(int n) {
	calculateEnergy(true);
}

double UFF::energy() const { return _eBond + _eAngle + _eDihedral + _eInversion + _eVdW + _eElectro; };
double UFF::getBondEnergy() const { return _eBond; };
double UFF::getAngleEnergy() const { return _eAngle; };
double UFF::getDihedralEnergy() const { return _eDihedral; };
double UFF::getInversionEnergy() const { return _eInversion; };
double UFF::getVDWEnergy() const { return _eVdW; };
double UFF::getElectrostaticEnergy() const { return _eElectro; };

int UFF::nBonds() const {
	return _bonds.size();
}
int UFF::nAngles() const {
	return _angles.size();
}
int UFF::nDihedrals() const {
	return _torsions.size();
}
int UFF::nInversions() const {
	return _inversions.size();
}
int UFF::nNonBonded() const {
	return _nonBonded.size();
}

void UFF::calculateEnergy(bool gradiants) {
	_eBond = 0.0;
	_eAngle = 0.0;

	// Bond energy calculation
	for (BondCalc* bnd : _bonds) {
		_eBond += E_R(bnd);
	}
	// Angle energy calculation
	for (AngleCalc* angle : _angles) {
		_eAngle += E_Theta(angle);
	}
	// VdW energy calculation 
	for (NonBond* vdw : _nonBonded) {
		_eVdW += E_VdW(vdw);
	}
	
}

double UFF::E_R(const BondCalc* bond) {
	double r = bond->getLength();
	r = (r - bond->getR0());
	double r2 = r * r;
	return (bond->getForceConstant() * r2);
}

double UFF::E_Theta(const AngleCalc* angle) {
	double p{ 0.0 };  // penalty function generally based on ESFF

	switch (angle->getAtomj()->coordination()) {
	case 1: // sp - linear 
		return angle->getForceConstant() - (angle->getForceConstant() * std::cos(angle->getTheta()));
	case 2: // sp2 - trigonal planar (n = 3)
		p = exp(-20.0 * (angle->getTheta() - angle->getTheta0() + 0.25));
		return (angle->getForceConstant() / 9) * (1 - cos(3 * angle->getTheta())) + p;
	case 4: // square planar (n = 4) 
	case 6: // octahedral (n = 4) 
		p = exp(-20.0 * (angle->getTheta() - angle->getTheta0() + 0.25));
		return (angle->getForceConstant() / 16) * (1 - cos(4 * angle->getTheta())) + p;
	case 7: // pentagonal 
		return 0.0; // NOT IMPLEMENTED 
	default: // sp3 
		double ct = std::cos(angle->getTheta()); // cos(theta)
		double ct0 = std::cos(angle->getTheta0());
		double ct2 = ct * ct; // cos2(theta) 
		double ct02 = ct0 * ct0;
		double c2 = 1 / (4 * (1 - ct02));
		double c0 = (2 * ct02 + 1) * c2;
		double c1 = -4 * c2 * ct0;
		return angle->getForceConstant() * (c0 + (c1 * ct) + (c2 * (2 * ct2 - 1)));
	}
}

double UFF::E_Torsion(const TorsionCalc* tor) {
	double phi = tor->getPeriodicity() * tor->getPhi();
	phi = std::cos(phi);
	return tor->getV() * (1 - (tor->getPhi0() * phi));
}

double UFF::E_Inversion(const InversionCalc* oop) {
	return 0.0; 
}

double UFF::E_VdW(const NonBond* vdw) {
	ctkMaths::Vector3 rij = vdw->getAtomi()->getPosition() - vdw->getAtomj()->getPosition();
	double r = rij.normal();

	double r2 = r * r; 
	double r6 = r2 * r2 * r2;
	double r12 = r6 * r6; 

	return vdw->_dij * ((vdw->_xij12 / r12) - 2 * (vdw->_xij6 / r6));
}

std::string UFF::energyToString() const {
	std::string oStr; 
	oStr += std::format("Bond     : Terms = {0:3d}, Energy = {1:>10.6} Kcal/mol\n", nBonds(), getBondEnergy());
	oStr += std::format("Angle    : Terms = {0:3d}, Energy = {1:>10.6} Kcal/mol\n", nAngles(), getAngleEnergy());
	oStr += std::format("Dihedral : Terms = {0:3d}, Energy = {1:>10.6} Kcal/mol\n", nDihedrals(), getDihedralEnergy());
	oStr += std::format("Inversion: Terms = {0:3d}, Energy = {1:>10.6} Kcal/mol\n", nInversions(), getInversionEnergy());
	oStr += std::format("Non-Bond : Terms = {0:3d}, Energy = {1:>10.6} Kcal/mol\n", nNonBonded(), getVDWEnergy());
	return oStr;
}


void UFF::clearBonds() {
	for (auto b : _bonds) {
		delete b;
	}
	_bonds.clear();
}

void UFF::clearAngles() {
	for (auto a : _angles) {
		delete a;
		a = 0;
	}
	_angles.clear();
}

void UFF::clearTorsions() {
	for (auto t : _torsions) {
		delete t; 
		t = 0;
	}
	_torsions.clear();
}

void UFF::clearInversions() {
	for (auto oop : _inversions) {
		delete oop;
		oop = 0;
	}
	_inversions.clear();
}

void UFF::clearNonBonded() {
	for (auto nb : _nonBonded) {
		delete nb;
		nb = 0;
	}
	_nonBonded.clear();
}

std::string UFF::getAtomKey(ctkData::Atom* atom) const {
	int coord = atom->coordination();
	switch (atom->getAtomicNumber()) {
	case 1:
		if (atom->nBonds() > 1) { return "H_b"; }
		else { return "H_"; }
	case 2:
		return "He4+4";
	case 3:
		return "Li";
	case 4:
		return "Be3 + 2";
	case 5:
		if (coord == 2) { return "B_2"; }
		else { return "B_3"; }
	case 6:
		if (atom->isAromatic()) { return "C_R"; }
		else if (coord == 2) { return "C_2"; }
		else if (coord == 1) { return "C_1"; }
		else { return "C_3"; }
	case 7:
		if (atom->isAromatic()) { return "N_R"; }
		else if (coord == 2) { return "N_2"; }
		else if (coord == 1) { return "N_1"; }
		else { return "N_3"; }
	case 8:
		if (atom->isAromatic()) { return "O_R"; }
		else if (coord == 2) { return "O_2"; }
		else if (coord == 1) { return "O_1"; }
		else { return "O_3"; } // need case checking for zeolite (O_3_z)
	case 9:
		return "F_";
	case 10:
		return "Ne4+4";
	default:
		return "Du";
	}
}