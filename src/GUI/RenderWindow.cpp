#include "GUI/RenderWindow.h" 
#include "GUI/Interactor.h"

#include <vtkCamera.h>
#include <vtkAxesActor.h>
#include <vtkLine.h>

using namespace ctkGraphics;

RenderWindow::RenderWindow() {
	setBackground(0.0, 0.0, 0.0);
	_rw->AddRenderer(_ren);
	_rw->SetSize(640, 480);
	_ren->AddActor(_atomSphere.actor);
	_ren->AddActor(_bondTube.actor);
	//_iren = _rw->GetInteractor();
	_iren->SetRenderWindow(_rw);

	createAxisArrows();
	setDefaultCamera();

	vtkNew<Interactor> style;
	_iren->SetInteractorStyle(style);

	setActorProperties(_atomSphere.actor);
	setActorProperties(_bondTube.actor);
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
	drawBonds();

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

inline void RenderWindow::setWinId(const char* id) const {
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
	_atomSphere.data.colours->SetNumberOfTuples(_model->nAtoms());
	_atomSphere.data.radii->SetNumberOfTuples(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		// Position
		_atomSphere.data.points->SetPoint(
			i,
			_model->getAtom(i)->getPosition()[0],
			_model->getAtom(i)->getPosition()[1],
			_model->getAtom(i)->getPosition()[2]
		);
		// Colour
		float c[3] = {
			_model->getAtom(i)->getColour()[0] * 255,
			_model->getAtom(i)->getColour()[1] * 255,
			_model->getAtom(i)->getColour()[2] * 255
		};
		_atomSphere.data.colours->SetTuple(i, c);
		// Size 
		float r[3];
		if (_wireframe) {
			r[0] = 0.1165f;
			r[1] = 0.1165f;
			r[2] = 0.1165f;
		}
		else {
			r[0] = _model->getAtom(i)->getCovalentRadii();
			r[1] = _model->getAtom(i)->getCovalentRadii();
			r[2] = _model->getAtom(i)->getCovalentRadii();
		}
		_atomSphere.data.radii->SetTuple(i, r);
	}

	_atomSphere.glyph->Update();
	//_atomSphere.glyph->SetScaleFactor(1.0);
}

// TODO -> use atom ids to improve efficiency ???
void RenderWindow::drawBonds() {

	_bondTube.lines->Reset();
	_bondTube.colours->Reset();

	if (_drawBonds) {
		if (_wireframe) {
			_bondTube.setRadius(0.2f);
		}

		_bondTube.colours->SetNumberOfComponents(3);
		_bondTube.colours->SetNumberOfTuples(_model->nBonds() * 2);
		_bondTube.points->SetNumberOfPoints(_model->nBonds() * 3);
		int pointId = 0;
		int bondId = 0;
		for (int i = 0; i < _model->nAtoms(); i++) {
			for (int j = (i + 1); j < _model->nAtoms(); j++) {
				if (_model->connected(i, j)) {
					
					// Get the bond midpoint 
					ctkMaths::Vector3 mp = _model->getAtom(i)->getPosition() - _model->getAtom(j)->getPosition();
					mp /= 2;
					mp += _model->getAtom(j)->getPosition();

					// Create the first line 
					vtkNew<vtkLine> linei;
					_bondTube.points->SetPoint(pointId, _model->getAtom(i)->getPosition()[0], _model->getAtom(i)->getPosition()[1], _model->getAtom(i)->getPosition()[2]);
					linei->GetPointIds()->SetId(0, pointId);
					pointId++;
					_bondTube.points->SetPoint(pointId, mp[0], mp[1], mp[2]);
					linei->GetPointIds()->SetId(1, pointId);
					//pointId++;
					_bondTube.lines->InsertNextCell(linei);
					float c[3] = {
						_model->getAtom(i)->getColour()[0] * 255,
						_model->getAtom(i)->getColour()[1] * 255,
						_model->getAtom(i)->getColour()[2] * 255
					};
					_bondTube.colours->SetTuple(bondId, c);
					bondId++;

					// Create the second line 
					vtkNew<vtkLine> linej;
					//_bondTube.points->SetPoint(pointId, mp[0], mp[1], mp[2]);
					linej->GetPointIds()->SetId(0, pointId);
					pointId++;
					_bondTube.points->SetPoint(pointId, _model->getAtom(j)->getPosition()[0], _model->getAtom(j)->getPosition()[1], _model->getAtom(j)->getPosition()[2]);
					linej->GetPointIds()->SetId(1, pointId);
					pointId++;
					_bondTube.lines->InsertNextCell(linej);
					c[0] = _model->getAtom(j)->getColour()[0] * 255;
					c[1] = _model->getAtom(j)->getColour()[1] * 255;
					c[2] = _model->getAtom(j)->getColour()[2] * 255;
					_bondTube.colours->SetTuple(bondId, c);
					bondId++;

				}
			}
		}
	}
	else {
		_bondTube.points->Reset();
	}
	_bondTube.mapper->Update();
}

inline void RenderWindow::finalise() {
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

inline void RenderWindow::showAxes(const bool show) const {
	_axes->SetEnabled(show);
}

void RenderWindow::createLighting() const {

	//! Front light 
	_lights[0]->SetLightType(2);
	_lights[0]->SetPosition(0.0, 0.0, 1.0);
	_lights[0]->SetIntensity(1);
	_lights[0]->SetColor(1.0, 1.0, 1.0);
	_ren->AddLight(_lights[0]);

	//! top light 
	_lights[1]->SetLightType(2);
	_lights[1]->SetPosition(0.2, 1.0, 0.0);
	_lights[1]->SetIntensity(1);
	_lights[1]->SetColor(1.0, 1.0, 1.0);
	_ren->AddLight(_lights[1]);
}

void RenderWindow::lightSwitch(const unsigned int l, const bool on) const {
	if (l <= 1) {
		_lights[l]->SetIntensity(on);
	}
}

inline void RenderWindow::setBondColour(const double r, const double g, const double b) {
	_bondTube.actor->GetProperty()->SetColor(r, g, b);
}

inline void RenderWindow::setBondRadius(const float r) {
	_bondTube.setRadius(r);
}