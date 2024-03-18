#include "ForceField/TorsionCalc.h"
#include "Maths/Vector3.h"

TorsionCalc::TorsionCalc(const ctkData::Atom* ai, const ctkData::Atom* aj, const ctkData::Atom* ak, const ctkData::Atom* al)
	: _ai(ai), _aj(aj), _ak(ak), _al(al) {

}

bool TorsionCalc::setupConstants(const UFFParameters* pj, const UFFParameters* pk) {

	int coordSum = _aj->coordination() + _ak->coordination();
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
		
		switch (_aj->getAtomicNumber()) {
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

		switch (_ak->getAtomicNumber()) {
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

		if (_aj->coordination() == 2) {
			switch (_aj->getAtomicNumber()) {
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
			switch (_ak->getAtomicNumber()) {
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
		if (_aj->isAromatic() || _ak->isAromatic()) {
			bo = 1 + (4.18 * log(1.5));
		}
		else if(_aj->isAmide() || _ak->isAmide()) {
			bo = 1 + (4.18 * log(1.41));
		}
		else if (_aj->isDouble(_ak)) {
			bo = 1 + (4.18 * log(2));
		}
		else if (_aj->isTriple(_ak)) {
			bo = 1 + (4.18 * log(3));
		}
		else {
			bo = 1;
		}
		_phi0 = 180.0;
		_n = 2;
		_V = 2.5 * sqrt(pj->Uj * pk->Uj) * (bo);
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
	const ctkMaths::Vector3 b1 = _aj->getPosition() - _ai->getPosition();
	const ctkMaths::Vector3 b2 = _ak->getPosition() - _aj->getPosition();
	const ctkMaths::Vector3 b3 = _al->getPosition() - _ak->getPosition();

	const ctkMaths::Vector3 n1 = ctkMaths::cross(b1, b2);
	const ctkMaths::Vector3 n2 = ctkMaths::cross(b2, b3); 

	return ctkMaths::dot(n1, n2) / (n1.normal() * n2.normal()); 
}