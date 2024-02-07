#pragma once

#include <map>
#include <string>

#include "ForceField.h"
#include "../Molecule/Molecule.h"
#include "../Molecule/Atom.h"
#include "BondCalc.h"
#include "AngleCalc.h"
#include "UFFParams.h"


class UFF : protected ForceField {
public:
	UFF(Molecule& mol);
	~UFF();

	void setupTerms();
	void runSteps(int steps);
	double energy() { return _eBond + _eAngle + _eDihedral + _eInversion + _eVdW + _eElectro; };
	void calculateEnergy(bool gradients);


	// individual energy access functions 
	double getBondEnergy() const { return _eBond; };
	double getAngleEnergy() const { return _eAngle; };
	double getDihedralEnergy() const { return _eDihedral; };
	double getInversionEnergy() const { return _eInversion; };
	double getVDWEnergy() const { return _eVdW; };
	double getElectrostaticEnergy() const { return _eElectro; };

protected:
	void setParameters();
	

private:
	std::map<std::string, UFFParameters*> _params;
	double _eBond{ 0.0 };
	double _eAngle{ 0.0 };
	double _eDihedral{ 0.0 };
	double _eInversion{ 0.0 };
	double _eVdW{ 0.0 };
	double _eElectro{ 0.0 };

	std::vector<BondCalc*> _bonds;
	std::vector<AngleCalc*> _angles;

	std::string getAtomKey(Atom* atom) const;

	double E_R(BondCalc* bond);
	double E_Theta(AngleCalc* angle);

	void clearAngles();
	void clearBonds();
};