#include "GUI/RenderWindow.h" 
#include "GUI/Interactor.h"

using namespace ctkGraphics;

RenderWindow::RenderWindow() {
	_ren->SetBackground(0.0, 0.0, 0.0);
	_rw->AddRenderer(_ren);
	_rw->SetSize(640, 480);
	_ren->AddActor(_atomSphere.actor);
	_iren->SetRenderWindow(_rw);

	vtkNew<Interactor> style;
	_iren->SetInteractorStyle(style);

	_iren->Initialize();
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

void RenderWindow::render() {
	_rw->Render();
	_rw->SetWindowName("Test");
	_iren->Initialize();
	_iren->Start();
}