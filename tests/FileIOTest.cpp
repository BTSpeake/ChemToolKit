#include <gtest/gtest.h>
#include "Data/Model.h"
#include "FileIO/FileControl.h"

TEST(FileIOTest, Read_XYZ) {

	ctkIO::FileControl fc; 
	ctkData::Model model;

	EXPECT_TRUE(fc.read("test_files/Water_Trimer.xyz", model));

	EXPECT_EQ(model.nAtoms(), 9);
	EXPECT_EQ(model.nBonds(), 6);

	EXPECT_EQ(model.getAtom(0)->getAtomicNumber(), 8);
	EXPECT_EQ(model.getAtom(1)->getAtomicNumber(), 1);
}

TEST(FileIOTest, Read_PDB) {

	ctkIO::FileControl fc;
	ctkData::Model model;

	EXPECT_TRUE(fc.read("test_files/ala_phe_ala.pdb", model));

	EXPECT_EQ(model.nAtoms(), 103);
	EXPECT_EQ(model.nBonds(), 103);

}

TEST(FileIOTest, Read_MOL2) {
	ctkIO::FileControl fc;
	ctkData::Model model;
	EXPECT_TRUE(fc.read("test_files/CTN.mol2", model));
	EXPECT_EQ(model.nAtoms(), 53);
	EXPECT_EQ(model.nBonds(), 54);
	EXPECT_EQ(model.getAtom(0)->getAtomicNumber(), 6);
	EXPECT_EQ(model.getAtom(1)->getAtomicNumber(), 1);
}

TEST(FileIOTest, Write_XYZ) {
	ctkIO::FileControl fileControl;
	ctkData::Model mol;
	mol.addAtom("H", 0.0, 0.0, 0.0);
	mol.addAtom("H", 0.0, 0.0, 1.0);

	EXPECT_TRUE(fileControl.write("test_files/H2", mol, "xyz"));

	ctkData::Model mol2;
	EXPECT_TRUE(fileControl.read("test_files/H2.xyz", mol2));
	EXPECT_EQ(mol2.nAtoms(), 2);
	EXPECT_EQ(mol2.getAtom(0)->getAtomicNumber(), 1);
	EXPECT_EQ(mol2.getAtom(1)->getAtomicNumber(), 1);
	std::remove("test_files/H2.xyz");
}

TEST(FileIOTest, Write_MOL2) {
	ctkIO::FileControl fc;
	ctkData::Model mol;
	EXPECT_TRUE(fc.read("test_files/Water_Trimer.xyz", mol));
	EXPECT_TRUE(fc.write("test_files/Water_Trimer.mol2", mol, "ml2"));
	ctkData::Model mol2;
	EXPECT_TRUE(fc.read("test_files/Water_Trimer.mol2", mol2, "ml2"));
	EXPECT_EQ(mol2.nAtoms(), 9);
	EXPECT_EQ(mol2.nBonds(), 6);
	EXPECT_EQ(mol2.getAtom(0)->getAtomicNumber(), 8);
	EXPECT_EQ(mol2.getAtom(1)->getAtomicNumber(), 1);
	std::remove("test_files/Water_Trimer.mol2");
}