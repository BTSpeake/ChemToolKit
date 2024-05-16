#pragma once 
#include <string>
#include <map>

namespace ctkData::AtomData {

	class Element {
	public:
		Element(
			int a,
			const char* sym,
			float covR,
			float colR, 
			float colG, 
			float colB
		) :
			atomicNumber(a),
			symbol(sym),
			covalentRadii(covR), 
			colour{ colR, colB, colG }
		{}
		~Element() = default;

		int atomicNumber;
		const char* symbol;
		float covalentRadii;
		float colour[3];

	private:
		Element(const Element&) = delete;
		Element& operator=(const Element&) = delete;
		Element() = delete;
	};

	class PeriodicTable {
	public: 
		PeriodicTable() = default;
		~PeriodicTable() = default;
		const Element& operator[](const unsigned int i) { 
			if (i >= 31) {
				return _atoms[0];
			}
			else {
				return _atoms[i];
			}
		}
	
	private:
		PeriodicTable(const PeriodicTable&) = delete;
		PeriodicTable& operator=(const PeriodicTable&) = delete;

		Element _atoms[31] = {
			Element( 0, "  ", 0.00, 0.00, 0.00, 0.00),
			Element( 1, "H ", 0.32, 1.00, 1.00, 1.00),
			Element( 2, "He", 0.32, 0.85, 1.00, 1.00),
			Element( 3, "Li", 1.33, 0.50, 0.00, 1.00),
			Element( 4, "Be", 1.04, 0.76, 1.00, 0.00),
			Element( 5, "B ", 0.85, 1.00, 0.71, 0.71),
			Element( 6, "C ", 0.75, 0.50, 0.50, 0.50),
			Element( 7, "N ", 0.71, 0.00, 0.00, 1.00),
			Element( 8, "O ", 0.63, 1.00, 0.00, 0.00),
			Element( 9, "F ", 0.64, 0.00, 0.70, 1.00),
			Element(10, "Ne", 0.67, 0.70, 0.90, 0.96),
			Element(11, "Na", 1.55, 0.67, 0.36, 0.95), 
			Element(12, "Mg", 1.39, 0.50, 1.00, 0.00),
			Element(13, "Al", 1.26, 0.75, 0.65, 0.65), 
			Element(14, "Si", 1.16, 0.54, 0.60, 0.78), 
			Element(15, "P ", 1.11, 1.00, 0.50, 0.00), 
			Element(16, "S ", 1.03, 1.00, 1.00, 0.19), 
			Element(17, "Cl", 0.80, 0.24, 1.00, 0.00), 
			Element(18, "Ar", 0.96, 0.50, 0.82, 0.89), 
			Element(19, "K ", 1.96, 0.56, 0.25, 0.83),
			Element(20, "Ca", 1.71, 0.24, 1.00, 0.00), 
			Element(21, "Sc", 1.48, 0.90, 0.90, 0.90), 
			Element(22, "Ti", 1.36, 0.75, 0.76, 0.78), 
			Element(23, "V ", 1.34, 0.65, 0.65, 0.67), 
			Element(24, "Cr", 1.22, 0.54, 0.60, 0.78), 
			Element(25, "Mn", 1.19, 0.61, 0.48, 0.78), 
			Element(26, "Fe", 1.16, 0.88, 0.40, 0.20), 
			Element(27, "Co", 1.11, 0.94, 0.56, 0.63), 
			Element(28, "Ni", 1.10, 0.31, 0.82, 0.31), 
			Element(29, "Cu", 1.12, 0.78, 0.50, 0.20), 
			Element(30, "Zn", 1.18, 0.49, 0.50, 0.69), 
		};
	};
}