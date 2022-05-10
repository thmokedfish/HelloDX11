#include "pch.h"
#include "Skybox.h"
using namespace HelloDX11;

void Skybox::SetFollow(Camera* cam)
{
	camera = cam;
}

void Skybox::OnCreateResource()
{
	Geometry::MeshData<geoVPC> mesh = Geometry::CreateBox<geoVPC>(50, 50, 50, {1,1,1,1 });
	DirectX::XMFLOAT4 topColor = { 0.2f,0.2f,1,1 };
	mesh.vertexVec[1].color = topColor;
	mesh.vertexVec[2].color = topColor;
	mesh.vertexVec[5].color = topColor;
	mesh.vertexVec[6].color = topColor;
	mesh.vertexVec[8].color = topColor;
	mesh.vertexVec[9].color = topColor;
	mesh.vertexVec[10].color = topColor;
	mesh.vertexVec[11].color = topColor;
	mesh.vertexVec[17].color = topColor;
	mesh.vertexVec[18].color = topColor;
	mesh.vertexVec[21].color = topColor;
	mesh.vertexVec[22].color = topColor;
	CreateResourceWithVertexData(mesh);
}

void Skybox::OnUpdate()
{
	m_transform.setPosition(camera->getPosition());
}

std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> Skybox::getDepthDesc()
{
	std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> depthDesc = RenderObject::getDepthDesc(); 
	depthDesc->DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	return depthDesc;
}


std::shared_ptr< D3D11_RASTERIZER_DESC> Skybox::getRasterizerDesc()
{
	std::shared_ptr< D3D11_RASTERIZER_DESC> desc = RenderObject::getRasterizerDesc();
	desc->FrontCounterClockwise = false;
	return desc;
}
