#include "Data/VolumeData.h"

using namespace ctkData;

VolumeData::VolumeData(int dim[])
	: _dim{ dim[0], dim[1], dim[2] } {
	int tot = dim[0] * dim[1] * dim[2];
	_grid.reserve(tot * 3);
	_data.reserve(tot);
}

VolumeData::~VolumeData() {
	delete[] _dim;
}

void VolumeData::addNewValue(const double x, const double y, const double z, const double val) {
	if (_data.size() <= _data.capacity()) {
		_grid.push_back(x);
		_grid.push_back(y);
		_grid.push_back(z);
		_data.push_back(val);
	}
}

inline void VolumeData::addNewValue(const double val) {
	if (_data.size() <= _data.capacity()) {
		_data.push_back(val);
	}
}

void VolumeData::setValue(const int i, const double x, const double y, const double z, const double val) {
	if (i < _data.capacity()) {
		int gi = 3 * i;
		_grid[gi] = x;
		_grid[gi + 1] = y;
		_grid[gi + 2] = z;
		_data[i] = val;
	}
}

inline void VolumeData::setValue(const int i, const double val) {
	if (i < _data.capacity()) {
		_data[i] = val;
	}
}

inline const int* VolumeData::getDimension() const {
	return _dim;
}

const double VolumeData::getGridX(const int i) const {
	return _grid[i * 3];
}
const double VolumeData::getGridY(const int i) const {
	return _grid[i * 3 + 1];
}
const double VolumeData::getGridZ(const int i) const {
	return _grid[i * 3 + 2];
}
const double VolumeData::getData(const int i) const {
	return _data[i];
}

bool VolumeData::hasColourData() const {
	return (_colour.size() == _data.size());
}

float VolumeData::getColourHue(unsigned int i) const {
	return _colour[i];
}