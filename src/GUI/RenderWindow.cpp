#include "GUI/RenderWindow.h" 
#include "vtkFloatArray.h"
#include "vtkPointData.h"

using namespace ctkGraphics;

RenderWindow::RenderWindow() {
	_ren->SetBackground(0.0, 0.0, 0.0);
	_rw->AddRenderer(_ren);
	_rw->SetSize(640, 480);
	_ren->AddActor(_atomSphere.actor);
	_iren->SetRenderWindow(_rw);
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

	vtkNew<vtkPoints> points;
	points->SetNumberOfPoints(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		points->SetPoint(
			i,
			_model->getAtom(i)->getPosition()[0],
			_model->getAtom(i)->getPosition()[1],
			_model->getAtom(i)->getPosition()[2]
		);
	}
	_atomSphere.data->SetPoints(points);

	vtkNew<vtkUnsignedCharArray> colours; 
	colours->SetNumberOfComponents(3);
	colours->SetNumberOfTuples(_model->nAtoms());
	colours->SetName("Colours");
	for (int i = 0; i < _model->nAtoms(); i++) {
		double c[3] = { 255, 0, 0 };
		colours->SetTuple(i, c);
	}
	_atomSphere.data->GetPointData()->SetScalars(colours);

	vtkNew<vtkFloatArray> radii;
	radii->SetNumberOfComponents(3);
	radii->SetNumberOfTuples(_model->nAtoms());
	for (int i = 0; i < _model->nAtoms(); i++) {
		float r[3] = {_model->getAtom(i)->getCovalentRadii(), _model->getAtom(i)->getCovalentRadii(), _model->getAtom(i)->getCovalentRadii() };
		radii->SetTuple(i, r);
	}
	_atomSphere.data->GetPointData()->SetVectors(radii);


	_atomSphere.glyph->Update();
	//_atomSphere.glyph->SetScaleFactor(1.0);
}

void RenderWindow::render() {
	_rw->Render();
	_rw->SetWindowName("Test");
	_iren->Initialize();
	_iren->Start();
}