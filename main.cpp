#include <iostream>

#include "Molecule/Molecule.h"
#include "ForceField/UFF.h"

int main()
{
	Molecule mol;
	// Hydrogen Molecule 
	//mol.addAtom(1, 0.0, 0.0, 0.7);
	//mol.addAtom(1, 0.0, 0.0, 0.0);
	//mol.addBond(0, 1);

	// Water Molecule 
	mol.addAtom(8, -1.6527176, 0.2922510, -0.2322186);
	mol.addAtom(1, -2.3904046, 0.6644842, 0.2209743);
	mol.addAtom(1, -0.9705371, 0.9532540, -0.2350245);
	mol.addBond(0, 1, 1);
	mol.addBond(0, 2, 1);

	std::cout << "Creating H2 Molecule" << std::endl;
	std::cout << "Number of Atoms: " << mol.nAtoms() << std::endl;
	std::cout << "Number of Bonds: " << mol.nBonds() << std::endl;

	UFF uff(mol);
	uff.setupTerms();
	uff.calculateEnergy(false);
	std::cout << "Total Energy: " << uff.energy() << std::endl;
	std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
	std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
}
