#pragma once 
#include "Data/api.h"

#include "Maths/Vector3.h"

namespace ctkData {
	namespace SurfaceUtils {

		class Vertex {
		public:
			Vertex() : _pos(0.0, 0.0, 0.0) {}
			Vertex(const double x, const double y, const double z) : _pos(x, y, z) {}
			~Vertex() = default;
			double operator[](const int& i) const { return _pos[i]; }
			Vertex& operator*=(const double& s) {
				_pos *= s;
				return *this;
			}
			Vertex& operator/=(const double& s) {
				_pos /= s;
				return *this;
			}
			Vertex& operator=(const Vertex& v) {
				_pos.setX(v[0]);
				_pos.setY(v[1]);
				_pos.setZ(v[2]);
			}
			Vertex operator-(const Vertex& v) const { return Vertex(_pos[0] - v[0], _pos[1] - v[1], _pos[2] - v[2]); }
			Vertex operator+(const Vertex& v) const { return Vertex(_pos[0] + v[0], _pos[1] + v[1], _pos[2] + v[2]); }
			Vertex& operator+=(const Vertex& v) {
				_pos += v.getPosition();
				return *this;
			}
			Vertex& operator-=(const Vertex& v) {
				_pos -= v.getPosition();
				return *this;
			}

			void setBuffer(const double x, const double y, const double z) {
				_buf.setX(x);
				_buf.setY(y);
				_buf.setZ(z);
			}
			void setNormal(const double x, const double y, const double z) {
				_nrm.setX(x);
				_nrm.setY(y);
				_nrm.setZ(z);
			}
			void update() {
				_pos.setX(_buf[0]);
				_pos.setY(_buf[1]);
				_pos.setZ(_buf[2]);
			}

			const ctkMaths::Vector3& getPosition() const {
				return _pos;
			}
			const ctkMaths::Vector3& getNormal() const {
				return _nrm;
			}

			bool isVisited() const { return _visited; }
			void visit(const bool visit) { _visited = visit; }

		private:
			ctkMaths::Vector3 _pos;
			ctkMaths::Vector3 _buf;
			ctkMaths::Vector3 _nrm;
			bool _visited;

		};
	}
}