#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
	class Wheel : public RenderObject
	{
	protected:
		Geometry::MeshData<geoVPC> CreateMesh() override;
	public:
		void OnUpdate(DX::StepTimer const& timer) override;
		void Rotate(float radians);
	};
}

