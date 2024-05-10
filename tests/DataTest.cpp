#include <gtest/gtest.h>
#include "Data/Model.h"


TEST(DataTest, Model_H2) {

	using namespace ctkData;

	Model mol;
	// Hydrogen Molecule 
	mol.addAtom(1, 0.0, 0.0, 0.7);
	mol.addAtom(1, 0.0, 0.0, 0.0);
	mol.addBond(0, 1);

	EXPECT_EQ(mol.nAtoms(), 2);
	EXPECT_EQ(mol.nBonds(), 1);


}