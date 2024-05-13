#pragma once 
#include "GUI/api.h"

#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>



namespace ctkGraphics {
	class GRAPHICS_API Interactor : public vtkInteractorStyleTrackballCamera {
	public:
		static Interactor* New();
		vtkTypeMacro(Interactor, vtkInteractorStyleTrackballCamera);

		void OnRightButtonDown() override {
			vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
		}
		void OnRightButtonUp() override {
			vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
		}
		void OnMiddleButtonDown() override {
			vtkInteractorStyleTrackballCamera::OnRightButtonDown();
		}
		void OnMiddleButtonUp() override {
			vtkInteractorStyleTrackballCamera::OnRightButtonUp();
		}


	};
	vtkStandardNewMacro(Interactor);
}