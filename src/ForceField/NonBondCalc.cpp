#include "ForceField/NonBondCalc.h"


void NonBond::setupTerms(const UFFParameters* pi, const UFFParameters* pj, bool electrostatic) {
	_electrostatic = electrostatic;

	double xij2 = pi->x * pj->x;
	_xij6 = xij2 * xij2 * xij2;
	_xij12 = _xij6 * _xij6;
	_dij = sqrt(pi->d * pj->d);
}