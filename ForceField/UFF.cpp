#include "UFF.h"

#include <fstream>
#include <iostream>
#include <regex>



UFF::UFF(Molecule& mol) : ForceField(mol) {
	setParameters();
}

UFF::~UFF() {
	for (auto p : _params) {
		delete p.second;
		p.second = 0;
	}
	_params.clear();
	clearAngles();
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
	clearAngles();
	
	std::string keyi; 
	std::string keyj;
	std::string keyk;
	for (int i = 0; i < _mol.nBonds(); i++) {
		keyi = getAtomKey(_mol.getBond(i)->getAtomi());
		keyj = getAtomKey(_mol.getBond(i)->getAtomj());
		_mol.getBond(i)->calculateConstants(_params[keyi], _params[keyj]);
	}
	for (int i = 0; i < _mol.nBonds(); i++) {
		for (int j = (i + 1); j < _mol.nBonds(); j++) {
			if (_mol.getBond(i)->isAtomInBond(_mol.getBond(j)->getAtomi()) || _mol.getBond(i)->isAtomInBond(_mol.getBond(j)->getAtomj())) {
				Angle* angle = new Angle(_mol.getBond(i), _mol.getBond(j));
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

void UFF::calculateEnergy(bool gradiants) {
	_eBond = 0.0;
	_eAngle = 0.0;

	// Bond energy calculation
	for (int i = 0; i < _mol.nBonds(); i++) {
		_eBond += E_R(_mol.getBond(i));
	}
	// Angle energy calculation
	for (Angle* angle : _angles) {
		_eAngle += E_Theta(angle);
	}
	
}

double UFF::E_R(Bond* bond) {
	double r = bond->getLength();
	r = (r - bond->getR0());
	double r2 = r * r;
	return (bond->getForceConstant() * r2);
}

double UFF::E_Theta(Angle* angle) {
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

void UFF::clearAngles() {
	for (auto a : _angles) {
		delete a;
		a = 0;
	}
	_angles.clear();
}

std::string UFF::getAtomKey(Atom* atom) const {
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