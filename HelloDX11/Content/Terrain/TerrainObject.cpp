#include "pch.h"
#include "TerrainObject.h"
#include "HeightmapSampling.h"
using namespace HelloDX11;
using namespace DirectX;
TerrainObject::TerrainObject() :RenderObject()
{

}
void TerrainObject::OnCreateResource()
{
	HeightmapSampling sampler;
	Geometry::MeshData<Geometry::VertexPosColor> mesh = sampler.LoadAndSample<Geometry::VertexPosColor>("/heightmap.tga");//PathConsts::AssetPath +"StoreLogo.scale-200.png");
	this->CreateResourceWithVertexData(mesh);
}

void TerrainObject::OnUpdate()
{

}