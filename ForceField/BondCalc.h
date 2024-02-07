#pragma once

#include "../Molecule/Atom.h"
#include "../Maths/Vector3.h"
#include "../ForceField/UFFParams.h"

class BondCalc {
public:
	BondCalc(Atom* atmi, Atom* atmj);
	~BondCalc() = default;

	BondCalc(const BondCalc&) = delete;
	BondCalc& operator=(const BondCalc&) = delete;

	// Processing functions 
	void calculateDistance();

	// Set functions 
	void setBondOrder(int bo) { _bo = bo; };
	void calculateConstants(UFFParameters* pi, UFFParameters* pj);

	// access functions 
	double getLength() const { return _l; };
	Atom* getAtomi() const { return _atmi; };
	Atom* getAtomj() const { return _atmj; };
	int getBondOrder() const { return _bo; };
	Vector3 getBondVector() const { return _atmj->getPosition() - _atmi->getPosition(); };
	bool isAtomInBond(const Atom* atm) const { return (atm == _atmi) || (atm == _atmj); };

	double getR0() const { return _r0; };
	double getForceConstant() const { return _k; };


private:
	Atom* _atmi;
	Atom* _atmj;
	int _bo{ 1 };
	double _l;

	double _r0;
	double _k;
};