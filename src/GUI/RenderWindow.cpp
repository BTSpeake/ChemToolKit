#include "GUI/RenderWindow.h" 
#include "GUI/Interactor.h"

#include <vtkCamera.h>
#include <vtkAxesActor.h>

using namespace ctkGraphics;

RenderWindow::RenderWindow() {
	setBackground(0.0, 0.0, 0.0);
	_rw->AddRenderer(_ren);
	_rw->SetSize(640, 480);
	_ren->AddActor(_atomSphere.actor);
	//_iren = _rw->GetInteractor();
	_iren->SetRenderWindow(_rw);

	createAxisArrows();
	setDefaultCamera();

	vtkNew<Interactor> style;
	_iren->SetInteractorStyle(style);


	//_iren->ReInitialize();
	//render();
}

RenderWindow::~RenderWindow() {

}


inline void RenderWindow::setModel(const ctkData::Model& model) {
	_model = &model;
	updateRendering();
}

inline void RenderWindow::setModel(const ctkData::Model* model) {
	_model = model;
	updateRendering();
}

void RenderWindow::updateRendering() {

	drawAtoms();

}

void RenderWindow::setBackground(const double r, const double g, const double b) {
	bgCol[0] = r; 
	bgCol[1] = g; 
	bgCol[2] = b;
	_ren->SetBackground(bgCol);
}

void RenderWindow::normaliseCamera() const {
	_ren->ResetCamera();
}

//! \Todo Allow the change of the camera's up vector 
void RenderWindow::setDefaultCamera() const {
	_ren->GetActiveCamera()->SetViewUp(0.0, 1.0, 0.0);
	_ren->GetActiveCamera()->SetFocalPoint(0, 0, 0);
	_ren->GetActiveCamera()->SetPosition(0.0, 0.0, 50.0);
	//_ren->GetActiveCamera()->SetDistance(50);
	_ren->ResetCamera();
}

void RenderWindow::setWinId(const char* id) const {
	_rw->SetWindowInfo(id);
}

//void RenderWindow::timerEvent() const {
//	_iren->TimerEvent();
//}

void RenderWindow::setEventInformation(int x, int y, int ctrl, int shift, char keycode, int repeatcount, const char* keysum) {
	_iren->SetEventInformation(x, y, ctrl, shift, keycode, repeatcount, keysum);
}

void RenderWindow::enterEvent() {
	_iren->EnterEvent();
}
void RenderWindow::leaveEvent() {
	_iren->LeaveEvent();
}
void RenderWindow::buttonPressEvent(const int opt) const {
	switch (opt) {
	case 0:
		_iren->LeftButtonPressEvent();
		break;
	case 1:
		_iren->RightButtonPressEvent();
		break;
	case 2:
		_iren->MiddleButtonPressEvent();
	}
}
void RenderWindow::buttonReleaseEvent(const int opt) const {
	switch (opt) {
	case 0:
		_iren->LeftButtonReleaseEvent();
		break;
	case 1:
		_iren->RightButtonReleaseEvent();
		break;
	case 2:
		_iren->MiddleButtonReleaseEvent();
	}
}
void RenderWindow::mouseMoveEvent() const {
	_iren->MouseMoveEvent();
}
void RenderWindow::wheelEvent(const bool forward) const {
	if (forward) {
		_iren->MouseWheelForwardEvent();
	}
	else {
		_iren->MouseWheelBackwardEvent();
	}
}

void RenderWindow::drawAtoms() {

	_atomSphere.data.points->SetNumberOfPoints(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		_atomSphere.data.points->SetPoint(
			i,
			_model->getAtom(i)->getPosition()[0],
			_model->getAtom(i)->getPosition()[1],
			_model->getAtom(i)->getPosition()[2]
		);
	}

	_atomSphere.data.colours->SetNumberOfTuples(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		_atomSphere.data.colours->SetTuple(i, _model->getAtom(i)->getColour());
	}

	_atomSphere.data.radii->SetNumberOfTuples(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		float r[3] = {_model->getAtom(i)->getCovalentRadii(), _model->getAtom(i)->getCovalentRadii(), _model->getAtom(i)->getCovalentRadii() };
		_atomSphere.data.radii->SetTuple(i, r);
	}


	_atomSphere.glyph->Update();
	//_atomSphere.glyph->SetScaleFactor(1.0);
}

void RenderWindow::finalise() {
	_rw->Finalize();
}

void RenderWindow::render() {
	//_rw->Render();
	//_iren->Initialize();
	//_iren->Start();
	_iren->ReInitialize();
	_iren->Render();
}

void RenderWindow::resize(const int w, const int h, const int dpi) {
	_rw->SetDPI(dpi);
	_rw->SetSize(w, h);
	_iren->SetSize(w, h);
	_iren->ConfigureEvent();
}


void RenderWindow::createAxisArrows() const {
	vtkNew<vtkAxesActor> axes;
	axes->SetShaftTypeToCylinder();
	axes->SetXAxisLabelText("X");
	axes->SetYAxisLabelText("Y");
	axes->SetZAxisLabelText("Z");
	_axes->SetOrientationMarker(axes);
	_axes->SetViewport(0, 0, 0.3, 0.3);
	_axes->SetInteractor(_iren);
	_axes->SetEnabled(true);
	_axes->SetInteractive(true);
}

void RenderWindow::showAxes(const bool show) const {
	_axes->SetEnabled(show);
}