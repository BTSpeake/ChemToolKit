#pragma once 
#include "GUI/api.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>


#include "Data/Model.h"
#include "GUI/utils.h"

namespace ctkGraphics {

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

		// Event handling for external api like Qt (doesn't need to know about vtk) 


		// VTK cleanup 
		void finalise();

		void render();
		void resize(const int w, const int h, const int dpi);

	private:
		vtkNew<vtkRenderWindow> _rw;
		vtkNew<vtkRenderer> _ren;
		vtkNew<vtkRenderWindowInteractor> _iren;
		const ctkData::Model* _model = 0;
		utils::AtomSphere _atomSphere;

		void drawAtoms();
		
	};
}