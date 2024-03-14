#pragma once

#ifdef _WIN32
#ifdef ctkForceField_EXPORTS
#define UFF_API __declspec(dllexport)
#else
#define UFF_API __declspec(dllimport)
#endif // ctkDataObjs_EXPORTS 
#else
#define UFF_API
#endif //_WIN32 

#include <map>
#include <string>

#include "ForceField.h"
#include "Data/Molecule.h"
#include "Data/Atom.h"
#include "ForceField/BondCalc.h"
#include "ForceField/AngleCalc.h"
#include "ForceField/NonBondCalc.h"
#include "ForceField/UFFParams.h"


class UFF_API UFF : protected ForceField {
public:
	UFF(ctkData::Molecule& mol);
	~UFF();

	void setupTerms();
	void runSteps(int steps);
	double energy() const;
	void calculateEnergy(bool gradients);


	// individual energy access functions 
	double getBondEnergy() const;
	double getAngleEnergy() const;
	double getDihedralEnergy() const;
	double getInversionEnergy() const;
	double getVDWEnergy() const;
	double getElectrostaticEnergy() const;

protected:
	void setParameters();
	

private:
	std::map<std::string, UFFParameters*> _params;
	double _eBond{ 0.0 };
	double _eAngle{ 0.0 };
	double _eDihedral{ 0.0 };
	double _eInversion{ 0.0 };
	double _eVdW{ 0.0 };
	double _eElectro{ 0.0 };

	std::vector<BondCalc*> _bonds;
	std::vector<AngleCalc*> _angles;
	std::vector<NonBond*> _nonBonded;

	std::string getAtomKey(ctkData::Atom* atom) const;

	double E_R(const BondCalc* bond);
	double E_Theta(const AngleCalc* angle);
	double E_VdW(const NonBond* vdw);

	void clearAngles();
	void clearBonds();
	void clearNonBonded();
};