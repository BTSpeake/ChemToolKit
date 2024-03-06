#include "Data/Atom.h"
#include <string>
#include <iostream>

using namespace ctkData;

Atom::Atom(int a, double x, double y, double z)
	: _a(a), _pos(x, y, z) {
    if (atmDict.find(a) == atmDict.end()) {
        _a = 0;
    }
}

Atom::Atom(std::string s, double x, double y, double z)
    : _a(0), _pos(x, y, z) {
    auto a = symbolDict.find(s);
    if (a != symbolDict.end()) {
        _a = a->second;
    }
}

Atom::Atom(const Atom& atm) {
	_a = atm.getAtomicNumber();
	_pos = atm.getPosition();
}

Atom& Atom::operator=(const Atom& atm) {
    if (this == &atm) {
        return *this;
    }
    _a = atm.getAtomicNumber();
    _pos = atm.getPosition();
    return *this; 
}

// Access Functions 
int Atom::getAtomicNumber() const { return _a; };
ctkMaths::Vector3& Atom::getPosition() { return _pos; };
const ctkMaths::Vector3& Atom::getPosition() const { return _pos; };
const char* Atom::getSymbol() const { return Atom::atmDict[_a]; };
unsigned int Atom::nSingleBonds() const { return _nSingle; };
unsigned int Atom::nDoubleBonds() const { return _nDouble; };
unsigned int Atom::nTripleBonds() const { return _nTriple; };
unsigned int Atom::nBonds() const { return _nSingle + _nDouble + _nTriple; };
bool Atom::isAromatic() const { return _isAromatic; };
bool Atom::isAmide() const { return _isAmide; }
double Atom::getCovalentRadii() const { return covRadiiDict[_a]; }

int Atom::coordination() const {
    switch (_a) {
    case 6:
        if (_nSingle == 4) { return 3; };
        if (_nSingle == 2 && _nDouble == 1) { return 2; };
        if (_nTriple == 1 || _nDouble == 2) { return 1; };
        return 0;
    case 7:
        if (_nSingle == 3) { return 3; };
        if (_nDouble == 1) { return 2; };
        if (_nTriple == 1) { return 1; };
        return 0;
    case 8:
        //if (_nSingle == 2) { return 3; };
        //if (_nDouble == 1) { return 2; };
        return 3;
    default:
        return 0;
    }
}

std::string Atom::getSYBYL() const {
    std::string sym = getSymbol();
    int coord;
    switch (_a) {
    // Hydrogen .spc .tp3??
    // Carbon
    case 6: // .cat???
        coord = coordination();
        if (_isAromatic) { return sym + ".ar"; }
        else if (coord == 0) { return sym; }
        else { return sym + "." + std::to_string(coord); }
    // Nitrogen
    case 7: // .p13 (trigonal)
        coord = coordination();
        if (_isAmide) { return sym + ".am"; }
        else if (_isAromatic) { return sym + ".ar"; }
        else if (coord == 0) { return sym; }
        else { return sym + "." + std::to_string(coord); }
    // Oxygen
    case 8: // .co2 .spc .t3p
        coord = coordination();
        if (coord == 2 || coord == 3) { return sym + "." + std::to_string(coordination()); }
        else { return sym; }
    // Phosphorous
    case 15:
        if (coordination() == 3) { return sym + "." + std::to_string(coordination()); }
        else { return sym; }
    // Sulfur 
    case 16: // .o .o2
        coord = coordination();
        if (coord == 2 || coord == 3) { return sym + "." + std::to_string(coordination()); }
        else { return sym; }
    default:
        return sym;
    }
}

// Set Functions 
void Atom::setAtomicNumber(int a) { _a = a; }
void Atom::addSingleBond() { _nSingle++; }
void Atom::addDoubleBond() { _nDouble++; }
void Atom::addTripleBond() { _nTriple++; }
void Atom::removeSingleBond() { _nSingle--; }
void Atom::removeDoubleBond() { _nDouble--; }
void Atom::removeTripleBond() { _nTriple--; }
void Atom::isAromatic(bool aromatic) { _isAromatic = aromatic; }
void Atom::isAmide(bool amide) { _isAmide = amide; }
void Atom::addLabel(std::string label) { _labels.push_back(label); }


// Utility functions 
void Atom::resetBonding() {
    _nSingle = 0;
    _nDouble = 0;
    _nTriple = 0;
}

std::string Atom::toString() const {
    std::string s = static_cast<std::string>(getSymbol()) + ":  " + _pos.toString();
    //s += '\t' + getSYBYL();
    if (_labels.size() > 0) {
        s += "\nLabels: ";
        for (std::string lbl : _labels) {
            s += lbl + ",    ";
        }
    }
    return s;
}

// Static Data

std::map<int, const char*> Atom::atmDict = {
        {  1, "H" }, {  2, "He"}, {  3, "Li"}, {  4, "Be"}, {  5, "B" }, {  6, "C" },
        {  7, "N" }, {  8, "O" }, {  9, "F" }, { 10, "Ne"}, { 11, "Na"}, { 12, "Mg"},
        { 13, "Al"}, { 14, "Si"}, { 15, "P" }, { 16, "S" }, { 17, "Cl"}, { 18, "Ar"},
        { 19, "K" }, { 20, "Ca"}, { 21, "Sc"}, { 22, "Ti"}, { 23, "V" }, { 24, "Cr"},
        { 25, "Mn"}, { 26, "Fe"}, { 27, "Co"}, { 28, "Ni"}, { 29, "Cu"}, { 30, "Zn"},
        { 31, "Ga"}, { 32, "Ge"}, { 33, "As"}, { 34, "Se"}, { 35, "Br"}, { 36, "Kr"},
        { 37, "Rb"}, { 38, "Sr"}, { 39, "Y" }, { 40, "Zr"}, { 41, "Nb"}, { 42, "Mo"},
        { 43, "Tc"}, { 44, "Ru"}, { 45, "Rh"}, { 46, "Pd"}, { 47, "Ag"}, { 48, "Cd"},
        { 49, "In"}, { 50, "Sn"}, { 51, "Sb"}, { 52, "Te"}, { 53, "I" }, { 54, "Xe"},
        { 55, "Cs"}, { 56, "Ba"}, { 57, "La"}, { 58, "Ce"}, { 59, "Pr"}, { 60, "Nd"},
        { 61, "Pm"}, { 62, "Sm"}, { 63, "Eu"}, { 64, "Gd"}, { 65, "Tb"}, { 66, "Dy"},
        { 67, "Ho"}, { 68, "Er"}, { 69, "Tm"}, { 70, "Yb"}, { 71, "Lu"}, { 72, "Hf"},
        { 73, "Ta"}, { 74, "W" }, { 75, "Re"}, { 76, "Os"}, { 77, "Ir"}, { 78, "Pt"},
        { 79, "Au"}, { 80, "Hg"}, { 81, "Tl"}, { 82, "Pb"}, { 83, "Bi"}, { 84, "Po"},
        { 85, "At"}, { 86, "Rn"}, { 87, "Fr"}, { 88, "Ra"}, { 89, "Ac"}, { 90, "Th"},
        { 91, "Pa"}, { 92, "U" }, { 93, "Np"}, { 94, "Pu"}, { 95, "Am"}, { 96, "Cm"},
        { 97, "Bk"}, { 98, "Cf"}, { 99, "Es"}, {100, "Fm"}, {101, "Md"}, {102, "No"},
        {103, "Lr"}, {104, "Rf"}, {105, "Db"}, {106, "Sg"}, {107, "Bh"}, {108, "Hs"},
        {109, "Mt"}, {110, "Ds"}, {111, "Rg"}, {112, "Cn"}, {113, "Nh"}, {114, "Fl"},
        {115, "Mc"}, {116, "Lv"}, {117, "Ts"}, {118, "Og"}, {  0, "Gh"}
};

std::map<std::string, int> Atom::symbolDict = {
        {"H" ,   1}, {"He",   2}, {"Li",   3}, {"Be",   4}, {"B" ,   5}, {"C" ,   6}, {"N" ,   7},
        {"O" ,   8}, {"F" ,   9}, {"Ne",  10}, {"Na",  11}, {"Mg",  12}, {"Al",  13}, {"Si",  14},
        {"P" ,  15}, {"S" ,  16}, {"Cl",  17}, {"Ar",  18}, {"K" ,  19}, {"Ca",  20}, {"Sc",  21},
        {"Ti",  22}, {"V" ,  23}, {"Cr",  24}, {"Mn",  25}, {"Fe",  26}, {"Co",  27}, {"Ni",  28},
        {"Cu",  29}, {"Zn",  30}, {"Ga",  31}, {"Ge",  32}, {"As",  33}, {"Se",  34}, {"Br",  35},
        {"Kr",  36}, {"Rb",  37}, {"Sr",  38}, {"Y" ,  39}, {"Zr",  40}, {"Nb",  41}, {"Mo",  42},
        {"Tc",  43}, {"Ru",  44}, {"Rh",  45}, {"Pd",  46}, {"Ag",  47}, {"Cd",  48}, {"In",  49},
        {"Sn",  50}, {"Sb",  51}, {"Te",  52}, {"I" ,  53}, {"Xe",  54}, {"Cs",  55}, {"Ba",  56},
        {"La",  57}, {"Ce",  58}, {"Pr",  59}, {"Nd",  60}, {"Pm",  61}, {"Sm",  62}, {"Eu",  63},
        {"Gd",  64}, {"Tb",  65}, {"Dy",  66}, {"Ho",  67}, {"Er",  68}, {"Tm",  69}, {"Yb",  70},
        {"Lu",  71}, {"Hf",  72}, {"Ta",  73}, {"W" ,  74}, {"Re",  75}, {"Os",  76}, {"Ir",  77},
        {"Pt",  78}, {"Au",  79}, {"Hg",  80}, {"Tl",  81}, {"Pb",  82}, {"Bi",  83}, {"Po",  84},
        {"At",  85}, {"Rn",  86}, {"Fr",  87}, {"Ra",  88}, {"Ac",  89}, {"Th",  90}, {"Pa",  91},
        {"U" ,  92}, {"Np",  93}, {"Pu",  94}, {"Am",  95}, {"Cm",  96}, {"Bk",  97}, {"Cf",  98},
        {"Es",  99}, {"Fm", 100}, {"Md", 101}, {"No", 102}, {"Lr", 103}, {"Rf", 104}, {"Db", 105},
        {"Sg", 106}, {"Bh", 107}, {"Hs", 108}, {"Mt", 109}, {"Ds", 110}, {"Rg", 111}, {"Cn", 112},
        {"Nh", 113}, {"Fl", 114}, {"Mc", 115}, {"Lv", 116}, {"Ts", 117}, {"Og", 118}, {"Gh",   0}
};

// Taken from the QUEST collection of computational chemistry codes
// Values are in Angstroms
std::map<int, double> Atom::covRadiiDict = {
        {  1, 0.32}, {  2, 0.46}, {  3, 1.33}, {  4, 1.04}, {  5, 0.85}, {  6, 0.75},
        {  7, 0.71}, {  8, 0.63}, {  9, 0.64}, { 10, 0.67}, { 11, 1.55}, { 12, 1.39},
        { 13, 1.26}, { 14, 1.16}, { 15, 1.11}, { 16, 1.03}, { 17, 0.80}, { 18, 0.96},
        { 19, 1.96}, { 20, 1.71}, { 21, 1.48}, { 22, 1.36}, { 23, 1.34}, { 24, 1.22},
        { 25, 1.19}, { 26, 1.16}, { 27, 1.11}, { 28, 1.10}, { 29, 1.12}, { 30, 1.18},
        { 31, 1.24}, { 32, 1.21}, { 33, 1.21}, { 34, 1.16}, { 35, 1.14}, { 36, 1.17},
        { 37, 2.10}, { 38, 1.85}, { 39, 1.63}, { 40, 1.54}, { 41, 1.47}, { 42, 1.38},
        { 43, 1.27}, { 44, 1.25}, { 45, 1.25}, { 46, 1.20}, { 47, 1.28}, { 48, 1.36},
        { 49, 1.42}, { 50, 1.40}, { 51, 1.40}, { 52, 1.36}, { 53, 1.33}, { 54, 1.31},
        { 55, 2.32}, { 56, 1.96}, { 57, 1.80}, { 58, 1.63}, { 59, 1.76}, { 60, 1.74},
        { 61, 1.73}, { 62, 1.72}, { 63, 1.68}, { 64, 1.69}, { 65, 1.68}, { 66, 1.67},
        { 67, 1.66}, { 68, 1.65}, { 69, 1.64}, { 70, 1.70}, { 71, 1.62}, { 72, 1.52},
        { 73, 1.46}, { 74, 1.37}, { 75, 1.31}, { 76, 1.29}, { 77, 1.22}, { 78, 1.23},
        { 79, 1.24}, { 80, 1.33}, { 81, 1.44}, { 82, 1.44}, { 83, 1.51}, { 84, 1.45},
        { 85, 1.47}, { 86, 1.42}, { 87, 2.23}, { 88, 2.01}, { 89, 1.86}, { 90, 1.75},
        { 91, 1.69}, { 92, 1.70}, { 93, 1.71}, { 94, 1.72}, { 95, 1.66}, { 96, 1.66},
        { 97, 1.68}, { 98, 1.68}, { 99, 1.65}, {100, 1.67}, {101, 1.73}, {102, 1.76},
        {103, 1.61}, {104, 1.57}, {105, 1.49}, {106, 1.43}, {107, 1.41}, {108, 1.34},
        {109, 1.29}, {110, 1.28}, {111, 1.21}, 
        // find data on the following atoms 
        {112, 1.50}, {113, 1.50}, {114, 1.50},
        {115, 1.50}, {116, 1.50}, {117, 1.50}, {118, 1.50}, {  0, 1.00} // should ghost act as no bonding??
};
