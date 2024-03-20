#pragma once 

#ifdef _WIN32
#ifdef ctkDataObjs_EXPORTS
#define MOLECULE_API __declspec(dllexport)
#else
#define MOLECULE_API __declspec(dllimport)
#endif // ctkDataObjs_EXPORTS 
#else
#define MOLECULE_API
#endif //_WIN32 

#include <vector>
#include "Data/Atom.h"

namespace ctkData {

	class MOLECULE_API Molecule {
	public:
		Molecule();
		~Molecule();
		Molecule(const Molecule& mol) = delete;
		Molecule& operator=(const Molecule& mol) = delete;

		// get functions for atoms/bonds
		int nAtoms() const;
		int nBonds() const;
		Atom* getAtom(int i) const;
		std::vector<Atom*>::const_iterator getAtomIt(int i) const;
		bool connected(const int i, const int j) const;
		bool connected13(const int i, const int j) const;

		// get functions for molecule properties 
		int getCharge() const;
		double getSpinProjection() const;
		int getMultiplicity() const;
		const ctkMaths::Vector3& getCoM() const;

		// set functions atoms/bonds 
		void addAtom(int a, double x, double y, double z);
		void addAtom(std::string s, double x, double y, double z);
		void addBond(int i, int j, int bo = 1);

		// set functions properties 
		void setCharge(int charge);
		void setSpinProjection(double sp);
		void setMultiplicity(double m);

		// processing functions 
		void calculateBonding();
		void calculateCoM();
		void centreOnOrigin();
		double calculateNNR() const;

		// Utility functions
		void clearAtoms();
		void clearBonds();

		std::string toString() const;
		std::string atomsList() const;

	private:
		int _charge{ 0 };
		double _spinProj{ 0.0 };
		ctkMaths::Vector3 CoM;
		std::vector<Atom*> _atoms;
	};

}