#pragma once 
#include "Data/Atom.h"
#include "ForceField/UFFParams.h"

class TorsionCalc {
public:
	TorsionCalc(const ctkData::Atom* ai, const ctkData::Atom* aj, const ctkData::Atom* ak, const ctkData::Atom* al); 
	~TorsionCalc() = default;

	TorsionCalc(const TorsionCalc&) = delete; 
	TorsionCalc& operator=(const TorsionCalc&) = delete; 

	bool setupConstants(const UFFParameters* pj, const UFFParameters* pk); 

	double getPhi() const;
	const int& getPeriodicity() const { return _n; }
	const double& getPhi0() const { return _phi0; }
	const double& getV() const { return _V; }

private:
	const ctkData::Atom* _ai; 
	const ctkData::Atom* _aj; 
	const ctkData::Atom* _ak; 
	const ctkData::Atom* _al;
	int _n{ 0 };
	double _phi0{ 0.0 };
	double _V{ 0.0 };
};