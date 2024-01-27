#include <iostream>

#include "Molecule/Molecule.h"

int main()
{
	Molecule mol;
	mol.addAtom(1, 0.0, 0.0, 0.7);
	mol.addAtom(1, 0.0, 0.0, 0.0);
	mol.addBond(0, 1);

	std::cout << "Creating H2 Molecule" << std::endl;
	std::cout << "Number of Atoms: " << mol.nAtoms() << std::endl;
	std::cout << "Number of Bonds: " << mol.nBonds() << std::endl;
}
