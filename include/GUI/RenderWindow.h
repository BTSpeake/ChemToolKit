#pragma once 
#include "GUI/api.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkGlyph3D.h>
#include <vtkSphereSource.h>
#include <vtkRenderWindowInteractor.h>

#include "Data/Model.h"

namespace ctkGraphics {

	namespace utils {
		struct AtomSphere {
			vtkNew<vtkActor> actor;
			vtkNew<vtkPolyData> data;
			vtkNew<vtkPolyDataMapper> mapper;
			vtkNew<vtkGlyph3D> glyph;
			vtkNew<vtkSphereSource> src;
			
			AtomSphere() {
				src->SetCenter(0, 0, 0);
				src->SetRadius(1);
				src->SetThetaResolution(30);
				src->SetPhiResolution(30);
				glyph->SetSourceConnection(src->GetOutputPort());
				glyph->SetScaleModeToScaleByVector();
				glyph->SetColorModeToColorByScalar();
				glyph->GeneratePointIdsOn();
				glyph->SetInputData(data);
				mapper->SetInputConnection(glyph->GetOutputPort());
				mapper->UseLookupTableScalarRangeOff();
				mapper->ScalarVisibilityOn();
				mapper->SetScalarModeToDefault();
				actor->SetMapper(mapper);
			}

		};
	}

	class GRAPHICS_API RenderWindow {
	public:
		//! Default constructor 
		RenderWindow();
		//! Destructor 
		~RenderWindow();

		//! Sets the currently active model 
		void setModel(const ctkData::Model& model);
		void setModel(const ctkData::Model* model);

		//! Updates the vtk data based on the current model 
		void updateRendering();

		void render();

	private:
		vtkNew<vtkRenderWindow> _rw;
		vtkNew<vtkRenderer> _ren;
		vtkNew<vtkRenderWindowInteractor> _iren;
		const ctkData::Model* _model = 0;
		utils::AtomSphere _atomSphere;

		void drawAtoms();
		
	};
}