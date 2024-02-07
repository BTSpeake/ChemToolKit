#include <iostream>

#include "Molecule/Molecule.h"
#include "ForceField/UFF.h"
#include "FileIO/FileControl.h"

int main()
{
	// manually create molecule
	Molecule mol;
	// Hydrogen Molecule 
	mol.addAtom(1, 0.0, 0.0, 0.7);
	mol.addAtom(1, 0.0, 0.0, 0.0);
	mol.addBond(0, 1);

	std::cout << "Creating H2 Molecule" << std::endl;
	std::cout << "Number of Atoms: " << mol.nAtoms() << std::endl;
	std::cout << "Number of Bonds: " << mol.nBonds() << std::endl;
	{
		UFF uff(mol);
		uff.setupTerms();
		uff.calculateEnergy(false);
		std::cout << "Total Energy: " << uff.energy() << std::endl;
		std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
		std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
	}
	// Use file parsing 
	FileControl fileControl;

	std::cout << '\n';
	std::cout << "Reading XYZ File:" << std::endl;
	Molecule mol2;
	if (fileControl.read("C:\\Users\\sil23665\\Documents\\Nottingham\\questview\\tests\\Resources\\Water_Trimer.xyz", mol2)) {
		//fio.read(mol2);
		std::cout << "Number of Atoms: " << mol2.nAtoms() << std::endl;
		std::cout << "Number of Bonds: " << mol2.nBonds() << std::endl;
		std::cout << mol2.getAtom(5)->getSymbol() << std::endl;
	}
	else {
		std::cout << "ERROR::File doesn't exist" << std::endl;
	}
	mol2.calculateBonding();
	std::cout << "Number of Bonds: " << mol2.nBonds() << std::endl;
	{
		UFF uff(mol2);
		uff.setupTerms();
		uff.calculateEnergy(false);
		std::cout << "Total Energy: " << uff.energy() << std::endl;
		std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
		std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
	}

	std::cout << '\n';
	std::cout << "Reading PDB File:" << std::endl; 
	Molecule mol3; 
	if (fileControl.read("C:\\Users\\sil23665\\Documents\\Nottingham\\questview\\tests\\Resources\\ala_phe_ala.pdb", mol3)) {
		//fpdb.read(mol3);
		std::cout << "Number of Atoms: " << mol3.nAtoms() << std::endl;
		std::cout << "Number of Bonds: " << mol3.nBonds() << std::endl;
		std::cout << mol3.getAtom(5)->getSymbol() << std::endl;
	}
	//{
	//	UFF uff(mol3);
	//	uff.setupTerms();
	//	uff.calculateEnergy(false);
	//	std::cout << "Total Energy: " << uff.energy() << std::endl;
	//	std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
	//	std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
	//}

}
