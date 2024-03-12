#pragma once

#ifdef _WIN32
#ifdef ctkDataObjs_EXPORTS
#define ATOM_API __declspec(dllexport)
#else
#define ATOM_API __declspec(dllimport)
#endif // ctkDataObjs_EXPORTS 
#else
#define ATOM_API
#endif //_WIN32 


#include <map>
#include <string>
#include <vector>
#include "Maths/Vector3.h"

namespace ctkData {

	class ATOM_API Atom {
	public:
		Atom(int a, double x, double y, double z);
		Atom(std::string s, double x, double y, double z);
		//~Atom() = default;

		// Copy and assignment 
		Atom(const Atom& atm);
		Atom& operator=(const Atom& atm);

		// Access functions 
		int getAtomicNumber() const;
		ctkMaths::Vector3& getPosition();
		const ctkMaths::Vector3& getPosition() const;
		const char* getSymbol() const;
		int coordination() const;
		unsigned int nSingleBonds() const;
		unsigned int nDoubleBonds() const;
		unsigned int nTripleBonds() const;
		unsigned int nBonds() const;
		bool isAromatic() const;
		bool isAmide() const;
		double getCovalentRadii() const;
		bool isConnected(const int i) const;
		const std::vector<int>& connections() const;
		std::string getSYBYL() const;

		// set functions 
		void setAtomicNumber(int a);
		void updatePosition(const double x, const double y, const double z);
		bool addConnection(const int i);
		//void addSingleBond();
		void addDoubleBond();
		void addTripleBond();
		//void removeSingleBond();
		void removeDoubleBond();
		void removeTripleBond();
		void isAromatic(bool aromatic);
		void isAmide(bool amide);
		void addLabel(std::string label);

		// reset functions 
		void resetBonding();

		std::string toString() const;


	private:
		int _a;
		unsigned int _nDouble{ 0 };
		unsigned int _nTriple{ 0 };
		bool _isAromatic{ false };
		bool _isAmide{ false };
		ctkMaths::Vector3 _pos;
		std::vector<int> _connections;
		std::vector<std::string> _labels;

		// make these const??? seems to break access functions
		static std::map<int, const char*> atmDict;
		static std::map<std::string, int> symbolDict; // could we get better performance with a const char* / has approach???
		static std::map<int, double> covRadiiDict;
	};

}