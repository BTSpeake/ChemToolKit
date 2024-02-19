#pragma once 

#include <map>
#include <string>

#include "Molecule/Atom.h"
#include "ForceField/BondCalc.h"
#include "ForceField/UFFParams.h"

class AngleCalc {
public:
	AngleCalc(BondCalc* bi, BondCalc* bj);
	~AngleCalc() = default;

	AngleCalc(const AngleCalc&) = delete;
	AngleCalc& operator=(const AngleCalc&) = delete;

	void calculateConstants(UFFParameters* pi, UFFParameters* pj, UFFParameters* pk);

	BondCalc* getBondi() const { return _bi; };
	BondCalc* getBondj() const { return _bj; };
	Atom* getAtomi() const { return _atmi; };
	Atom* getAtomj() const { return _atmj; };
	Atom* getAtomk() const { return _atmk; };

	double getForceConstant() const { return _k; };
	double getTheta() const { return _theta; };
	double getTheta0() const { return _theta0; };


private:
	BondCalc* _bi;
	BondCalc* _bj;
	Atom* _atmi = 0;
	Atom* _atmj = 0; 
	Atom* _atmk = 0;
	double _theta{ 0.0 };
	double _theta0{ 0.0 };
	double _k{ 0.0 };
};