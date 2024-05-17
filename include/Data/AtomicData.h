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
#ifdef WITH_CTK_GRAPHICS
			colour{ colR, colB, colG }
#endif
		{}
		~Element() = default;

		int atomicNumber;
		const char* symbol;
		float covalentRadii;
#ifdef WITH_CTK_GRAPHICS
		float colour[3];
#endif

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
			if (i >= PeriodicTable::_nElements) {
				return _atoms[0];
			}
			else {
				return _atoms[i];
			}
		}
	
	private:
		PeriodicTable(const PeriodicTable&) = delete;
		PeriodicTable& operator=(const PeriodicTable&) = delete;

		static constexpr int _nElements = 112;
		Element _atoms[_nElements] = {
			Element(  0, "  ", 0.00, 0.00, 0.00, 0.00),
			Element(  1, "H ", 0.32, 1.00, 1.00, 1.00),
			Element(  2, "He", 0.32, 0.85, 1.00, 1.00),
			Element(  3, "Li", 1.33, 0.50, 0.00, 1.00),
			Element(  4, "Be", 1.04, 0.76, 1.00, 0.00),
			Element(  5, "B ", 0.85, 1.00, 0.71, 0.71),
			Element(  6, "C ", 0.75, 0.50, 0.50, 0.50),
			Element(  7, "N ", 0.71, 0.00, 0.00, 1.00),
			Element(  8, "O ", 0.63, 1.00, 0.00, 0.00),
			Element(  9, "F ", 0.64, 0.00, 0.70, 1.00),
			Element( 10, "Ne", 0.67, 0.70, 0.90, 0.96),
			Element( 11, "Na", 1.55, 0.67, 0.36, 0.95), 
			Element( 12, "Mg", 1.39, 0.50, 1.00, 0.00),
			Element( 13, "Al", 1.26, 0.75, 0.65, 0.65), 
			Element( 14, "Si", 1.16, 0.54, 0.60, 0.78), 
			Element( 15, "P ", 1.11, 1.00, 0.50, 0.00), 
			Element( 16, "S ", 1.03, 1.00, 1.00, 0.19), 
			Element( 17, "Cl", 0.80, 0.24, 1.00, 0.00), 
			Element( 18, "Ar", 0.96, 0.50, 0.82, 0.89), 
			Element( 19, "K ", 1.96, 0.56, 0.25, 0.83),
			Element( 20, "Ca", 1.71, 0.24, 1.00, 0.00), 
			Element( 21, "Sc", 1.48, 0.90, 0.90, 0.90), 
			Element( 22, "Ti", 1.36, 0.75, 0.76, 0.78), 
			Element( 23, "V ", 1.34, 0.65, 0.65, 0.67), 
			Element( 24, "Cr", 1.22, 0.54, 0.60, 0.78), 
			Element( 25, "Mn", 1.19, 0.61, 0.48, 0.78), 
			Element( 26, "Fe", 1.16, 0.88, 0.40, 0.20), 
			Element( 27, "Co", 1.11, 0.94, 0.56, 0.63), 
			Element( 28, "Ni", 1.10, 0.31, 0.82, 0.31), 
			Element( 29, "Cu", 1.12, 0.78, 0.50, 0.20), 
			Element( 30, "Zn", 1.18, 0.49, 0.50, 0.69), 
			Element( 31, "Ga", 1.24, 0.76, 0.56, 0.56),
			Element( 32, "Ge", 1.21, 0.40, 0.56, 0.56),
			Element( 33, "As", 1.21, 0.74, 0.50, 0.89),
			Element( 34, "Se", 1.16, 1.00, 0.63, 0.00),
			Element( 35, "Br", 1.14, 0.65, 0.16, 0.16), 
			Element( 36, "Kr", 1.17, 0.36, 0.72, 0.82), 
			Element( 37, "Rb", 2.10, 0.44, 0.18, 0.69),
			Element( 38, "Sr", 1.85, 0.00, 1.00, 0.00), 
			Element( 39, "Y ", 1.63, 0.58, 1.00, 1.00),
			Element( 40, "Zr", 1.54, 0.58, 0.88, 0.88),
			Element( 41, "Nb", 1.47, 0.45, 0.76, 0.79),
			Element( 42, "Mo", 1.38, 0.33, 0.71, 0.71),
			Element( 43, "Tc", 1.27, 0.23, 0.62, 0.62),
			Element( 44, "Ru", 1.25, 0.14, 0.56, 0.56),
			Element( 45, "Rh", 1.25, 0.04, 0.49, 0.55),
			Element( 46, "Pd", 1.20, 0.00, 0.41, 0.52), 
			Element( 47, "Ag", 1.28, 0.75, 0.75, 0.75),
			Element( 48, "Cd", 1.36, 1.00, 0.85, 0.56),
			Element( 49, "In", 1.40, 0.65, 0.46, 0.45),
			Element( 50, "Sn", 1.42, 0.40, 0.50, 0.50),
			Element( 51, "Sb", 1.40, 0.62, 0.39, 0.71),
			Element( 52, "Te", 1.36, 0.83, 0.48, 0.00), 
			Element( 53, "I ", 1.33, 0.58, 0.00, 0.58),
			Element( 54, "Xe", 1.31, 0.26, 0.62, 0.69),
			Element( 55, "Cs", 2.32, 0.34, 0.09, 0.56),
			Element( 56, "Ba", 1.96, 0.00, 0.79, 0.00),
			Element( 57, "La", 1.80, 0.44, 0.83, 1.00),
			Element( 58, "Ce", 1.63, 1.00, 1.00, 0.78),
			Element( 59, "Pr", 1.76, 0.85, 1.00, 0.78),
			Element( 60, "Nd", 1.74, 0.78, 1.00, 0.78),
			Element( 61, "Pm", 1.73, 0.64, 1.00, 0.78),
			Element( 62, "Sm", 1.72, 0.56, 1.00, 0.78), 
			Element( 63, "Eu", 1.68, 0.38, 1.00, 0.78),
			Element( 64, "Gd", 1.69, 0.27, 1.00, 0.78), 
			Element( 65, "Tb", 1.68, 0.19, 1.00, 0.78), 
			Element( 66, "Dy", 1.67, 0.12, 1.00, 0.78), 
			Element( 67, "Ho", 1.66, 0.00, 1.00, 0.61), 
			Element( 68, "Er", 1.65, 0.00, 0.90, 0.46), 
			Element( 69, "Tm", 1.64, 0.00, 0.83, 0.32), 
			Element( 70, "Yb", 1.70, 0.00, 0.75, 0.22), 
			Element( 71, "Lu", 1.62, 0.00, 0.67, 0.14), 
			Element( 72, "Hf", 1.52, 0.30, 0.76, 1.00), 
			Element( 73, "Ta", 1.46, 0.30, 0.65, 1.00), 
			Element( 74, "W ", 1.37, 0.13, 0.58, 0.84),
			Element( 75, "Re", 1.31, 0.15, 0.49, 0.67), 
			Element( 76, "Os", 1.29, 0.15, 0.40, 0.59), 
			Element( 77, "Ir", 1.22, 0.09, 0.33, 0.53), 
			Element( 78, "Pt", 1.23, 0.82, 0.82, 0.88), 
			Element( 79, "Au", 1.24, 1.00, 0.82, 0.14), 
			Element( 80, "Hg", 1.33, 0.72, 0.72, 0.82), 
			Element( 81, "Tl", 1.44, 0.65, 0.33, 0.30), 
			Element( 82, "Pb", 1.44, 0.34, 0.35, 0.38), 
			Element( 83, "Bi", 1.51, 0.62, 0.31, 0.71), 
			Element( 84, "Po", 1.45, 0.67, 0.36, 0.00), 
			Element( 85, "At", 1.47, 0.46, 0.31, 0.27), 
			Element( 86, "Rn", 1.42, 0.26, 0.51, 0.59), 
			Element( 87, "Fr", 2.23, 0.26, 0.00, 0.40), 
			Element( 88, "Ra", 2.01, 0.00, 0.49, 0.00), 
			Element( 89, "Ac", 1.86, 0.44, 0.67, 0.98), 
			Element( 90, "Th", 1.75, 0.00, 0.73, 1.00),
			Element( 91, "Pa", 1.69, 0.00, 0.63, 1.00), 
			Element( 92, "U ", 1.70, 0.00, 0.56, 1.00), 
			Element( 93, "Np", 1.71, 0.00, 0.50, 1.00), 
			Element( 94, "Pu", 1.72, 0.00, 0.42, 1.00), 
			Element( 95, "Am", 1.66, 0.33, 0.36, 0.95), 
			Element( 96, "Cm", 1.66, 0.47, 0.36, 0.89), 
			Element( 97, "Bk", 1.68, 0.54, 0.31, 0.89), 
			Element( 98, "Cf", 1.68, 0.63, 0.21, 0.83), 
			Element( 99, "Es", 1.65, 0.70, 0.12, 0.83), 
			Element(100, "Fm", 1.67, 0.70, 0.12, 0.73), 
			Element(101, "Md", 1.73, 0.70, 0.05, 0.65), 
			Element(102, "No", 1.76, 0.74, 0.05, 0.53), 
			Element(103, "Lr", 1.61, 0.78, 0.00, 0.40), 
			Element(104, "Rf", 1.57, 0.80, 0.00, 0.35), 
			Element(105, "Db", 1.49, 0.82, 0.00, 0.31), 
			Element(106, "Sg", 1.43, 0.85, 0.00, 0.27), 
			Element(107, "Bh", 1.41, 0.88, 0.00, 0.22), 
			Element(108, "Hs", 1.34, 0.90, 0.00, 0.18), 
			Element(109, "Mt", 1.29, 0.92, 0.00, 0.15), 
			Element(110, "Ds", 1.28, 0.92, 0.00, 0.10), 
			Element(111, "Rg", 1.21, 0.92, 0.00, 0.05), 
			//Element(112, "Cn", 1.60)
			//Element(113, "Nh", 1.50)
			//Element(114, "Fl", 1.50)
			//Element(115, "Mc", 1.50)
			//Element(116, "Lv", 1.50)
			//Element(117, "Ts", 1.50)
			//Element(118, "Og", 1.50)
		};
	};
}