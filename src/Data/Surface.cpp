#include "Data/Surface.h"

using namespace ctkData;
using namespace ctkData::SurfaceUtils;

Surface::Surface(const VolumeData& vol) : _vol(&vol) {}

Surface::~Surface() {
    _vertexMap.clear();
    _faceEdges.clear();
}


/*!
* Marching cubes algorithm for creating an iso-surface from a uniform grid of points
* given a specific iso-value. Creates a mesh object containing the relevant information
* in a HalfEdge data structure.
*/
void Surface::MarchingCubes(const double isoValue) {

    std::map<std::pair<unsigned int, unsigned int>, std::shared_ptr<SurfaceUtils::HalfEdge>> _edgeMap;

    unsigned short tabInd;
    unsigned int vIndx[8];

    unsigned int eIs[2];
    double g0[3];
    double g1[3];

    short triTable[256][16] = {
            { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
            {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
            {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
            {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
            {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
            {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
            {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
            {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
            {9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
            {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
            {3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
            {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
            {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
            {4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
            {9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
            {5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
            {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
            {9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
            {0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
            {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
            {10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
            {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
            {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
            {5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
            {9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
            {0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
            {1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
            {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
            {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
            {2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
            {7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
            {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
            {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
            {11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
            {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
            {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
            {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
            {11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
            {1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
            {9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
            {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
            {2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
            {0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
            {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
            {6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
            {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
            {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
            {6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
            {5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
            {1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
            {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
            {6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
            {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
            {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
            {3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
            {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
            {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
            {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
            {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
            {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
            {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
            {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
            {10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
            {10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
            {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
            {1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
            {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
            {0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
            {10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
            {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
            {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
            {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
            {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
            {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
            {3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
            {6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
            {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
            {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
            {10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
            {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
            {7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
            {7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
            {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
            {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
            {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
            {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
            {0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
            {7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
            {10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
            {2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
            {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
            {7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
            {2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
            {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
            {10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
            {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
            {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
            {7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
            {6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
            {8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
            {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
            {6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
            {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
            {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
            {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
            {8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
            {0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
            {1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
            {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
            { 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 },
            { 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 },
            { 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
            { 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 },
            { 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 },
            { 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1 },
            { 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 },
            { 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 },
            { 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 },
            { 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 },
            { 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 },
            { 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 },
            { 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 },
            { 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 },
            { 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 },
            { 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 },
            { 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 },
            { 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 },
            { 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 },
            { 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 },
            { 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 },
            { 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 },
            { 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 },
            { 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 },
            { 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 },
            { 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 },
            { 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 },
            { 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 },
            { 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 },
            { 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 },
            { 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 },
            { 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 },
            { 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 },
            { 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 },
            { 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
            { 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 },
            { 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 },
            { 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 },
            { 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 },
            { 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 },
            { 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
            { 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 },
            { 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 },
            { 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 },
            { 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 },
            { 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 },
            { 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 },
            { 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 },
            { 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 },
            { 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 },
            { 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 },
            { 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 },
            { 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 },
            { 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 },
            { 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 },
            { 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 },
            { 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 },
            { 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 },
            { 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 },
            { 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 },
            { 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 },
            { 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 },
            { 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 },
            { 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 },
            { 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 },
            { 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
            { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }
    };

    int fc = 0;
    const int* dim = _vol->getDimension();

    // #pragma omp parallel for
    for (auto x = 0; x < (dim[0] - 1); x++) {
        // unsigned short tabInd;
        // unsigned int vIndx[8];

        // unsigned int eIs[2];
        // double g0[3];
        // double g1[3];
        for (auto y = 0; y < (dim[1] - 1); y++) {
            for (auto z = 0; z < (dim[2] - 1); z++) {

                calculateIndexes(vIndx, x, y, z, dim[1], dim[2]);
                tabInd = 0;
                if (_vol->getData(vIndx[0]) <= isoValue) { tabInd |= 1; }
                if (_vol->getData(vIndx[1]) <= isoValue) { tabInd |= 2; }
                if (_vol->getData(vIndx[2]) <= isoValue) { tabInd |= 4; }
                if (_vol->getData(vIndx[3]) <= isoValue) { tabInd |= 8; }
                if (_vol->getData(vIndx[4]) <= isoValue) { tabInd |= 16; }
                if (_vol->getData(vIndx[5]) <= isoValue) { tabInd |= 32; }
                if (_vol->getData(vIndx[6]) <= isoValue) { tabInd |= 64; }
                if (_vol->getData(vIndx[7]) <= isoValue) { tabInd |= 128; }

                if (tabInd == 0) { continue; }
                if (tabInd == 255) { continue; }

                std::shared_ptr<Face> pface;

                for (auto i = 0; i < 16; i++) {
                    if (triTable[tabInd][i] == -1) { break; }

                    unsigned int id = getEdgeId(triTable[tabInd][i], vIndx);
                    std::shared_ptr<HalfEdge> pedge = std::make_shared<HalfEdge>(id);
                    pedge->setXYZ(x, y, z);
                    if ((i % 3) == 0) {
                        // pface = new Face(pedge);
                        pface = std::make_shared<Face>(pedge);
                        pface->_count = fc;
                        fc++;
                        _faceEdges.push_back(pedge);
                    }
                    else if ((i % 3) == 1) {
                        pface->getEdge()->setNext(pedge);

                        // Set twin for the previous edge if one exists
                        unsigned int pId = pface->getEdge()->getId();
                        _edgeMap[std::pair<unsigned int, unsigned int>(pId, id)] = pface->getEdge();
                        if (_edgeMap.find(std::pair<unsigned int, unsigned int>(id, pId)) != _edgeMap.end()) {
                            pface->getEdge()->setTwin(_edgeMap[std::pair<unsigned int, unsigned int>(id, pId)]);
                            _edgeMap[std::pair<unsigned int, unsigned int>(id, pId)]->setTwin(pface->getEdge());
                        }
                    }
                    else if ((i % 3) == 2) {
                        pface->getEdge()->setPrevious(pedge);
                        pface->getEdge()->getNext()->setNext(pedge);

                        // Set twin for the previous edge if one exists
                        unsigned int pId = pface->getEdge()->getNext()->getId();
                        _edgeMap[std::pair<unsigned int, unsigned int>(pId, id)] = pface->getEdge()->getNext();
                        if (_edgeMap.find(std::pair<unsigned int, unsigned int>(id, pId)) != _edgeMap.end()) {
                            _edgeMap[std::pair<unsigned int, unsigned int>(id, pId)]->setTwin(pface->getEdge()->getNext());
                            pface->getEdge()->getNext()->setTwin(_edgeMap[std::pair<unsigned int, unsigned int>(id, pId)]);
                        }

                        // Set twin for the current edge if one exists 
                        unsigned int nId = pface->getEdge()->getId();
                        _edgeMap[std::pair<unsigned int, unsigned int>(id, nId)] = pedge;
                        if (_edgeMap.find(std::pair<unsigned int, unsigned int>(nId, id)) != _edgeMap.end()) {
                            _edgeMap[std::pair<unsigned int, unsigned int>(nId, id)]->setTwin(pedge);
                            pface->getEdge()->getPrevious()->setTwin(_edgeMap[std::pair<unsigned int, unsigned int>(nId, id)]);
                            _edgeMap[std::pair<unsigned int, unsigned int>(nId, id)]->setTwin(pface->getEdge()->getPrevious());
                        }
                    }
                    pedge->setFace(pface);

                    if (_vertexMap.find(id) != _vertexMap.end()) {
                        pedge->setOrigin(_vertexMap[id]->getOrigin());
                        continue;
                    }
                    else {
                        _vertexMap[id] = pedge;
                    }

                    switch (triTable[tabInd][i]) {
                    case 0:
                        eIs[0] = vIndx[0];
                        eIs[1] = vIndx[1];
                        break;
                    case 1:
                        eIs[0] = vIndx[1];
                        eIs[1] = vIndx[2];
                        break;
                    case 2:
                        eIs[0] = vIndx[2];
                        eIs[1] = vIndx[3];
                        break;
                    case 3:
                        eIs[0] = vIndx[3];
                        eIs[1] = vIndx[0];
                        break;
                    case 4:
                        eIs[0] = vIndx[4];
                        eIs[1] = vIndx[5];
                        break;
                    case 5:
                        eIs[0] = vIndx[5];
                        eIs[1] = vIndx[6];
                        break;
                    case 6:
                        eIs[0] = vIndx[6];
                        eIs[1] = vIndx[7];
                        break;
                    case 7:
                        eIs[0] = vIndx[7];
                        eIs[1] = vIndx[4];
                        break;
                    case 8:
                        eIs[0] = vIndx[0];
                        eIs[1] = vIndx[4];
                        break;
                    case 9:
                        eIs[0] = vIndx[1];
                        eIs[1] = vIndx[5];
                        break;
                    case 10:
                        eIs[0] = vIndx[2];
                        eIs[1] = vIndx[6];
                        break;
                    case 11:
                        eIs[0] = vIndx[3];
                        eIs[1] = vIndx[7];

                        break;
                    default:
                        eIs[0] = 0;
                        eIs[1] = 0;
                    }
                    int eIs0m3 = eIs[1] * 3;
                    int eIs1m3 = eIs[1] * 3;
                    g0[0] = _vol->getGridX(eIs0m3);
                    g0[1] = _vol->getGridY(eIs0m3);
                    g0[2] = _vol->getGridZ(eIs0m3);
                    g1[0] = _vol->getGridX(eIs1m3);
                    g1[1] = _vol->getGridY(eIs1m3);
                    g1[2] = _vol->getGridZ(eIs1m3);
                    std::shared_ptr<Vertex> origin = interpolate(g0, g1, _vol->getData(eIs[0]), _vol->getData(eIs[1]), isoValue);
                    pedge->setOrigin(origin);
                }
            }
        }
    }


    // Set Null edges for the boundary cases
    for (auto f = _faceEdges.begin(); f != _faceEdges.end(); f++) {
        if ((*f)->getTwin() == 0) {
            std::shared_ptr<HalfEdge> startE = (*f)->getNext();
            std::shared_ptr<HalfEdge> nullE = std::make_shared<HalfEdge>(0);
            (*f)->setTwin(nullE);
            nullE->setTwin(*f);
            nullE->setOrigin(startE->getOrigin());
            nullE->_boundary = true;
            assignNullEdge(startE, nullE);
            startE = (*f)->getPrevious()->getTwin();
            std::shared_ptr<HalfEdge> itrE = startE;
            while (true) {
                if (itrE->getId() == 0) {
                    itrE->setPrevious(nullE);
                    break;
                }
                itrE = itrE->getPrevious()->getTwin();

            }
        }
    }
    _edgeMap.clear();
    _faceEdges.resize(_faceEdges.size());
}



void Surface::calculateIndexes(unsigned int vIndx[8], int x, int y, int z, int dimY, int dimZ) {
    // Calculate the global indexes for the 8 corners of the given cube. 
    vIndx[0] = z + dimZ * (y + (dimY * x));
    vIndx[1] = z + dimZ * (y + (dimY * (x + 1)));
    vIndx[2] = z + dimZ * ((y + 1) + (dimY * (x + 1)));
    vIndx[3] = z + dimZ * ((y + 1) + (dimY * x));
    vIndx[4] = (z + 1) + dimZ * (y + (dimY * x));
    vIndx[5] = (z + 1) + dimZ * (y + (dimY * (x + 1)));
    vIndx[6] = (z + 1) + dimZ * ((y + 1) + (dimY * (x + 1)));
    vIndx[7] = (z + 1) + dimZ * ((y + 1) + (dimY * x));

}

unsigned int Surface::getEdgeId(int i, unsigned int vIndx[8]) {
    // Create a unique Id for the given edge knowing that there are 3 unique edges per 
    // single vertex in the point cloud. 
    switch (i) {
    case 0:
        return (3 * vIndx[0]);
    case 1:
        return (3 * vIndx[1] + 2);
    case 2:
        return (3 * vIndx[3]);
    case 3:
        return (3 * vIndx[0] + 2);
    case 4:
        return (3 * vIndx[4]);
    case 5:
        return (3 * vIndx[5] + 2);
    case 6:
        return (3 * vIndx[7]);
    case 7:
        return (3 * vIndx[4] + 2);
    case 8:
        return (3 * vIndx[0] + 1);
    case 9:
        return (3 * vIndx[1] + 1);
    case 10:
        return (3 * vIndx[2] + 1);
    case 11:
        return (3 * vIndx[3] + 1);
    default:
        // throw an error??
        return (3 * vIndx[0]);
    }
}

std::shared_ptr<Vertex> Surface::interpolate(const double g0[3], const double g1[3], const double& d0, const double& d1, const double& isoVal) {
    // Interpolate between two given grid points given a specified isovalue.  

    double lenVal = std::abs(d0 - d1);
    double intr = (std::abs(isoVal - d0) / lenVal);
    std::shared_ptr<Vertex> edgeVec = std::make_shared<Vertex>((g1[0] - g0[0]), (g1[1] - g0[1]), (g1[2] - g0[2]));
    (*edgeVec) *= intr;
    (*edgeVec) += Vertex(g0[0], g0[1], g0[2]);

    return edgeVec;
}

void Surface::laplacianSmoothing() {
    // Runs a laplacian smoothing algorithm on the generated isosurface. 

    // Timer timer("Laplacian function");
    smooth(true);
}

void Surface::smooth(bool lap) {
    // for (auto edge : faceEdges) {
#pragma omp parallel for
    for (int i = 0; i < _faceEdges.size(); i++) {
        auto edge = _faceEdges[i];
        edge->smooth(lap);
        edge->getNext()->smooth(lap);
        edge->getPrevious()->smooth(lap);
    }
    // for (auto edge : faceEdges) {
#pragma omp parallel for
    for (int i = 0; i < _faceEdges.size(); i++) {
        auto edge = _faceEdges[i];
        if (edge->getOrigin()->isVisited()) {
            edge->getOrigin()->visit(false);
            edge->getOrigin()->update();
        }
        if (edge->getNext()->getOrigin()->isVisited()) {
            edge->getNext()->getOrigin()->visit(false);
            edge->getNext()->getOrigin()->update();
        }
        if (edge->getPrevious()->getOrigin()->isVisited()) {
            edge->getPrevious()->getOrigin()->visit(false);
            edge->getPrevious()->getOrigin()->update();
        }
    }
}

void Surface::assignNullEdge(std::shared_ptr<HalfEdge> startE, std::shared_ptr<HalfEdge> nextNull) {
    std::shared_ptr<HalfEdge> itrE = startE;
    static int count = 0;
    count++;
    do {
        if (itrE->getTwin() == 0) {
            std::shared_ptr<HalfEdge> nullE = std::make_shared<HalfEdge>(0);
            nullE->_boundary = true;
            itrE->setTwin(nullE);
            nullE->setTwin(itrE);
            nextNull->setPrevious(nullE);
            nullE->setOrigin(itrE->getNext()->getOrigin());
            assignNullEdge(itrE->getNext(), nullE);
        }
        itrE = itrE->getTwin()->getNext();
        if (itrE == 0) {
            return;
        }
    } while (itrE != startE);

}

void Surface::calculateVertexNormals() {
    // Calculate the normal for each face in the mesh 
    // Timer timer("Normal Calc");
    // for (std::shared_ptr<HalfEdge> faceEdge : faceEdges) {
#pragma omp parallel for 
    for (auto i = 0; i < _faceEdges.size(); i++) {
        auto faceEdge = _faceEdges[i];
        faceEdge->getFace()->calculateNormal();
    }

    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        if (!edge->getOrigin()->isVisited()) {
            edge->getOrigin()->visit(true);

            double nX = edge->getFace()->getNormalX();
            double nY = edge->getFace()->getNormalY();
            double nZ = edge->getFace()->getNormalZ();
            int count = 1;
            std::shared_ptr<HalfEdge> curEdge = edge->getPrevious()->getTwin();
            while (curEdge != edge) {
                if (!curEdge->_boundary) {
                    nX += curEdge->getFace()->getNormalX();
                    nY += curEdge->getFace()->getNormalY();
                    nZ += curEdge->getFace()->getNormalZ();
                    count++;
                }
                curEdge = curEdge->getPrevious()->getTwin();
            }
            edge->getOrigin()->setNormal((nX / count), (nY / count), (nZ / count));
        }

        // edge->Next()
        if (!edge->getNext()->getOrigin()->isVisited()) {
            edge->getNext()->getOrigin()->visit(true);

            double nX = edge->getFace()->getNormalX(); // equivalent to getNext()->getFace as they are part of the same face
            double nY = edge->getFace()->getNormalY();
            double nZ = edge->getFace()->getNormalZ();
            int count = 1;
            //std::shared_ptr<HalfEdge> curEdge = edge->getNext()->getPrevious()->getTwin();
            std::shared_ptr<HalfEdge> curEdge = edge->getTwin();
            while (curEdge != edge->getNext()) {
                if (!curEdge->_boundary) {
                    nX += curEdge->getFace()->getNormalX();
                    nY += curEdge->getFace()->getNormalY();
                    nZ += curEdge->getFace()->getNormalZ();
                    count++;
                }
                curEdge = curEdge->getPrevious()->getTwin();
            }
            edge->getNext()->getOrigin()->setNormal((nX / count), (nY / count), (nZ / count));
        }

        // edge->Previous()
        if (!edge->getPrevious()->getOrigin()->isVisited()) {
            edge->getPrevious()->getOrigin()->visit(true);

            double nX = edge->getFace()->getNormalX();
            double nY = edge->getFace()->getNormalY();
            double nZ = edge->getFace()->getNormalZ();
            int count = 1;
            std::shared_ptr<HalfEdge> curEdge = edge->getNext()->getTwin(); // equiv to getP->getP->getT
            while (curEdge != edge->getPrevious()) {
                if (!curEdge->_boundary) {
                    nX += curEdge->getFace()->getNormalX();
                    nY += curEdge->getFace()->getNormalY();
                    nZ += curEdge->getFace()->getNormalZ();
                    count++;
                }
                curEdge = curEdge->getPrevious()->getTwin();
            }
            edge->getPrevious()->getOrigin()->setNormal((nX / count), (nY / count), (nZ / count));
        }
    }

    // Reset the vertex visited status
    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        edge->visit(false);
        edge->getNext()->visit(false);
        edge->getPrevious()->visit(false);
    }
}


void Surface::subdivide() {
    // First update all points 
    // laplacianSmoothing();
    smooth(false);

    // Now subdivide all edges
    // Timer timer("Subdivision");
    std::vector<std::shared_ptr<Face>> newFaces;
    newFaces.reserve(_faceEdges.size() * 4);

    // Calculate the new vertex positions and store in each edge's _midPoint attribute
    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        if (!edge->isVisited()) {
            subdivideEdge(edge);
        }
        if (!edge->getNext()->isVisited()) {
            subdivideEdge(edge->getNext());
        }
        if (!edge->getPrevious()->isVisited()) {
            subdivideEdge(edge->getPrevious());
        }
    }
    //Reset the edges visited status
    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        edge->visit(false);
        edge->getNext()->visit(false);
        edge->getPrevious()->visit(false);
    }
    // Create the new edges
    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        // New Face 1 
        std::shared_ptr<Face> f1 = std::make_shared<Face>(edge);
        edge->setFace(f1);
        std::shared_ptr<HalfEdge> f1e1 = std::make_shared<HalfEdge>(edge->getId());
        f1e1->setFace(f1);
        std::shared_ptr<HalfEdge> f1e2 = std::make_shared<HalfEdge>(edge->getPrevious()->getId());
        f1e2->setFace(f1);
        std::shared_ptr<HalfEdge> f4e1 = std::make_shared<HalfEdge>(edge->getPrevious()->getId());

        f1e1->setOrigin(edge->getMidpoint());
        f1e2->setOrigin(edge->getPrevious()->getMidpoint());
        f4e1->setOrigin(edge->getPrevious()->getMidpoint());


        f1e1->setTwin(f4e1);
        f4e1->setTwin(f1e1);

        // New Face 2
        std::shared_ptr<Face> f2 = std::make_shared<Face>(edge->getNext());
        edge->getNext()->setFace(f2);
        std::shared_ptr<HalfEdge> f2e1 = std::make_shared<HalfEdge>(edge->getNext()->getId());
        f2e1->setFace(f2);
        std::shared_ptr<HalfEdge> f2e2 = std::make_shared<HalfEdge>(edge->getId());
        f2e2->setFace(f2);
        std::shared_ptr<HalfEdge> f4e2 = std::make_shared<HalfEdge>(edge->getId());

        f2e1->setOrigin(edge->getNext()->getMidpoint());
        f2e2->setOrigin(edge->getMidpoint());
        f4e2->setOrigin(edge->getMidpoint());

        f2e1->setTwin(f4e2);
        f4e2->setTwin(f2e1);


        // New Face 3 
        std::shared_ptr<Face> f3 = std::make_shared<Face>(edge->getPrevious());
        edge->getPrevious()->setFace(f3);
        std::shared_ptr<HalfEdge> f3e1 = std::make_shared<HalfEdge>(edge->getPrevious()->getId());
        f3e1->setFace(f3);
        std::shared_ptr<HalfEdge> f3e2 = std::make_shared<HalfEdge>(edge->getNext()->getId());
        f3e2->setFace(f3);
        std::shared_ptr<HalfEdge> f4e3 = std::make_shared<HalfEdge>(edge->getNext()->getId());

        f3e1->setOrigin(edge->getPrevious()->getMidpoint());
        f3e2->setOrigin(edge->getNext()->getMidpoint());
        f4e3->setOrigin(edge->getNext()->getMidpoint());

        f3e1->setTwin(f4e3);
        f4e3->setTwin(f3e1);

        // Twin outer edges
        if (edge->getPrevious()->getTwin()->_boundary) {
            std::shared_ptr<HalfEdge> be = std::make_shared<HalfEdge>(0);
            be->setOrigin(edge->getPrevious()->getTwin()->getMidpoint());
            be->setNext(edge->getPrevious()->getTwin()->getNext());
            be->setPrevious(edge->getPrevious()->getTwin());
            be->_boundary = true;

            f1e2->setTwin(edge->getPrevious()->getTwin());
            edge->getPrevious()->getTwin()->setTwin(f1e2);

            edge->getPrevious()->setTwin(be);
            be->setTwin(edge->getPrevious());
        }
        else {
            std::shared_ptr<HalfEdge> twin;
            f1e2->setTwin(edge->getPrevious()->getTwin());
            f1e2->visit(true);
        }

        if (edge->getTwin()->_boundary) {
            std::shared_ptr<HalfEdge> be = std::make_shared<HalfEdge>(0);
            be->setOrigin(edge->getTwin()->getMidpoint());
            be->setNext(edge->getTwin()->getNext());
            be->setPrevious(edge->getTwin());
            be->_boundary = true;

            f2e2->setTwin(edge->getTwin());
            edge->getTwin()->setTwin(f2e2);

            edge->setTwin(be);
            be->setTwin(edge);
        }
        else {
            f2e2->setTwin(edge->getTwin());
            f2e2->visit(true);
        }

        if (edge->getNext()->getTwin()->_boundary) {
            std::shared_ptr<HalfEdge> be = std::make_shared<HalfEdge>(0);
            be->setOrigin(edge->getNext()->getTwin()->getMidpoint());
            be->setNext(edge->getNext()->getTwin()->getNext());
            be->setPrevious(edge->getNext()->getTwin());
            be->_boundary = true;

            f3e2->setTwin(edge->getNext()->getTwin());
            edge->getNext()->getTwin()->setTwin(f3e2);

            edge->getNext()->setTwin(be);
            be->setTwin(edge->getNext());
        }
        else {
            f3e2->setTwin(edge->getNext()->getTwin());
            f3e2->visit(true);
        }

        // New Face 4 (Internal face)
        std::shared_ptr<Face> f4 = std::make_shared<Face>(f4e1);
        f4e1->setFace(f4);
        f4e2->setFace(f4);
        f4e3->setFace(f4);

        f4e1->setNext(f4e2);
        f4e2->setNext(f4e3);
        f4e3->setNext(f4e1);

        // connect remaining faces in reverse order to preserve edge->get...
        edge->getPrevious()->setNext(f3e1);
        f3e1->setNext(f3e2);
        f3e2->setNext(edge->getPrevious());

        edge->getNext()->setNext(f2e1);
        f2e1->setNext(f2e2);
        f2e2->setNext(edge->getNext());


        edge->setNext(f1e1);
        f1e1->setNext(f1e2);
        f1e2->setNext(edge);

        // add new faces to newFaces; 
        newFaces.push_back(f1);
        newFaces.push_back(f2);
        newFaces.push_back(f3);
        newFaces.push_back(f4);

    }
    for (auto face : newFaces) {
        auto edge = face->getEdge();
        if (edge->getPrevious()->isVisited()) {
            edge->getPrevious()->getTwin()->setTwin(edge->getPrevious());
            edge->getPrevious()->visit(false);
        }

    }
    _faceEdges.clear();
    _faceEdges.reserve(newFaces.size());
    for (auto face : newFaces) {
        _faceEdges.push_back(face->getEdge());
    }
    newFaces.clear();
    //Reset the edges visited status
    for (std::shared_ptr<HalfEdge> edge : _faceEdges) {
        edge->visit(false);
        edge->getNext()->visit(false);
        edge->getPrevious()->visit(false);
    }
}

void Surface::subdivideEdge(std::shared_ptr<HalfEdge> edge) {
    // std::cout << edge->getId() << "-" << edge->getNext()->getId() << "  ";
    std::shared_ptr<Vertex> newVert;
    if (edge->_boundary == true) {
        newVert = newBoundaryVertex(edge);
    }
    else if (edge->getTwin()->_boundary == true) {
        newVert = newBoundaryVertex(edge);
    }
    else {
        newVert = newInternalVertex(edge);
    }
    edge->setMidPoint(newVert);
    edge->visit(true);
    edge->getTwin()->setMidPoint(newVert);
    edge->getTwin()->visit(true);
}

std::shared_ptr<Vertex> Surface::newBoundaryVertex(std::shared_ptr<HalfEdge> edge) {
    std::shared_ptr<Vertex> newVert = std::make_shared<Vertex>(0.0, 0.0, 0.0);
    (*newVert) += *(edge->getOrigin());
    (*newVert) += *(edge->getNext()->getOrigin());
    (*newVert) *= 0.5;
    return newVert;
}

std::shared_ptr<Vertex> Surface::newInternalVertex(std::shared_ptr<HalfEdge> edge) {
    std::shared_ptr<Vertex> newVert = std::make_shared<Vertex>(0.0, 0.0, 0.0);
    Vertex v18 = *(edge->getPrevious()->getOrigin()) + *(edge->getTwin()->getPrevious()->getOrigin());
    // v18.scalarDivide(8.0);
    Vertex v38 = *(edge->getOrigin()) + *(edge->getNext()->getOrigin());
    v38 *= 3.0;
    (*newVert) += (v18 + v38);
    (*newVert) /= 8.0;
    return newVert;
}

const int Surface::nFaces() const {
    return _faceEdges.size();
}

void Surface::generateOpenGLMesh(float* glMesh) {
#pragma omp parallel for
    for (auto i = 0; i < _faceEdges.size(); i++) {
        int fIndx = i * 3 * 3 * 3;
        float col[3] = { 0.0f, 0.0f, 0.0f };
        unsigned int cI = 0;

        // Set vertex 1
        glMesh[fIndx + 0] = static_cast<float>(_faceEdges[i]->getOriginX());
        glMesh[fIndx + 1] = static_cast<float>(_faceEdges[i]->getOriginY());
        glMesh[fIndx + 2] = static_cast<float>(_faceEdges[i]->getOriginZ());
        if (_vol->hasColourData()) {
            unsigned int cI = _faceEdges[i]->getId() / 3;
            generateRGBColour(col, _vol->getColourHue(cI));
        }       
        glMesh[fIndx + 3] = col[0];
        glMesh[fIndx + 4] = col[1];
        glMesh[fIndx + 5] = col[2];
        glMesh[fIndx + 6] = static_cast<float>(_faceEdges[i]->getOrigin()->getNormal()[0]);
        glMesh[fIndx + 7] = static_cast<float>(_faceEdges[i]->getOrigin()->getNormal()[1]);
        glMesh[fIndx + 8] = static_cast<float>(_faceEdges[i]->getOrigin()->getNormal()[2]);

        // Set vertex 2
        glMesh[fIndx + 9] = static_cast<float>(_faceEdges[i]->getNext()->getOriginX());
        glMesh[fIndx + 10] = static_cast<float>(_faceEdges[i]->getNext()->getOriginY());
        glMesh[fIndx + 11] = static_cast<float>(_faceEdges[i]->getNext()->getOriginZ());
        if (_vol->hasColourData()){
            cI = _faceEdges[i]->getNext()->getId() / 3;
            generateRGBColour(col, _vol->getColourHue(cI));
        }
        glMesh[fIndx + 12] = col[0];
        glMesh[fIndx + 13] = col[1];
        glMesh[fIndx + 14] = col[2];
        glMesh[fIndx + 15] = static_cast<float>(_faceEdges[i]->getNext()->getOrigin()->getNormal()[0]);
        glMesh[fIndx + 16] = static_cast<float>(_faceEdges[i]->getNext()->getOrigin()->getNormal()[1]);
        glMesh[fIndx + 17] = static_cast<float>(_faceEdges[i]->getNext()->getOrigin()->getNormal()[2]);

        // Set vertex 3
        glMesh[fIndx + 18] = static_cast<float>(_faceEdges[i]->getPrevious()->getOriginX());
        glMesh[fIndx + 19] = static_cast<float>(_faceEdges[i]->getPrevious()->getOriginY());
        glMesh[fIndx + 20] = static_cast<float>(_faceEdges[i]->getPrevious()->getOriginZ());
        if (_vol->hasColourData()) {
            cI = _faceEdges[i]->getPrevious()->getId() / 3;
            generateRGBColour(col, _vol->getColourHue(cI));
        }
        glMesh[fIndx + 21] = col[0];
        glMesh[fIndx + 22] = col[1];
        glMesh[fIndx + 23] = col[2];
        glMesh[fIndx + 24] = static_cast<float>(_faceEdges[i]->getPrevious()->getOrigin()->getNormal()[0]);
        glMesh[fIndx + 25] = static_cast<float>(_faceEdges[i]->getPrevious()->getOrigin()->getNormal()[1]);
        glMesh[fIndx + 26] = static_cast<float>(_faceEdges[i]->getPrevious()->getOrigin()->getNormal()[2]);

    }
}