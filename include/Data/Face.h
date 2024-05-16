#pragma once 
#include "Data/api.h"

#include <memory>
#include "Data/HalfEdge.h"

namespace ctkData {
	namespace SurfaceUtils {

		class Face {
		public:
			//! Default constructor.
			Face() = default;
			//! Default Destructor.
			~Face() = default;
			//! Constructor which provides a pointer to the identifying half-edge object.
			Face(std::shared_ptr<HalfEdge> edge) : _edge(edge) {};
			//! Copy constructor.
			Face(const Face& face) : _edge(face.getEdge()) {};
			//! Get function for retrieving the identifying half-edge object pointer.
			std::shared_ptr<HalfEdge> getEdge() const { return _edge; };

			//! Calculates the face's normal vector based on the its defining vertices.
			/*!
			* The calculation is performed by taking the cross product of two of the edge vectors that define the face.
			*/
			void calculateNormal() {
				double v1[3];
				double v2[3];

				v1[0] = _edge->getNext()->getOriginX() - _edge->getOriginX();
				v1[1] = _edge->getNext()->getOriginY() - _edge->getOriginY();
				v1[2] = _edge->getNext()->getOriginZ() - _edge->getOriginZ();

				v2[0] = _edge->getPrevious()->getOriginX() - _edge->getOriginX();
				v2[1] = _edge->getPrevious()->getOriginY() - _edge->getOriginY();
				v2[2] = _edge->getPrevious()->getOriginZ() - _edge->getOriginZ();

				_norm[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
				_norm[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
				_norm[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

				double nn = (_norm[0] * _norm[0]) + (_norm[1] * _norm[1]) + (_norm[2] * _norm[2]);
				nn = sqrt(nn);

				_norm[0] /= nn;
				_norm[1] /= nn;
				_norm[2] /= nn;
			};



			//! Get function for the face normal vector (\f$x\f$ coordinate). 
			double getNormalX() const { return _norm[0]; };
			//! Get function for the face normal vector (\f$y\f$ coordinate).
			double getNormalY() const { return _norm[1]; };
			//! Get function for the face normal vector (\f$z\f$ coordinate).
			double getNormalZ() const { return _norm[2]; };

			int _count;

		private:
			double _norm[3] = { 0.0, 0.0, 0.0 }; 	//!< The face's normal vector 
			// unsigned int _id;
			std::shared_ptr<HalfEdge> _edge; 		//!< The face's identifying half-edge object's pointer 
			// Face* _next;

		};
	}
}