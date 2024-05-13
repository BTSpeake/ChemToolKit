#pragma once 

#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkGlyph3D.h>
#include <vtkSphereSource.h>
#include <vtkTubeFilter.h>

namespace ctkGraphics::utils {

	struct RenderData {
		vtkNew<vtkPolyData> data;
		vtkNew<vtkPoints> points;
		vtkNew<vtkFloatArray> radii;
		vtkNew<vtkUnsignedCharArray> colours;

		RenderData() {
			data->SetPoints(points);
			colours->SetNumberOfComponents(3);
			colours->SetName("Colours");
			data->GetPointData()->SetScalars(colours);
			radii->SetNumberOfComponents(3);
			data->GetPointData()->SetVectors(radii);
		}
	};

	struct AtomSphere {
		vtkNew<vtkActor> actor;
		RenderData data;
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
			glyph->SetInputData(data.data);
			mapper->SetInputConnection(glyph->GetOutputPort());
			mapper->UseLookupTableScalarRangeOff();
			mapper->ScalarVisibilityOn();
			mapper->SetScalarModeToDefault();
			actor->SetMapper(mapper);
		}

	};

	struct BondTube {
		vtkNew<vtkTubeFilter> src;
		vtkNew<vtkPolyDataMapper> mapper;
		RenderData data;

		BondTube() {
			src->SetNumberOfSides(20);
			src->CappingOff();
			src->SetVaryRadius(0);
			src->SetRadiusFactor(10);
			src->SetInputData(data.data);
			mapper->SetInputConnection(src->GetOutputPort());
			setRadius();
		}
		void setRadius(const float r = 0.1) {
			src->SetRadius(r);
			mapper->Update();
		}
	};
}