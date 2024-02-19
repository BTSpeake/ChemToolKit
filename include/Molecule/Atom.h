#pragma once

#include <map>
#include <string>

#include "Maths/Vector3.h"

class Atom {
public:
	Atom(int a, double x, double y, double z);
	Atom(std::string s, double x, double y, double z);
	~Atom() = default;

	// Copy and assignment 
	Atom(const Atom& atm);
	Atom& operator=(const Atom& atm);

	// Access functions 
	int getAtomicNumber() const { return _a; };
	const Vector3& getPosition() const { return _pos; };
	const char* getSymbol() const { return Atom::atmDict[_a]; };
	int coordination() const;
	unsigned int nSingleBonds() const { return _nSingle; };
	unsigned int nDoubleBonds() const { return _nDouble; };
	unsigned int nTripleBonds() const { return _nTriple; };
	unsigned int nBonds() const { return _nSingle + _nDouble + _nTriple; };
	bool isAromatic() const { return _isAromatic; };
	double getCovalentRadii() const { return covRadiiDict[_a]; }

	// set functions 
	void addSingleBond() { _nSingle++; };
	void addDoubleBond() { _nDouble++; };
	void addTripleBond() { _nTriple++; };
	void removeSingleBond() { _nSingle--; };
	void removeDoubleBond() { _nDouble--; };
	void removeTripleBond() { _nTriple--; };
	void setAromatic(bool aromatic) { _isAromatic = aromatic; };

	// reset functions 
	void resetBonding() {
		_nSingle = 0;
		_nDouble = 0;
		_nTriple = 0;
	}


private:
	int _a;
	unsigned int _nSingle{ 0 };
	unsigned int _nDouble{ 0 };
	unsigned int _nTriple{ 0 };
	bool _isAromatic{ false };
	Vector3 _pos;

	// make these const??? seems to break access functions
    static std::map<int, const char*> atmDict; 
	static std::map<std::string, int> symbolDict; // could we get better performance with a const char* / has approach???
	static std::map<int, double> covRadiiDict;
};