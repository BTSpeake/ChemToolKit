#pragma once 
#include <string>

namespace AtomData {

	class Element {
	public:
		Element(
			int a,
			std::string sym,
			double covR
		) :
			atomicNumber(a),
			symbol(sym),
			covalentRadii(covR)
		{}

		int atomicNumber; 
		std::string symbol;
		double covalentRadii;

		Element(const Element&) = delete;
		Element& operator=(const Element&) = delete;
		~Element() = default;
		Element() = delete;
	};

	namespace Elements {
		extern const Element HYDROGEN;
		extern const Element HELIUM;
		extern const Element LITHIUM;
		extern const Element BERYLLIUM;
		extern const Element BORON;
		extern const Element CARBON;
		extern const Element NITROGEN;
		extern const Element OXYGEN;
		extern const Element FLUORINE;
		extern const Element NEON;
		extern const Element SODIUM;
		extern const Element MAGNESIUM;
		extern const Element ALUMINIUM;
		extern const Element SILICON;
		extern const Element PHOSPHORUS;
		extern const Element SULFUR;
		extern const Element CHLORINE;
		extern const Element ARGON;
		extern const Element POTASSIUM;
		extern const Element CALCIUM;
		extern const Element SCANDIUM;
		extern const Element TITATNIUM;
		extern const Element VANADIUM;
		extern const Element CHROMIUM;
		extern const Element MANGANESE;
		extern const Element IRON;
		extern const Element COBALT;
		extern const Element NICKEL;
		extern const Element COPPER;
		extern const Element ZINC;
		extern const Element GALLIUM;
		extern const Element GERMANIUM;
		extern const Element ARSENIC;
		extern const Element SELENIUM;
		extern const Element BROMINE;
		extern const Element KRYPTON;
		extern const Element RUBIDIUM;
		extern const Element STRONTIUM;
		extern const Element YTTRIUM;
		extern const Element ZIRCONIUM;
		extern const Element NIOBIUM;
		extern const Element MOLYBDENUM;
		extern const Element TECHNETIUM;
		extern const Element RUTHENIUM;
		extern const Element RHODIUM;
		extern const Element PALLADIUM;
		extern const Element SILVER;
		extern const Element CADMIUM;
		extern const Element INDIUM;
		extern const Element TIN;
		extern const Element ANTIMONY;
		extern const Element TELLURIUM;
		extern const Element IODINE;
		extern const Element XENON;
		extern const Element CAESIUM;
		extern const Element BARIUM;
		extern const Element LANTHANUM;
		extern const Element CERIUM;
		extern const Element PRASEODYMIUM;
		extern const Element NEODYMIUM;
		extern const Element PROMETHIUMM;
		extern const Element SAMARIUM;
		extern const Element EUROPIUM;
		extern const Element GADOLINIUM;
		extern const Element TERBIUM;
		extern const Element DYSPROSIUM;
		extern const Element HOLMIUM;
		extern const Element ERBIUM;
		extern const Element THULIUM;
		extern const Element YTTERBIUM;
		extern const Element LUTETIUM;
		extern const Element HAFNIUM;
		extern const Element TANTALUM;
		extern const Element TUNGSTEN;
		extern const Element RHENIUM;
		extern const Element OSMIUM;
		extern const Element IRIDIUM;
		extern const Element PLATINUM;
		extern const Element GOLD;
		extern const Element MERCURY;
		extern const Element THALLIUM;
		extern const Element LEAD;
		extern const Element BISMUTH;
		extern const Element POLONIUM;
		extern const Element ASTATINE;
		extern const Element RADON;
		extern const Element FRANCIUM;
		extern const Element RADIUM;
		extern const Element ACTINIUM;
		extern const Element THORIUM;
		extern const Element PROTACTINIUM;
		extern const Element URANIUM;
		extern const Element NEPTUNIUM;
		extern const Element PLUTONIUM;
		extern const Element AMERICIUM;
		extern const Element CURIUM;
		extern const Element BERKELIUM;
		extern const Element CALIFONIUM;
		extern const Element EINSTEINIUM;
		extern const Element FERMIUM;
		extern const Element MENDELEVIUM;
		extern const Element NOBELIUM;
		extern const Element LAWRENCIUM;
		extern const Element RUTHERFORDIUM;
		extern const Element DUBNIUM;
		extern const Element SEABORGIUM;
		extern const Element BOHRIUM;
		extern const Element HASSIUM;
		extern const Element MEITNERIUM;
		extern const Element DARMSTADTIUM;
		extern const Element ROENTGENIUM;
		// find data on the following atoms -> this data is assumed not taken from reliable sources ;covalent Radii)
		extern const Element COPERNICIUM;
		extern const Element NIHONIUM;
		extern const Element FLEROVIUM;
		extern const Element MOSCOVIUM;
		extern const Element LIVERMORIUM;
		extern const Element TENNESSINE;
		extern const Element OGANESSON;
	}
	

}