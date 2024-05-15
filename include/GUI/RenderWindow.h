#pragma once 
#include "GUI/api.h"

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkLight.h>


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

		//! Turns on/off a given light 
		void lightSwitch(const unsigned int l, const bool on) const;

		//! Sets the bond colour for when rendering bonds as single colour tubes 
		void setBondColour(const double r, const double g, const double b);

		//! Sets the radius of the tubes used to render bonds 
		void setBondRadius(const float r);

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

		// Rendering control flags 
		bool _drawBonds = true;
		bool _wireframe = false;

		void drawAtoms();
		void drawBonds();

		//! Create the viewer's axis arrows 
		void createAxisArrows() const;
		//! Setup the viewer's lighting 
		void createLighting() const;
		
		vtkNew<vtkLight> _lights[2];

		//! Default actor properties \todo -> make these editable 
		double _ambient = 0.2;
		double _diffuse = 1.0;
		double _specular = 0.5;
		double _spow = 16.0;

		void setActorProperties(vtkActor* actor) const {
			actor->GetProperty()->SetAmbient(_ambient);
			actor->GetProperty()->SetDiffuse(_diffuse);
			actor->GetProperty()->SetSpecular(_specular);
			actor->GetProperty()->SetSpecularPower(_spow);
			actor->GetProperty()->SetInterpolationToPhong();
		}
	};
}