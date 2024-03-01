#include "ForceField/BondCalc.h"

#include <cmath>

BondCalc::BondCalc(ctkData::Atom* atmi, ctkData::Atom* atmj)
	: _atmi(atmi), _atmj(atmj) {
	calculateDistance();
}

void BondCalc::calculateDistance() {
	ctkMaths::Vector3 bv = getBondVector();
	_l = bv.normal();
}

void BondCalc::calculateConstants(UFFParameters* pi, UFFParameters* pj) {
	_r0 = pi->r + pj->r;
	if (_bo > 1) {
		double rbo = -0.1332 * (_r0)*std::log(_bo);
		_r0 += rbo;
	}
	double ren = (sqrt(pi->chi) - sqrt(pj->chi));
	ren = pi->r * pj->r * ren * ren;
	ren /= ((pi->chi * pi->r) + (pj->chi * pj->r));
	_r0 -= ren;

	_k = 0.5 * 664.12 * (pi->z * pj->z) / (_r0 * _r0 * _r0);
}