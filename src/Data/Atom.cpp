#include "Data/Atom.h"
#include <string>
#include <iostream>

using namespace ctkData;

Atom::Atom(int a, double x, double y, double z)
	: _a(a), _pos(x, y, z) {
    _connections.reserve(4);
    _doubles.reserve(2);
    _triples.reserve(1);
}

Atom::Atom(std::string s, double x, double y, double z)
    : _a(0), _pos(x, y, z) {
    auto a = symbolDict.find(s);
    if (a != symbolDict.end()) {
        _a = a->second;
    }
    _connections.reserve(4);
    _doubles.reserve(2);
    _triples.reserve(1);
}

Atom::Atom(const Atom& atm) {
	_a = atm.getAtomicNumber();
	_pos = atm.getPosition();
    _connections.reserve(4);
    _doubles.reserve(2);
    _triples.reserve(1);
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
const short Atom::getAtomicNumber() const { return _a; };
ctkMaths::Vector3& Atom::getPosition() { return _pos; };
const ctkMaths::Vector3& Atom::getPosition() const { return _pos; };

const char* Atom::getSymbol() const { return Atom::periodicTable[_a].symbol; };

unsigned int Atom::nSingleBonds() const { return _connections.size() - nDoubleBonds() - nTripleBonds(); };
unsigned int Atom::nDoubleBonds() const { return _doubles.size(); };
unsigned int Atom::nTripleBonds() const { return _triples.size(); };
unsigned int Atom::nBonds() const { return _connections.size(); };
bool Atom::isAromatic() const { return _isAromatic; };
bool Atom::isAmide() const { return _isAmide; }

float Atom::getCovalentRadii() const { return Atom::periodicTable[_a].covalentRadii; }

bool Atom::isConnected(const Atom* a) const {
    return (std::find(_connections.begin(), _connections.end(), a) != _connections.end());
}

bool Atom::isDouble(const Atom* a) const {
    return (std::find(_doubles.begin(), _doubles.end(), a) != _doubles.end());
}

bool Atom::isTriple(const Atom* a) const {
    return (std::find(_triples.begin(), _triples.end(), a) != _triples.end());
}

const std::vector<Atom*>& Atom::connections() const {
    return _connections;
}

int Atom::coordination() const {
    switch (_a) {
    case 6:
        if (nSingleBonds() == 4) { return 3; };
        if (nSingleBonds() == 2 && nDoubleBonds() == 1) { return 2; };
        if (nTripleBonds() == 1 || nDoubleBonds() == 2) { return 1; };
        return 0;
    case 7:
        if (nSingleBonds() == 3) { return 3; };
        if (nDoubleBonds() == 1) { return 2; };
        if (nTripleBonds() == 1) { return 1; };
        return 0;
    case 8:
        //if (nSingleBonds() == 2) { return 3; };
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

int Atom::standardValence() const {
    switch (_a) {
    case 1:
        return 1;
    case 5:
    case 7:
    case 13:
    case 15:
    case 31:
        return 3; 
    case 6:
    case 14:
    case 32:
        return 4; 
    case 8:
    case 16:
    case 34:
    case 52:
        return 2;
    case 9:
    case 17:
    case 35:
    case 53:
        return 1;
    default:
        return 0;
    }
}

const double Atom::getMass() const {
    return 0;
}

#ifdef WITH_CTK_GRAPHICS
const float* Atom::getColour() const {
    return Atom::periodicTable[_a].colour;
}
#endif

// Set Functions 
void Atom::setAtomicNumber(int a) { _a = a; }
void Atom::updatePosition(const double x, const double y, const double z) {
    _pos.setX(x);
    _pos.setY(y);
    _pos.setZ(z);
}

bool Atom::addConnection(Atom* a) {
    if (isConnected(a)) {
        return false;
    }
    _connections.push_back(a);
    return true;
}

bool Atom::addConnection(Atom* a, int bo) {
    if (addConnection(a)) {
        if (bo == 2) {
            _doubles.push_back(a);
        }
        else if (bo == 3) {
            _triples.push_back(a);
        }
        return true;
    }
    else if (bo == 1) {
        return false;
    }
    else {
        for (auto i = 0; i < _doubles.size(); i++) {
            if (_doubles[i] == a) {
                _doubles.erase(_doubles.begin() + i);
                break;
            }
        }
        for (auto i = 0; i < _triples.size(); i++) {
            if (_triples[i] == a) {
                _triples.erase(_triples.begin() + i);
                break;
            }
        }
        if (bo == 2) {
            _doubles.push_back(a);
        }
        else if (bo == 3) {
            _triples.push_back(a);
        }
        else {
            return false;
        }
    }
    return true;
}

void Atom::removeConnection(Atom* a) {
    for (auto i = 0; i < _connections.size(); i++) {
        if (_connections[i] == a) {
            _connections.erase(_connections.begin() + i);
            break;
        }
    }
    for (auto i = 0; i < _doubles.size(); i++) {
        if (_doubles[i] == a) {
            _doubles.erase(_doubles.begin() + i);
            break;
        }
    }
    for (auto i = 0; i < _triples.size(); i++) {
        if (_triples[i] == a) {
            _triples.erase(_triples.begin() + i);
            break;
        }
    }
}

void Atom::isAromatic(bool aromatic) { _isAromatic = aromatic; }
void Atom::isAmide(bool amide) { _isAmide = amide; }
void Atom::addLabel(std::string label) { _labels.push_back(label); }


// Utility functions 
void Atom::resetBonding() {
    _connections.clear();
    _doubles.clear();
    _triples.clear();
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
// \todo change this to a switch style function instead of additional persitant data? 
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

AtomData::PeriodicTable Atom::periodicTable = AtomData::PeriodicTable();
