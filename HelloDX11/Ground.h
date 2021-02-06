#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
    class Ground : public RenderObject
    {
	protected:
		Geometry::MeshData<geoVPC> CreateMesh() override;
	public:
		void OnUpdate() override;
    };
}

