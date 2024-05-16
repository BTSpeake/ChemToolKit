#pragma once 
#include "Data/api.h"

#include "Data/Vertex.h"

namespace ctkData {
	namespace SurfaceUtils {

		class Face;

		//! The half-edge class for a half-edge based data struture 
		/*!
		* Defines a half-edge data object based on the half-edge data structure for 3D volumetric data.
		*/
		class HalfEdge : public std::enable_shared_from_this<HalfEdge> {
		public:
			//! Default constructor
			HalfEdge() = default;
			//! Constructor providing a unique id to the half-edge
			HalfEdge(unsigned int id) : _id(id) {};
			//! Default constructor
			~HalfEdge() = default;

			//! Sets the half-edge's origin reference
			void setOrigin(std::shared_ptr<Vertex> v) { _origin = v; };

			//! Sets the half-edge's face reference
			void setFace(std::shared_ptr<Face> face) { _face = face; };

			//! Sets the half-edges's previous connection reference 
			/*! The previous half-edge connection which defines a given face. */
			void setPrevious(std::shared_ptr<HalfEdge> prev) {
				_prev = prev;
				_prev->_next = shared_from_this();
			};

			//! Sets the half-edges's next connection reference 
			/*! The next half-edge connection which defines a given face. */
			void setNext(std::shared_ptr<HalfEdge> next) {
				_next = next;
				_next->_prev = shared_from_this();
			}

			//void setPrevious_ne(std::shared_ptr<HalfEdge> prev);

			//void setNext_ne(std::shared_ptr<HalfEdge> next);

			//! Sets the edge's twin
			/*! A half-edges twin is defined as the same edge pointing in the opposite direction. */
			void setTwin(std::shared_ptr<HalfEdge> twin) {
				_twin = twin;
			}

			//! Retrieves the half-edges id number 
			unsigned int getId() const { return _id; }

			//! Retrieves the pointer to the previous half-edge object 
			std::shared_ptr<HalfEdge> getPrevious() const { return _prev; }

			//! Retrieves the pointer to the next half-edge object 
			std::shared_ptr<HalfEdge> getNext() const { return _next; }

			//! Retrieves the pointer to the half-edge's twin object 
			std::shared_ptr<HalfEdge> getTwin() const { return _twin; }

			void setXYZ(int x, int y, int z) {
				_x = x;
				_y = y;
				_z = z;
			}

			//! Retrieves the half-edges origin. 
			/*! Retrieves a pointer to the vertex object defining the half-edges origin. */
			std::shared_ptr<Vertex> getOrigin() const { return _origin; }

			//! Retrieves the half-edges origin (\f$x\f$ coordinate).
			double getOriginX() { return (*_origin)[0]; }

			//! Retrieves the half-edges origin (\f$y\f$ coordinate).
			double getOriginY() { return (*_origin)[1]; }

			//! Retrieves the half-edges origin (\f$z\f$ coordinate).
			double getOriginZ() { return (*_origin)[2]; }

			//! Retrieves the pointer to the half-edges corresponding face object  
			std::shared_ptr<Face> getFace() const { return _face; }

			//! Sets the half-edges visited flag 
			void visit(const bool visit) { _visited = visit; }

			//! Gets the half-edges visisted flag 
			bool isVisited() const { return _visited; }

			//! Gets the pointer to the vertex object definining the edge's midpoint 
			std::shared_ptr<Vertex> getMidpoint() const { return _mp; }

			//! Sets the pointer to the vertex object definining the edge's midpoint 
			void setMidPoint(std::shared_ptr<Vertex> mp) { _mp = mp; }

			//! Runs a smoothing algorithm starting at this edge.
			/*! The algorithm can either be a Laplacian style of a basic average (used for loop subdivision).*/
			void smooth(bool lap) {
				if (getOrigin()->isVisited()) {
					return;
				}
				else {
					getOrigin()->visit(true);
				}
				std::shared_ptr<HalfEdge> curEdge = shared_from_this();
				double tmpX = 0.0;
				double tmpY = 0.0;
				double tmpZ = 0.0;
				double beta = 1.0 / 8.0;
				int count = 0;
				do {
					count++;
					tmpX += curEdge->getNext()->getOriginX();
					tmpY += curEdge->getNext()->getOriginY();
					tmpZ += curEdge->getNext()->getOriginZ();
					curEdge = curEdge->getPrevious()->getTwin();

					//if (count == 50) {
					//	std::cout << "While loop reached limit" << std::endl;
					//	break;
					//}
				} while (curEdge != shared_from_this());
				if (lap) {
					tmpX /= count;
					tmpY /= count;
					tmpZ /= count;
				}
				else {
					if (count > 3) {
						beta = 3 / (8 * count);
					}
					else if (count == 3) {
						beta = 3.0 / 16.0;
					}
					tmpX *= beta;
					tmpX += ((1 - (count * beta)) * getOriginX());
					tmpY *= beta;
					tmpY += ((1 - (count * beta)) * getOriginY());
					tmpZ *= beta;
					tmpZ += ((1 - (count * beta)) * getOriginZ());
				}

				getOrigin()->setBuffer(tmpX, tmpY, tmpZ);
			}

			//! Boundary edge flag
			/*! Set to true if the edge is on the external boundary of a 3D surface.*/
			bool _boundary = false;

			std::shared_ptr<Face> _face; 				//!< The corresponding face object's pointer 
		private:
			unsigned int _id;
			int _x;
			int _y;
			int _z;
			std::shared_ptr<Vertex> _origin = 0;		//!< Pointer to the vertex object defining the edge's origin
			std::shared_ptr<HalfEdge> _prev = 0;		//!< Pointer to the previous half-edge
			std::shared_ptr<HalfEdge> _next = 0; 		//!< Pointer to the next half-edge 
			std::shared_ptr<HalfEdge> _twin = 0;		//!< Pointer to the half-edge's twin
			std::shared_ptr<Vertex> _mp = 0;		//!< Pointer to the vertex object defining the edge's midpoint 
			bool _visited = false;						//!< Visited flag for surface traversal 

			HalfEdge(const HalfEdge&) = delete;
			HalfEdge& operator=(const HalfEdge&) = delete;
		};

	}
}