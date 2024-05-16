#pragma once 
#include "Data/api.h"

#include <map>
#include <vector>

#include "Data/Vertex.h"
#include "Data/HalfEdge.h"
#include "Data/Face.h"
#include "Data/VolumeData.h"

//#ifdef WITH_CTK_GRAPHICS
//#include <vtkPolyData.h>
//#include <vtkPointData.h>
//#endif 

namespace ctkData {

	class DATA_API Surface {
	public:
		Surface(const VolumeData& vol);
		~Surface();

		void MarchingCubes(const double isoValue);
		void laplacianSmoothing();
		void calculateVertexNormals();
		void subdivide();

		//! Returns the number of triangular faces that make up the surface
		const int nFaces() const;

		/*! \brief Generates an OpenGL compatable vertex mesh
		* Takes the half-edge based data structure alongside colour information for 3D volumetric input data
		* and generates a 32-bit float array of vertices compatable with OpenGL shader programs. Each vertex
		* entry is defined as a list of 9 32-bit float values in the form (x, y, z, r, g, b, nx, ny, nz).
		*/
		void generateOpenGLMesh(float* glMesh);

#ifdef WITH_CTK_GRAPHICS
		//void generatePolyData(vtkPolyData* pd) const;
#endif 

	private:
		//std::map<std::pair<unsigned int, unsigned int>, std::shared_ptr<SurfaceUtils::HalfEdge>> _edgeMap;
		std::map<unsigned int, std::shared_ptr<SurfaceUtils::HalfEdge>> _vertexMap;
		std::vector<std::shared_ptr<SurfaceUtils::HalfEdge>> _faceEdges;
		const VolumeData* _vol;

		//! Determines the indices within the input data that define a given cube 
		void calculateIndexes(unsigned int vIndx[8], int x, int y, int z, int dimY, int dimZ);

		//! Returns a unique id for a given edge 
		unsigned int getEdgeId(int i, unsigned int vIndx[8]);

		//! Interpolates between two points scaled by the iso-value 
		std::shared_ptr<SurfaceUtils::Vertex> interpolate(const double g0[3], const double g1[3], const double& d0, const double& d1, const double& isoVal);

		/*! \brief Recursive function for assigning successive boundary cases as Null edges.
		* Each case will link around the boundary with next/previous and the boundary
		* faces via their twins. Their face values remain unassigned.
		*/
		void assignNullEdge(std::shared_ptr<SurfaceUtils::HalfEdge> startE, std::shared_ptr<SurfaceUtils::HalfEdge> nextNull);

		//! Split a given edge as defined by the loop-subdivision algorithm
		void subdivideEdge(std::shared_ptr<SurfaceUtils::HalfEdge> edge);

		//! Runs a smoothing algorithm on the iso-surface (either Laplacian or subdivision)
		void smooth(bool lap);

		//! Creates a ne Vertex halfway along the given edge 
		std::shared_ptr<SurfaceUtils::Vertex> newBoundaryVertex(std::shared_ptr<SurfaceUtils::HalfEdge> edge);

		//! Creates a new Vertex along a given edge, scaled as defined for Loop-subdivision
		std::shared_ptr<SurfaceUtils::Vertex> newInternalVertex(std::shared_ptr<SurfaceUtils::HalfEdge> edge);



		Surface(const Surface&) = delete;
		Surface& operator=(const Surface&) = delete;
	};



	// Should this be moved elsewhere
	//! Function to generate an rgb colour value from a given angle in degrees
	/*! Performs a HSV -> RGB colour conversion with fixed S(=0.8) and V(=0.6) values.*/
	void generateRGBColour(float* rgb, const float& angle) {


		float m, c, s, v;
		s = 0.8f;
		v = 0.6f;

		float hue = angle + 180.0f; // adjusting colour scale to make +ve phase/value blue
		if (hue < 0.0f) {
			hue += 360.0f;
		}
		else if (hue >= 360.0f) {
			hue -= 360.0f;
		}
		float x = 1 - std::abs(std::fmod(hue / 60.0f, 2) - 1);

		c = v * s;
		m = v - c;

		x = (c * x) + m;
		c = c + m;

		if (hue < 60) {
			rgb[0] = c;
			rgb[1] = x;
			rgb[2] = m;
		}
		else if (hue < 120) {
			rgb[0] = x;
			rgb[1] = c;
			rgb[2] = m;
		}
		else if (hue < 180) {
			rgb[0] = m;
			rgb[1] = c;
			rgb[2] = x;
		}
		else if (hue < 240) {
			rgb[0] = m;
			rgb[1] = x;
			rgb[2] = c;
		}
		else if (hue < 300) {
			rgb[0] = x;
			rgb[1] = m;
			rgb[2] = c;
		}
		else if (hue < 360) {
			rgb[0] = c;
			rgb[1] = m;
			rgb[2] = x;
		}
		else {
			rgb[0] = 0.0f;
			rgb[1] = 0.0f;
			rgb[2] = 0.0f;
		}
	}
}