#pragma once 

#include <vector>
#include "Data/api.h"
#include "Data/Atom.h"
#include "Data/VolumeData.h"

namespace ctkData {

	class DATA_API Model {
	public:
		//! Constructor 
		Model();
		//! Constructor which sets a title string 
		Model(std::string title);
		//! Destructor 
		~Model();
		//! Copy Constructor 
		Model(const Model& mol);
		//! Copy assignment operator 
		Model& operator=(const Model& mol) = delete;

		// get functions for atoms/bonds
		//! Return the total number of Atoms in th model
		int nAtoms() const;
		//! Return the total number of bonds in the model 
		int nBonds() const;
		//! Return a pointer to the atom object at index [i]
		Atom* getAtom(int i) const;
		//! Get an const_iterator to the atom at index [i]
		std::vector<Atom*>::const_iterator getAtomIt(int i) const;
		//! Check whether atoms at indexes [i] and [j] are connected
		bool connected(const int i, const int j) const;
		//! Check whether atoms at indexes [i] and [j] are 1-3 connected
		bool connected13(const int i, const int j) const;

		// get functions for Model properties 
		//! Return the global charge for the model 
		int getCharge() const;
		//! Return the global spin projection for the model 
		double getSpinProjection() const;
		//! Return the global multiplicity for the model 
		int getMultiplicity() const;
		//! Return the centre of mass for the total model 
		const ctkMaths::Vector3& getCoM() const;
		//! Returns a given volumetric data set attached to the model 
		std::shared_ptr<VolumeData> getVolumetricDataSet(const int i);

		// set functions atoms/bonds 
		//! Adds a new atom with atomic number [a] at position ([x], [y], [z])
		void addAtom(int a, double x, double y, double z);
		//! Adds a new atom with element symbol [s] at at position ([x], [y], [z])
		void addAtom(std::string s, double x, double y, double z);
		//! Adds a new bond between atoms at indexes [i] and [j] with bond order [bo]
		void addBond(int i, int j, int bo = 1);

		// set functions properties 
		//! Sets the global charge of the model 
		void setCharge(int charge);
		//! Sets the global spin projection of the model 
		void setSpinProjection(double sp);
		//! Sets the global spin projection of the model based on a multiplicity value
		void setMultiplicity(double m);
		//! Adds an associated volumetric data set (such as electronic density values) to the model 
		void addVolumetricDataSet(std::shared_ptr<VolumeData> data);

		// processing functions 
		//! Generates an approximate bonding model based in covalent radii
		void calculateBonding(const double scale = 1.0);
		//! Calculates the centre of mass for the total model 
		void calculateCoM();
		//! Moves the total model so that the centre of mass lies on the Cartesian origin 
		void centreOnOrigin();
		//! Calculates the total nuclear-nuclear repulsion within the model 
		double calculateNNR() const;

		// Utility functions]
		//! Resets the model object to initial settings 
		void reset();
		//! Resets the atom and bonding information 
		void clearAtoms();
		//! Resets the bonding information
		void clearBonds();

		//! Returns a string representation of the model instance 
		std::string toString() const;
		//! Returns a string representation of the atoms contained within the model instance 
		std::string atomsList() const;
		//! Returns the models title 
		std::string getTitle() const;
		//! Sets the model's title 
		void setTitle(std::string title);

	private:
		int _charge{ 0 };
		double _spinProj{ 0.0 };
		ctkMaths::Vector3 CoM;
		std::vector<Atom*> _atoms;
		std::string _title;
		std::vector<std::shared_ptr<VolumeData>> _gridData;
	};

}