#include <iostream>
#include <cassert>
#include <string>

#include "Data/Molecule.h"
#include "ForceField/UFF.h"
#include "FileIO/FileControl.h"

#include "Maths/Vector3.h"
#include "Maths/Matrix33.h"

using ctkData::Molecule;

double THR = 1e-8;

void runTest(bool (*func)(void), const std::string& descr);
bool test_Maths();
bool test_H2();
bool test_XYZ();
bool test_PDB();
bool test_MOL2();
bool test_XYZ_write();
bool test_MOL2_write();

int main() {

	runTest(&test_Maths, "Maths test.");
	runTest(&test_H2, "H2 test.");
	runTest(&test_XYZ, "xyz parser test.");
	runTest(&test_PDB, "pdb parser test.");
	runTest(&test_XYZ_write, "xyz write test.");
	runTest(&test_MOL2, "mol2 parser test.");
	runTest(&test_MOL2_write, "mol2 write test.");

}

void runTest(bool (*func)(void), const std::string& descr) {
	if (!func()) {
		std::cout << "FAILED :: " << descr << std::endl;
	}
	else {
		std::cout << "SUCCESS :: " << descr << std::endl;
	}
}

bool test_H2() {
	bool chk = true;
	// manually create molecule
	Molecule mol;
	// Hydrogen Molecule 
	mol.addAtom(1, 0.0, 0.0, 0.7);
	mol.addAtom(1, 0.0, 0.0, 0.0);
	mol.addBond(0, 1);

	if (mol.nAtoms() != 2) {
		std::cout << "ERROR :: Incorrect number of atoms." << std::endl;
		chk = false;
	}
	if (mol.nBonds() != 1) {
		std::cout << "ERROR :: Incorrect number of bonds." << std::endl;
		chk = false;
	}

	UFF uff(mol);
	uff.setupTerms();
	uff.calculateEnergy(false);
	if (std::abs(uff.energy() - 0.030356853290024122) > THR) {
		std::cout << "ERROR :: Incorrect total energy for H2" << std::endl;
		chk = false;
	}
	if (std::abs(uff.getBondEnergy() - 0.030356853290024122) > THR) {
		std::cout << "ERROR :: Incorrect bond energy for H2" << std::endl;
		chk = false;
	}

	return chk;
}

bool test_XYZ() {
	bool chk = true;
	// Use file parsing 
	ctkIO::FileControl fileControl;
	Molecule mol;
	if (fileControl.read("tests/Water_Trimer.xyz", mol)) {
		//fio.read(mol2);
		if (mol.nAtoms() != 9) {
			std::cout << "ERROR :: Incorrect number of atoms determined. :: " << mol.nAtoms() << std::endl;
			chk = false;
		}
		if (mol.nBonds() != 6) {
			std::cout << "ERROR :: Incorrect number of bonds determined. :: " << mol.nBonds() << std::endl;
			chk = false;
		}
	}
	else {
		std::cout << "ERROR :: File doesn't exist" << std::endl;
		chk = false;
	}
	
	UFF uff(mol);
	uff.setupTerms();
	uff.calculateEnergy(false);
	if (std::abs(uff.energy() - 30.04892287177733) > THR) {
		std::cout << "ERROR :: Incorrect total energy for Water Trimer" << std::endl;
		chk = false;
	}
	if (std::abs(uff.getBondEnergy() - 6.5221261546325815) > THR) {
		std::cout << "ERROR :: Incorrect bond energy for Water Trimer" << std::endl;
		chk = false;
	}
	if (std::abs(uff.getAngleEnergy() - 0.22312561395540859) > THR) {
		std::cout << "ERROR :: Incorrect angle energy for Water Trimer" << std::endl;
		chk = false;
	}
	if (std::abs(uff.getVDWEnergy() - 23.303671103189338) > THR) {
		std::cout << "ERROR :: Incorrect VdW energy for Water Trimer" << std::endl;
		chk = false;
	}

	return chk;
}

bool test_PDB() {
	bool chk = true;

	ctkIO::FileControl fileControl;
	Molecule mol;
	if (!fileControl.read("tests/ala_phe_ala.pdb", mol)) {
		std::cout << "ERROR :: Can't read ala_phe_ala.pdb file." << std::endl;
		chk = false;
	}
	if (mol.nAtoms() != 103) {
		std::cout << "ERROR :: Incorrect number of atoms." << std::endl;
		chk = false;
	}
	if (mol.nBonds() != 103) {
		std::cout << "ERROR :: Incorrect number of bonds." << std::endl;
		chk = false;
	}

	//{
	//	UFF uff(mol3);
	//	uff.setupTerms();
	//	uff.calculateEnergy(false);
	//	std::cout << "Total Energy: " << uff.energy() << std::endl;
	//	std::cout << "Bond Energy:  " << uff.getBondEnergy() << std::endl;
	//	std::cout << "Angle Energy: " << uff.getAngleEnergy() << std::endl;
	//}

	return chk;
}

bool test_XYZ_write() {

	bool chk = true;

	ctkIO::FileControl fileControl;
	Molecule mol; 
	mol.addAtom("H", 0.0, 0.0, 0.0);
	mol.addAtom("H", 0.0, 0.0, 1.0);

	if (!fileControl.write("tests/H2", mol, "xyz")) {
		std::cout << "Error :: when writting file." << std::endl;
		chk = false;
	}

	Molecule mol2; 
	if (!fileControl.read("tests/H2.xyz", mol2)) {
		std::cout << "ERROR :: Can't read H2.xyz file." << std::endl;
		chk = false;
	}
	if (mol2.nAtoms() != 2) {
		std::cout << "ERROR :: Incorrect number of atoms" << std::endl;
		chk = false;
	}

	if (chk) {
		std::remove("tests/H2.xyz");
	}

	return chk;
}

bool test_MOL2() {
	bool chk = true;

	ctkIO::FileControl fileControl;
	Molecule mol;
	if (!fileControl.read("tests/CTN.mol2", mol)) {
		std::cout << "ERROR :: reading m2 mol file" << std::endl;
		chk = false;
	}
	if (mol.nAtoms() != 53) {
		std::cout << "ERROR :: Incorrect number of atoms." << std::endl;
		chk = false;
	}
	if (mol.nBonds() != 54) {
		std::cout << "ERROR :: Incorrect number of bonds." << std::endl;
		chk = false;
	}

	return chk;
}

bool test_MOL2_write() {
	bool chk = true;

	ctkIO::FileControl fc;
	Molecule mol;
	fc.read("tests/Water_Trimer.xyz", mol);
	if (!fc.write("tests/Water_Trimer.mol2", mol, "ml2")) {
		std::cout << "ERROR :: writing mol2 file." << std::endl;
		chk = false;
	}
	Molecule mol2;
	if (!fc.read("tests/Water_Trimer.mol2", mol2, "ml2")) {
		std::cout << "ERROR :: reading writen mol2 file." << std::endl;
		chk = false;
	}
	if (mol2.nAtoms() != 9) {
		std::cout << "ERROR :: Incorrect number of atoms. :: " << mol2.nAtoms() << std::endl;
		chk = false;
	}
	if (mol2.nBonds() != 6) {
		std::cout << "ERROR :: Incorrect number of bonds. :: " << mol2.nBonds() << std::endl;
		chk = false;
	}

	if (chk) {
		std::remove("tests/Water_Trimer.mol2");
	}

	return chk;
}

bool test_Maths() {
	bool chk = true;

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

	std::cout << std::endl;

	return chk;
}

