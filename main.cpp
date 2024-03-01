#include <iostream>
#include <cassert>

#include "Data/Molecule.h"
#include "ForceField/UFF.h"
#include "FileIO/FileControl.h"

#include "Maths/Vector3.h"
#include "Maths/Matrix33.h"

using ctkData::Molecule;

void testMaths();


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
	ctkIO::FileControl fileControl;

	std::cout << '\n';
	std::cout << "Reading XYZ File:" << std::endl;
	Molecule mol2;
	if (fileControl.read("tests/Water_Trimer.xyz", mol2)) {
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
	if (fileControl.read("tests/ala_phe_ala.pdb", mol3)) {
		//fpdb.read(mol3);
		std::cout << "Number of Atoms: " << mol3.nAtoms() << std::endl;
		std::cout << "Number of Bonds: " << mol3.nBonds() << std::endl;
		if (mol3.nAtoms() > 0) {
			std::cout << mol3.getAtom(5)->getSymbol() << std::endl;
		}
	}
	//{
	//	UFF uff(mol3);
	//	uff.setupTerms();
	//	uff.calculateEnergy(false);
	//	std::cout << "Total Energy: " << uff.energy() << std::endl;
	//	std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
	//	std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
	//}

	std::cout << "\nWriting XYZ File:" << std::endl;
	if (fileControl.write("ala_phe_ala", mol3, "xyz")) {
		std::cout << "File written succesfully" << std::endl;
	}
	else {
		std::cout << "Error when writting file" << std::endl;
	}


	std::cout << "\nReading a mol2 file " << std::endl; 
	Molecule m2mol; 
	if (fileControl.read("tests/CTN.mol2", m2mol)) {
		std::cout << "File read successfully" << std::endl;
		std::cout << "nAtoms: " << m2mol.nAtoms() << std::endl;
	}
	else {
		std::cout << "Error reading m2 mol file" << std::endl;
	}

	testMaths();
}



void testMaths() {

	using namespace ctkMaths;
	double errThr = 1e-4; // -> Increase this (requries getting better precision for the check values)

	std::cout << "\nMaths Library Tests" << std::endl;
	std::cout << "-------------------" << std::endl;

	Vector3 v1(1, 2, 3);
	Vector3 v2(2, 3, 4);
	Vector3 v3(v2);

	assert(v1[0] == 1.0);
	assert(v1[1] == 2.0);
	assert(v1[2] == 3.0);

	assert(dot(v1, v2) == 20);
	assert(abs(v1.normal() - 3.74166) < errThr);

	v1 *= 4;
	assert(v1[0] == 4);
	v1.normalise(); 
	assert(abs(v1[0] - 0.267261) < errThr);
	assert(abs(v1[1] - 0.534522) < errThr);
	assert(abs(v1[2] - 0.801784) < errThr);

	v3 += v2; 
	Vector3 v4 = v3 - v2; 
	assert(v4[0] == v2[0]);
	assert(v4[1] == v2[1]);
	assert(v4[2] == v2[2]);

	Vector3 sv1 = 5.0 * v2;
	std::cout << "v2  = " << v2 << std::endl;
	std::cout << "sv1 = " << sv1 << std::endl;


	Matrix33 eye = identity33();
	assert(eye[0] == 1.0);
	assert(eye[1] == 0.0);
	assert(eye[4] == 1.0);
	assert(eye.value(2, 2));

	Vector3 iv3 = eye * v2;
	assert(iv3[0] == 2.0);
	assert(iv3[1] == 3.0);
	assert(iv3[2] == 4.0);

	Matrix33 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);
	assert(m1[0] == 1.0);
	assert(m1.value(2, 2) == 9.0);

	Matrix33 im1 = eye * m1;

	assert(im1[0] == 1.0);
	assert(im1[3] == 4.0);
	assert(im1.value(1, 2) == 6.0);
	assert(im1.value(2, 2) == 9.0);

	m1 *= 2;
	assert(m1[0] == 2.0);
	assert(m1.value(2, 2) == 18.0);

	std::cout << im1 << std::endl;

	std::cout << "Tests completed succesfully!" << std::endl;
}

