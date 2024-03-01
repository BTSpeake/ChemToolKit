#pragma once

#include "Data/Molecule.h"


class ForceField {
public:
	ForceField(ctkData::Molecule& mol) : _mol(mol) {};
	~ForceField() {};
	
	ForceField(const ForceField*) = delete;
	ForceField& operator=(const ForceField&) = delete;

	// Abstract public functions
	virtual void runSteps(int steps) = 0;
	virtual double energy() = 0;

	// Basic access functions
	ctkData::Molecule& getMolecule() { return _mol; };

protected:
	double _energy{ 0.0 };
	ctkData::Molecule& _mol;

	virtual void calculateEnergy(bool gradients) = 0;
	virtual void setParameters() = 0;
};