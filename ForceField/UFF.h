#pragma once

#include <map>
#include <string>

#include "ForceField.h"
#include "../Molecule/Molecule.h"
#include "../Molecule/Bond.h"
#include "../Molecule/Angle.h"
#include "UFFParams.h"


class UFF : protected ForceField {
public:
	UFF(Molecule& mol);
	~UFF();

	
	void runSteps(int steps);
	double energy();

	// individual energy access functions 
	double getBondEnergy() const { return _eBond; };
	double getAngleEnergy() const { return _eAngle; };
	double getDihedralEnergy() const { return _eDihedral; };
	double getInversionEnergy() const { return _eInversion; };
	double getVDWEnergy() const { return _eVdW; };
	double getElectrostaticEnergy() const { return _eElectro; };

protected:
	void setParameters();
	void setupTerms();
	void calculateEnergy(bool gradients);

private:
	std::map<std::string, UFFParameters*> _params;
	double _eBond{ 0.0 };
	double _eAngle{ 0.0 };
	double _eDihedral{ 0.0 };
	double _eInversion{ 0.0 };
	double _eVdW{ 0.0 };
	double _eElectro{ 0.0 };

	std::vector <Angle*> _angles;

	double E_R(Bond* bond);
	double E_Theta(Angle* angle);
};