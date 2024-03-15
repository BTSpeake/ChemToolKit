#include "ForceField/TorsionCalc.h"
#include "Maths/Vector3.h"

TorsionCalc::TorsionCalc(const BondCalc* bi, const BondCalc* bj, const BondCalc* bk)
	: _bi(bi), _bj(bj), _bk(bk) {

}

bool TorsionCalc::setupConstants(const UFFParameters* pj, const UFFParameters* pk) {

	int coordSum = _bj->getAtomi()->coordination() + _bj->getAtomj()->coordination();
	double vi = pj->Vi;
	double vj = pk->Vi;

	switch (coordSum) {
	case 6: 
		// Two sp3 centres 
		_n = 3; 
		_phi0 = 60.0;
		
		if (vi == 0 || vj == 0) {
			return false;
		}
		
		switch (_bj->getAtomi()->getAtomicNumber()) {
		case 8: 
			_n = 2; 
			_phi0 = 90.0;
			vi = 2.0;
			break;
		case 16: 
		case 34:
		case 52:
		case 84:
			_n = 2;
			_phi0 = 90.0;
			vi = 6.8;
		}

		switch (_bj->getAtomj()->getAtomicNumber()) {
		case 8:
			_n = 2;
			_phi0 = 90.0;
			vj = 2.0;
			break;
		case 16:
		case 34:
		case 52:
		case 84:
			_n = 2;
			_phi0 = 90.0;
			vj = 6.8;
		}

		_V = 0.5 * sqrt(vi * vj);
		break;

	case 5:
		// sp3 - sp2
		_phi0 = 0.0; 
		_n = 6; 
		_V = 0.5;

		if (_bj->getAtomi()->coordination()) {
			switch (_bj->getAtomi()->getAtomicNumber()) {
			case 8:
			case 16:
			case 34:
			case 52:
			case 84:
				_n = 2; 
				_phi0 = 90.0;
			}
		}
		else {
			switch (_bj->getAtomj()->getAtomicNumber()) {
			case 8:
			case 16:
			case 34:
			case 52:
			case 84:
				_n = 2;
				_phi0 = 90.0;
			}
		}
		break;

	case 4: 
		// sp2 - sp2
		double bo;
		if (_bj->getAtomi()->isAromatic() || _bj->getAtomj()->isAromatic()) {
			bo = 1.5;
		}
		else if(_bj->getAtomi()->isAmide() || _bj->getAtomj()->isAmide()) {
			bo = 1.41;
		}
		else {
			bo = _bj->getBondOrder();
		}
		_phi0 = 180.0;
		_n = 2;
		_V = 2.5 * sqrt(pj->Uj * pk->Uj) * (1 + 4.18 * log(bo));
		break;

	default: 
		return false;
	}

	if (abs(_V) < 1e-8) {
		return false;
	}

	_phi0 = std::cos(_n * _phi0);
	return true;
}

double TorsionCalc::getPhi() const {
	const ctkMaths::Vector3& b1 = _bi->getBondVector(); 
	const ctkMaths::Vector3& b2 = _bj->getBondVector();
	const ctkMaths::Vector3& b3 = _bk->getBondVector();

	const ctkMaths::Vector3 n1 = ctkMaths::cross(b1, b2);
	const ctkMaths::Vector3 n2 = ctkMaths::cross(b2, b3); 

	return ctkMaths::dot(n1, n2) / (n1.normal() * n2.normal()); 
}