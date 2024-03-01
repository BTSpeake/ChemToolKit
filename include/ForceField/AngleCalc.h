#pragma once 

#include <map>
#include <string>

#include "Data/Atom.h"
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
	ctkData::Atom* getAtomi() const { return _atmi; };
	ctkData::Atom* getAtomj() const { return _atmj; };
	ctkData::Atom* getAtomk() const { return _atmk; };

	double getForceConstant() const { return _k; };
	double getTheta() const { return _theta; };
	double getTheta0() const { return _theta0; };


private:
	BondCalc* _bi;
	BondCalc* _bj;
	ctkData::Atom* _atmi = 0;
	ctkData::Atom* _atmj = 0;
	ctkData::Atom* _atmk = 0;
	double _theta{ 0.0 };
	double _theta0{ 0.0 };
	double _k{ 0.0 };
};