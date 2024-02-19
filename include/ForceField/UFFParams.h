#pragma once

#include <string>

class UFFParameters {
public:
	UFFParameters(std::string key, double* vals);
	~UFFParameters();
	UFFParameters(const UFFParameters&) = delete;
	UFFParameters& operator=(const UFFParameters&) = delete;

	std::string _key;
	double r, theta, x, d, zeta, z, Vi, Uj, chi, hard, radius;

};