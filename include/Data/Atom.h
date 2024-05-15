#pragma once

#include <map>
#include <string>
#include <vector>
#include "Data/api.h"
#include "Maths/Vector3.h"

#include "Data/AtomicData.h"

namespace ctkData {

	/*! \brief The basic atom class 
	* This contains all the information needed to describe a single atom instance. 
	*/
	class DATA_API Atom {
	public:
		//! Constructor -> sets atomic number and position in Cartesian space
		Atom(int a, double x, double y, double z);
		//! Constructor -> sets aotmic number via element symbal and position in Cartesian space 
		Atom(std::string s, double x, double y, double z);
		//! Default destructor
		~Atom() = default;
		
		//! Copy constructor  
		Atom(const Atom& atm);
		//! Copy Assignment operator 
		Atom& operator=(const Atom& atm);

		// Access functions 
		//! Returns the atomic number for this atom 
		const short getAtomicNumber() const;
		//! Returns the position of the atom as a Vector3 object reference 
		ctkMaths::Vector3& getPosition();									// Do we need both of these??
		//! Returns the position of the atom as a const Vector3 object reference
		const ctkMaths::Vector3& getPosition() const;
		//! Returns the element symbol for this atom
		const char* getSymbol() const;
		//! Returns the coordination of this atom 
		int coordination() const;
		//! Returns the number of single bonds attached to this atom 
		unsigned int nSingleBonds() const;
		//! Returns the number of double bonds attached to this atom 
		unsigned int nDoubleBonds() const;
		//! Returns the number of triple bonds attached to this atom 
		unsigned int nTripleBonds() const;
		//! Returns the total number of bonds attached to this atom 
		unsigned int nBonds() const;
		//! Returns whether the atom has been specified as aromatic or not  
		bool isAromatic() const;
		//! Returns whether the atom has been specified as an amide or not 
		bool isAmide() const;
		//! Returns the covalent Radii for this atom 
		float getCovalentRadii() const;
		//! Checks whehter a given atom is bonded to this atom 
		bool isConnected(const Atom* a) const;
		//! Checks whether a given atom is bonded via a double bond to this atom 
		bool isDouble(const Atom* a) const;
		//! Checks whether a given atom is bonded via a triple bond to this atom 
		bool isTriple(const Atom* a) const;
		//! Returns a const reference to the internal connections list vector 
		const std::vector<Atom*>& connections() const;
		//! Returns a SYBYL string representation for this atom 
		std::string getSYBYL() const;
		//! Returns the standard valence for a neutral instance of this atom 
		int standardValence() const;
		//! Get atomic mass 
		const double getMass() const;
#ifdef WITH_CTK_GRAPHICS
		//! Gets the default rgb colour value for this atom 
		const float* getColour() const;
#endif

		// set functions 
		//! Sets the atomic number
		void setAtomicNumber(int a);
		//! Sets the position in Cartesian space
		void updatePosition(const double x, const double y, const double z);
		//! Adds a new connection 
		bool addConnection(Atom* a);
		//! Adds a new connection whith a specified bond order 
		bool addConnection(Atom* a, int bo);
		//! Removes a given atom from the connections list 
		void removeConnection(Atom* a);
		//! Sets whether this atom is aromatic or not 
		void isAromatic(bool aromatic);
		//! Sets whether this atom is an amide or not 
		void isAmide(bool amide);
		//! Adds a string label containing more information on this atom 
		void addLabel(std::string label);

		// reset functions 
		//! Removes all connections to this atom 
		void resetBonding();

		//! Returns a basic string representation of this atom instance 
		std::string toString() const;


	private:
		short _a;
		short _charge{ 0 };


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
		static std::map<int, float> covRadiiDict;

		static AtomData::PeriodicTable periodicTable;
	};

}