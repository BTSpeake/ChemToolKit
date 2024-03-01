#pragma once 

#include <vector>

#include "Molecule/Atom.h"
//#include "Bond.h"
//#include "Angle.h"

struct Bond {
	Bond(int i, int j, int o) : _i(i), _j(j), _o(o) {};
	unsigned int _i;
	unsigned int _j; 
	int _o;
};

class Molecule {
public:
	Molecule();
	~Molecule();
	Molecule(const Molecule& mol) = delete;
	Molecule& operator=(const Molecule& mol) = delete;

	// get functions for atoms/bonds
	int nAtoms() const { return _atoms.size(); };
	int nBonds() const { return _bonds.size(); };
	Atom* getAtom(int i) const { return _atoms[i]; };
	Bond* getBond(int i) const { return _bonds[i]; };

	// get functions for molecule properties 
	int getCharge() const { return _charge; };
	double getSpinProjection() const { return _spinProj; };
	int getMultiplicity() const { return static_cast<int>(round(2 * _spinProj)) + 1; };
	const ctkMaths::Vector3& getCoM() const { return CoM; };

	// set functions atoms/bonds 
	void addAtom(int a, double x, double y, double z);
	void addAtom(std::string s, double x, double y, double z);
	void addBond(int i, int j, int bo = 1) {
		if (i < nAtoms() && j < nAtoms()) { _bonds.push_back(new Bond(i, j, bo)); }
	};

	// set functions properties 
	void setCharge(int charge) { _charge = charge; };
	void setSpinProjection(double sp) { _spinProj = sp; };
	void setMultiplicity(double m) { _spinProj = (m - 1) / 2; };

	// processing functions 
	void calculateBonding();
	void calculateCoM();
	void centreOnOrigin();

	// Utility functions
	void clearAtoms();
	void clearBonds();

	std::string toString() const;
	std::string atomsList() const;

private:
	int _charge{ 0 };
	double _spinProj{ 0.0 };
	ctkMaths::Vector3 CoM;
	std::vector<Atom*> _atoms;
	std::vector<Bond*> _bonds;
};