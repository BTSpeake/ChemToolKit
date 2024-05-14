#pragma once 
#include "GUI/api.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkOrientationMarkerWidget.h>


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

		//! Sets the background colour for the render window 
		void setBackground(const double r, const double g, const double b);

		//! Normalise the camera 
		void normaliseCamera() const;

		//! Setup the default camera orientation and position 
		void setDefaultCamera() const;

		//! Controls whether the axis arrows are visible in the render window 
		void showAxes(const bool show) const;

		//! Set window id
		void setWinId(const char* id) const;

		//void timerEvent() const;
		void setEventInformation(int x, int y, int ctrl = 0, int shift = 0, char keycode = 0, int repeatcount = 0, const char* keysym = nullptr);
		void enterEvent();
		void leaveEvent();
		void buttonPressEvent(const int opt) const;
		void buttonReleaseEvent(const int opt) const;
		void mouseMoveEvent() const;
		void wheelEvent(const bool forward) const;

		// Event handling for external api like Qt (doesn't need to know about vtk) 


		// VTK cleanup 
		void finalise();

		void render();
		void resize(const int w, const int h, const int dpi);

	private:
		vtkNew<vtkRenderWindow> _rw;
		vtkNew<vtkRenderer> _ren;
		vtkNew<vtkGenericRenderWindowInteractor> _iren;
		vtkNew<vtkOrientationMarkerWidget> _axes;
		const ctkData::Model* _model = 0;
		utils::AtomSphere _atomSphere;
		utils::BondTube _bondTube;

		double bgCol[3];

		void drawAtoms();

		//! Create the viewer's axis arrows 
		void createAxisArrows() const;
		
	};
}