#include <gtest/gtest.h>
#include "Data/Model.h"
#include "FileIO/FileControl.h"
#include "ForceField/UFF.h"

#define ERROR_THRESHOLD 1e-8

TEST(UFFTest, Water_Trimer) {
	ctkIO::FileControl fc; 
	ctkData::Model model;
	EXPECT_TRUE(fc.read("test_files/Water_Trimer.xyz", model));
	UFF uff(model);
	uff.setupTerms();
	uff.calculateEnergy(false);

	const double totalEnergy	= 30.04892287177733;
	const double bondEnergy		= 6.5221261546325815;
	const double angleEnergy	= 0.22312561395540859;
	const double vdwEnergy = 23.303671103189338;
	

	EXPECT_LT(std::abs(uff.energy() - totalEnergy), ERROR_THRESHOLD);
	EXPECT_LT(std::abs(uff.getBondEnergy() - bondEnergy), ERROR_THRESHOLD);
	EXPECT_LT(std::abs(uff.getAngleEnergy() - angleEnergy), ERROR_THRESHOLD);
	EXPECT_LT(std::abs(uff.getVDWEnergy() - vdwEnergy), ERROR_THRESHOLD);

}