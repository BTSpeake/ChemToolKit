#pragma once 

#include <map>
#include <string>

#include "Atom.h"
#include "Bond.h"
#include "../ForceField/UFFParams.h"

class Angle {
public:
	Angle(Bond* bi, Bond* bj);
	~Angle() = default;

	Angle(const Angle&) = delete;
	Angle& operator=(const Angle&) = delete;

	void calculateConstants(UFFParameters* pi, UFFParameters* pj, UFFParameters* pk);

	Bond* getBondi() const { return _bi; };
	Bond* getBondj() const { return _bj; };
	Atom* getAtomi() const { return _atmi; };
	Atom* getAtomj() const { return _atmj; };
	Atom* getAtomk() const { return _atmk; };

	double getForceConstant() const { return _k; };
	double getTheta() const { return _theta; };
	double getTheta0() const { return _theta0; };


private:
	Bond* _bi;
	Bond* _bj;
	Atom* _atmi = 0;
	Atom* _atmj = 0; 
	Atom* _atmk = 0;
	double _theta{ 0.0 };
	double _theta0{ 0.0 };
	double _k{ 0.0 };
};