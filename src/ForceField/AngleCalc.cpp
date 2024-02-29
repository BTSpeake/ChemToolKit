#include "ForceField/AngleCalc.h"
#include "Maths/Vector3.h"

#include <cmath>

AngleCalc::AngleCalc(BondCalc* bi, BondCalc* bj) : _bi(bi), _bj(bj) {

	if (_bi->getAtomi() == _bj->getAtomj()) {
		_atmj = _bi->getAtomi();
		_atmi = _bi->getAtomj();
		_atmk = _bj->getAtomi();

	}
	else if (_bi->getAtomj() == _bj->getAtomi()) {
		_atmj = _bi->getAtomj();
		_atmi = _bi->getAtomi();
		_atmk = _bj->getAtomj();

	}
	else if (_bi->getAtomj() == _bj->getAtomj()) {
		_atmj = _bi->getAtomj();
		_atmi = _bi->getAtomi();
		_atmk = _bj->getAtomi();
	}
	else {
		_atmj = _bi->getAtomi();
		_atmi = _bi->getAtomj();
		_atmk = _bj->getAtomj();
	}
}

void AngleCalc::calculateConstants(UFFParameters* pi, UFFParameters* pj, UFFParameters* pk) {
	ctkMaths::Vector3 v1 = _atmi->getPosition() - _atmj->getPosition();
	ctkMaths::Vector3 v2 = _atmk->getPosition() - _atmj->getPosition();



	double l1 = v1.normal();
	double l2 = v2.normal();
	double d = dot(v1, v2) / (l1 * l2);

	if (d < -1.0) { d = -1.0; }
	else if (d > 1.0) { d = 1.0; }

	_theta = std::acos(d);
	_theta0 = pj->theta * 0.01745329252; // convert to radians 

	double ct0 = std::cos(_theta0);
	double rijk = _bi->getR0() * _bj->getR0();
	double rik2 = (_bi->getR0() * _bi->getR0()) + (_bj->getR0() * _bj->getR0()) - (2 * rijk * std::cos(_theta));
	double rik5 = rik2 * rik2 * std::sqrt(rik2);
	_k = 664.12 * (pi->z * pk->z) / rik5;
	_k *= ((3 * rijk * (1 - (ct0 * ct0))) - (rik2 * ct0));
}