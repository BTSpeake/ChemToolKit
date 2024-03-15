#pragma once 
#include "ForceField/BondCalc.h"
#include "ForceField/UFFParams.h"

class TorsionCalc {
public:
	TorsionCalc(const BondCalc* bi, const BondCalc* bj, const BondCalc* bk); 
	~TorsionCalc() = default;

	TorsionCalc(const TorsionCalc&) = delete; 
	TorsionCalc& operator=(const TorsionCalc&) = delete; 

	bool setupConstants(const UFFParameters* pj, const UFFParameters* pk); 

	double getPhi() const;
	const int& getPeriodicity() const { return _n; }
	const double& getPhi0() const { return _phi0; }
	const double& getV() const { return _V; }

private:
	const BondCalc* _bi; 
	const BondCalc* _bj; 
	const BondCalc* _bk;
	int _n; 
	double _phi0;
	double _V;
};