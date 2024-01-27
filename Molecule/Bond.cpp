#include "Bond.h"

Bond::Bond(Atom* atmi, Atom* atmj) 
	: _atmi(atmi), _atmj(atmj) {
	calculateDistance();
}

void Bond::calculateDistance() {
	Vector3 bv = getBondVector();
	_l = bv.normal();
}