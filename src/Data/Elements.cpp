#include "Data/AtomicData.h"

using namespace AtomData;
using namespace AtomData::Elements;

static const Element HYDROGEN(
	1, "H ", 0.32
);

static const Element HELIUM(
	2, "He", 0.46
);

static const Element LITHIUM(
	3, "Li", 1.33
);

static const Element BERYLLIUM(
	4, "Be", 1.04
);

static const Element BORON(
	5, "B ", 0.85
);

static const Element CARBON(
	6, "C ", 0.75
);

static const Element NITROGEN(
	7, "N ", 0.71
);

static const Element OXYGEN(
	8, "O ", 0.63
);

static const Element FLUORINE(
	9, "F ", 0.64
);

static const Element NEON(
	10, "Ne", 0.67
);

static const Element SODIUM(
	11, "Na", 1.55
);

static const Element MAGNESIUM(
	12, "Mg", 1.39
);

static const Element ALUMINIUM(
	13, "Al", 1.26
);

static const Element SILICON(
	14, "Si", 1.16
);

static const Element PHOSPHORUS(
	15, "P ", 1.11
);

static const Element SULFUR(
	16, "S ", 1.03
);

static const Element CHLORINE(
	17, "Cl", 0.80
);

static const Element ARGON(
	18, "Ar", 0.96
);

static const Element POTASSIUM(
	19, "K ", 1.96
);

static const Element CALCIUM(
	20, "Ca", 1.71
);

static const Element SCANDIUM(
	21, "Sc", 1.48
);

static const Element TITATNIUM(
	22, "Ti", 1.36
);

static const Element VANADIUM(
	23, "V ", 1.34
);

static const Element CHROMIUM(
	24, "Cr", 1.22
);

static const Element MANGANESE(
	25, "Mn", 1.19
);

static const Element IRON(
	26, "Fe", 1.16
);

static const Element COBALT(
	27, "Co", 1.11
);

static const Element NICKEL(
	28, "Ni", 1.10
);

static const Element COPPER(
	29, "Cu", 1.12
);

static const Element ZINC(
	30, "Zn", 1.18
);

static const Element GALLIUM(
	31, "Ga", 1.24
);

static const Element GERMANIUM(
	32, "Ge", 1.21
);

static const Element ARSENIC(
	33, "As", 1.21
);

static const Element SELENIUM(
	34, "Se", 1.16
);

static const Element BROMINE(
	35, "Br", 1.14
);

static const Element KRYPTON(
	36, "Kr", 1.17
);

static const Element RUBIDIUM(
	37, "Rb", 2.10
);

static const Element STRONTIUM(
	38, "Sr", 1.85
);

static const Element YTTRIUM(
	39, "Y ", 1.63
);

static const Element ZIRCONIUM(
	40, "Zr", 1.54
);

static const Element NIOBIUM(
	41, "Nb", 1.47
);

static const Element MOLYBDENUM(
	42, "Mo", 1.38
);

static const Element TECHNETIUM(
	43, "Tc", 1.27
);

static const Element RUTHENIUM(
	44, "Ru", 1.25
);

static const Element RHODIUM(
	45, "Rh", 1.25
);

static const Element PALLADIUM(
	46, "Pd", 1.20
);

static const Element SILVER(
	47, "Ag", 1.28
);

static const Element CADMIUM(
	48, "Cd", 1.36
);

static const Element INDIUM(
	49, "In", 1.40
);

static const Element TIN(
	50, "Sn", 1.42
);

static const Element ANTIMONY(
	51, "Sb", 1.40
);

static const Element TELLURIUM(
	52, "Te", 1.36
);

static const Element IODINE(
	53, "I", 1.33
);

static const Element XENON(
	54, "Xe", 1.31
);

static const Element CAESIUM(
	55, "Cs", 2.32
);

static const Element BARIUM(
	56, "Ba", 1.96
);

static const Element LANTHANUM(
	57, "La", 1.80
);

static const Element CERIUM(
	58, "Ce", 1.63
);

static const Element PRASEODYMIUM(
	59, "Pr", 1.76
);

static const Element NEODYMIUM(
	60, "Nd", 1.74
);

static const Element PROMETHIUMM(
	61, "Pm", 1.73
);

static const Element SAMARIUM(
	62, "Sm", 1.72
);

static const Element EUROPIUM(
	63, "Eu", 1.68
);

static const Element GADOLINIUM(
	64, "Gd", 1.69
);

static const Element TERBIUM(
	65, "Tb", 1.68
);

static const Element DYSPROSIUM(
	66, "Dy", 1.67
);

static const Element HOLMIUM(
	67, "Ho", 1.66
);

static const Element ERBIUM(
	68, "Er", 1.65
);

static const Element THULIUM(
	69, "Tm", 1.64
);

static const Element YTTERBIUM(
	70, "Yb", 1.70
);

static const Element LUTETIUM(
	71, "Lu", 1.62
);

static const Element HAFNIUM(
	72, "Hf", 1.52
);

static const Element TANTALUM(
	73, "Ta", 1.46
);

static const Element TUNGSTEN(
	74, "W", 1.37
);

static const Element RHENIUM(
	75, "Re", 1.31
);

static const Element OSMIUM(
	76, "Os", 1.29
);

static const Element IRIDIUM(
	77, "Ir", 1.22
);

static const Element PLATINUM(
	78, "Pt", 1.23
);

static const Element GOLD(
	79, "Au", 1.24
);

static const Element MERCURY(
	80, "Hg", 1.33
);

static const Element THALLIUM(
	81, "Tl", 1.44
);

static const Element LEAD(
	82, "Pb", 1.44
);

static const Element BISMUTH(
	83, "Bi", 1.51
);

static const Element POLONIUM(
	84, "Po", 1.45
);

static const Element ASTATINE(
	85, "At", 1.47
);

static const Element RADON(
	86, "Rn", 1.42
);

static const Element FRANCIUM(
	87, "Fr", 2.23
);

static const Element RADIUM(
	88, "Ra", 2.01
);

static const Element ACTINIUM(
	89, "Ac", 1.86
);

static const Element THORIUM(
	90, "Th", 1.75
);

static const Element PROTACTINIUM(
	91, "Pa", 1.69
);

static const Element URANIUM(
	92, "U", 1.70
);

static const Element NEPTUNIUM(
	93, "Np", 1.71
);

static const Element PLUTONIUM(
	94, "Pu", 1.72
);

static const Element AMERICIUM(
	95, "Am", 1.66
);

static const Element CURIUM(
	96, "Cm", 1.66
);

static const Element BERKELIUM(
	97, "Bk", 1.68
);

static const Element CALIFONIUM(
	98, "Cf", 1.68
);

static const Element EINSTEINIUM(
	99, "Es", 1.65
);

static const Element FERMIUM(
	100, "Fm", 1.67
);

static const Element MENDELEVIUM(
	101, "Md", 1.73
);

static const Element NOBELIUM(
	102, "No", 1.76
);

static const Element LAWRENCIUM(
	103, "Lr", 1.61
);

static const Element RUTHERFORDIUM(
	104, "Rf", 1.57
);

static const Element DUBNIUM(
	105, "Db", 1.49
);

static const Element SEABORGIUM(
	106, "Sg", 1.43
);

static const Element BOHRIUM(
	107, "Bh", 1.41
);

static const Element HASSIUM(
	108, "Hs", 1.34
);

static const Element MEITNERIUM(
	109, "Mt", 1.29
);

static const Element DARMSTADTIUM(
	110, "Ds", 1.28
);

static const Element ROENTGENIUM(
	111, "Rg", 1.21
);

// find data on the following atoms -> this data is assumed not taken from reliable sources (covalent Radii)

static const Element COPERNICIUM(
	112, "Cn", 1.50
);

static const Element NIHONIUM(
	113, "Nh", 1.50
);

static const Element FLEROVIUM(
	114, "Fl", 1.50
);

static const Element MOSCOVIUM(
	115, "Mc", 1.50
);

static const Element LIVERMORIUM(
	116, "Lv", 1.50
);

static const Element TENNESSINE(
	117, "Ts", 1.50
);

static const Element OGANESSON(
	118, "Og", 1.50
);