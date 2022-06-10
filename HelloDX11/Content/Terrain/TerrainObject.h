#pragma once
#include"RenderObject.h"
namespace HelloDX11
{
	class TerrainObject :public RenderObject
	{
	private:
		//Geometry::MeshData<geoVPC> GetMesh() override;
	protected:
		void OnCreateResource() override;
	public:
		TerrainObject();
		void OnUpdate() override;
	};
}