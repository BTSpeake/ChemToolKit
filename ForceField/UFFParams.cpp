#include "UFFParams.h"

UFFParameters::UFFParameters(std::string key, double* vals) {
	_key = key;
	r = vals[0];
	theta = vals[1];
	x = vals[2];
	d = vals[3];
	zeta = vals[4];
	z = vals[5];
	Vi = vals[6];
	Uj = vals[7];
	chi = vals[8];
	hard = vals[9];
	radius = vals[10];
}

UFFParameters::~UFFParameters() {}