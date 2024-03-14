#pragma once 

#include "Data/Atom.h"
#include "ForceField/UFFParams.h"

class NonBond {
public:
	NonBond(const ctkData::Atom* ai, const ctkData::Atom* aj) : _ai(ai), _aj(aj) {}
	~NonBond() = default;

	NonBond(const NonBond&) = delete;
	NonBond operator=(const NonBond&) = delete;

	void setupTerms(const UFFParameters* pi, const UFFParameters* pj, bool electrostatic);

	const ctkData::Atom* getAtomi() const { return _ai; }
	const ctkData::Atom* getAtomj() const { return _aj; }

	double _xij6{ 0.0 };
	double _xij12{ 0.0 };
	double _dij{ 0.0 };

private:
	const ctkData::Atom* _ai;
	const ctkData::Atom* _aj;
	bool _electrostatic{ false };

};