#include "UFF.h"

#include <fstream>
#include <iostream>
#include <regex>



UFF::UFF(Molecule& mol) : ForceField(mol) {
	setParameters();
}

void UFF::setParameters() {

	std::ifstream prmFile("C:\\Users\\sil23665\\Documents\\Projects\\FFOptimiser\\data\\UFF.prm");
	if (!prmFile.is_open()) {
		std::cout << "Unable to read param file" << std::endl;
		return;
	}
	std::string line;
	std::vector<std::string> vals;
	vals.reserve(12);
	const std::regex re("\t");
	while (std::getline(prmFile, line)) {
		double params[11];
		vals.clear();
		std::copy(
			std::sregex_token_iterator(
				line.begin(), line.end(), re, -1
			),
			std::sregex_token_iterator(),
			std::back_inserter(vals)
		);

		for (int i = 1; i < 12; i++) {
			params[i - 1] = stod(vals[i]);
		}
		_params.insert(std::pair<std::string, UFFParameters*>(vals[0], new UFFParameters(vals[0], params)));
	}
	prmFile.close();
}