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
		bool isConnected(const Atom* a) const;
		bool isDouble(const Atom* a) const;
		bool isTriple(const Atom* a) const;
		const std::vector<Atom*>& connections() const;
		std::string getSYBYL() const;
		int standardValence() const;

		// set functions 
		void setAtomicNumber(int a);
		void updatePosition(const double x, const double y, const double z);
		bool addConnection(Atom* a);
		bool addConnection(Atom* a, int bo);
		void removeConnection(Atom* a);
		void isAromatic(bool aromatic);
		void isAmide(bool amide);
		void addLabel(std::string label);

		// reset functions 
		void resetBonding();

		std::string toString() const;


	private:
		int _a;
		bool _isAromatic{ false };
		bool _isAmide{ false };
		ctkMaths::Vector3 _pos;
		std::vector<Atom*> _connections;
		std::vector<Atom*> _doubles; 
		std::vector<Atom*> _triples;
		std::vector<std::string> _labels;

		// make these const??? seems to break access functions
		static std::map<int, const char*> atmDict;
		static std::map<std::string, int> symbolDict; // could we get better performance with a const char* / has approach???
		static std::map<int, double> covRadiiDict;
	};

}