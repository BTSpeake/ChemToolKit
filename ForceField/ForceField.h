#pragma once

#include "../Molecule/Molecule.h"


class ForceField {
public:
	ForceField(Molecule& mol) : _mol(mol) {};
	~ForceField() {};
	
	ForceField(const ForceField*) = delete;
	ForceField& operator=(const ForceField&) = delete;

	// Abstract public functions
	virtual void runSteps(int steps) = 0;
	virtual double energy() = 0;

	// Basic access functions
	Molecule& getMolecule() { return _mol; };

protected:
	double _energy{ 0.0 };
	Molecule& _mol;

	virtual void calculateEnergy(bool gradients) = 0;
	virtual void setParameters() = 0;
};