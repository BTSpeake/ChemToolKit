#include <iostream>
#include <cassert>

#include "Molecule/Molecule.h"
#include "ForceField/UFF.h"
#include "FileIO/FileControl.h"

#include "Maths/Vector3.h"
#include "Maths/Matrix33.h"

void testMaths();
void printVector3(const ctkMaths::Vector3& v);
void printMatrix33(const ctkMaths::Matrix33& m);


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

	assert(v1[0] == 1.0, "Error in creating v1 -> v1[0] value doesn't match ");
	assert(v1[1] == 2.0, "Error in creating v1 -> v1[1] value doesn't match ");
	assert(v1[2] == 3.0, "Error in creating v1 -> v1[2] value doesn't match ");

	assert(dot(v1, v2) == 20, "Error in the dot product of two vectors");
	assert(abs(v1.normal() - 3.74166) < errThr, "Error in the calculation of v1's normal");

	v1 *= 4;
	assert(v1[0] == 4, "Error in the scalar multiplication of v1");
	v1.normalise(); 
	assert(abs(v1[0] - 0.267261) < errThr, "Error in the normalisation of v1");
	assert(abs(v1[1] - 0.534522) < errThr, "Error in the normalisation of v1");
	assert(abs(v1[2] - 0.801784) < errThr, "Error in the normalisation of v1");

	v3 += v2; 
	Vector3 v4 = v3 - v2; 
	assert(v4[0] == v2[0], "Error with vector addition/subtration");
	assert(v4[1] == v2[1], "Error with vector addition/subtration");
	assert(v4[2] == v2[2], "Error with vector addition/subtration");

	Matrix33 eye = identity33();
	assert(eye[0] == 1.0, "Error in creating identity matrix (3x3)");
	assert(eye[1] == 0.0, "Error in creating identity matrix (3x3)");
	assert(eye[4] == 1.0, "Error in creating identity matrix (3x3)");
	assert(eye.value(2, 2), "Error in creating identity matrix (3x3)");

	Vector3 iv3 = eye * v2;
	assert(iv3[0] == 2.0, "Error in matrix * vector function");
	assert(iv3[1] == 3.0, "Error in matrix * vector function");
	assert(iv3[2] == 4.0, "Error in matrix * vector function");

	Matrix33 m1(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9
	);
	assert(m1[0] == 1.0, "Error in Matrix m1 creation/access");
	assert(m1.value(2, 2) == 9.0, "Error in Matrix m1 creation/access");

	Matrix33 im1 = eye * m1;

	assert(im1[0] == 1.0, "Error in matrix * matrix function");
	assert(im1[3] == 4.0, "Error in matrix * matrix function");
	assert(im1.value(1, 2) == 6.0, "Error in matrix * matrix function");
	assert(im1.value(2, 2) == 9.0, "Error in matrix * matrix function");

	m1 *= 2;
	assert(m1[0] == 2.0, "Error in matrix *= scaler");
	assert(m1.value(2, 2) == 18.0, "Error in matrix *= scalar");

	std::cout << "Tests completed succesfully!" << std::endl;
}



void printVector3(const ctkMaths::Vector3& v) {
	std::cout << '['; 
	std::cout << v[0] << ", " << v[1] << ", " << v[2];
	std::cout << ']';
	std::cout << std::endl;
}
void printMatrix33(const ctkMaths::Matrix33& m) {
	std::cout << "[";
	std::cout << " [" << m[0] << ", " << m[1] << ", " << m[2] << "]\n";
	std::cout << " [" << m[3] << ", " << m[4] << ", " << m[5] << "]\n";
	std::cout << " [" << m[6] << ", " << m[7] << ", " << m[8] << "]";
	std::cout << "]" << std::endl;
}