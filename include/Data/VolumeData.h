#pragma once 
#include "Data/api.h"

#include <vector>

namespace ctkData {

	class DATA_API VolumeData {
	public:
		VolumeData(int dim[]);
		~VolumeData();

		void addNewValue(const double x, const double y, const double z, const double val);
		void addNewValue(const double val);
		void setValue(const int i, const double x, const double y, const double z, const double val);
		void setValue(const int i, const double val);

		const int* getDimension() const;
		const double getGridX(const int i) const;
		const double getGridY(const int i) const;
		const double getGridZ(const int i) const;
		const double getData(const int i) const;
		bool hasColourData() const;
		float getColourHue(unsigned int i) const;
	private:
		int _dim[3];
		std::vector<double> _grid;
		std::vector<double> _data;
		std::vector<float>	_colour;
	};

}