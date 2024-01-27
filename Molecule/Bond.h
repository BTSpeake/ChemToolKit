#pragma once

#include "Atom.h"
#include "../Maths/Vector3.h"

class Bond {
public:
	Bond(Atom* atmi, Atom* atmj);
	~Bond() = default;

	Bond(const Bond&) = delete;
	Bond& operator=(const Bond&) = delete;

	// Processing functions 
	void calculateDistance();

	// Set functions 
	void setBondOrder(int bo) { _bo = bo; };

	// access functions 
	double getLength() const { return _l; };
	Atom* getAtomi() const { return _atmi; };
	Atom* getAtomj() const { return _atmj; };
	int getBondOrder() const { return _bo; };
	Vector3 getBondVector() const { return _atmj->getPosition() - _atmi->getPosition(); };
	bool isAtomInBond(const Atom* atm) const { return (atm == _atmi) || (atm == _atmj); };

private:
	Atom* _atmi;
	Atom* _atmj;
	int _bo{ 1 };
	double _l;
};