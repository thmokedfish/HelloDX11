#include "pch.h"
#include "Wheel.h"
using namespace HelloDX11;
using namespace DirectX;
void Wheel::OnUpdate()
{
	//if input w
	//wheel rotate x
	//if input a/d
	//wheel rotate y
}

void Wheel::OnCreateResource()
{
	Geometry::MeshData<geoVPC> mesh= Geometry::CreateCylinder<geoVPC>(0.2f, 0.1f, 16, 3, 0, 0 );
	XMFLOAT4 color = { (1.0f), (0.5f), (0.5f), (1.0f) };
	for (int i = 0; i < mesh.vertexVec.size(); i += 3)
	{
		mesh.vertexVec[i].color = color;
	}
	CreateResourceWithVertexData(mesh);
}