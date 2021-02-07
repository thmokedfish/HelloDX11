#include "pch.h"
#include "Skybox.h"
using namespace HelloDX11;

void Skybox::SetFollow(Camera* cam)
{
	camera = cam;
}

Geometry::MeshData<geoVPC> Skybox::CreateMesh()
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
	return mesh;
}

void Skybox::OnUpdate()
{
	m_position = camera->getPosition();
}
void Skybox::CreateState()
{
	D3D11_DEPTH_STENCIL_DESC depthDesc;
	depthDesc.DepthEnable = true;
	depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;


	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	device->CreateDepthStencilState(&depthDesc, m_depthStencilState.GetAddressOf());


	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise =false;
	rasterizerDesc.DepthClipEnable = true;

	device->CreateRasterizerState(&rasterizerDesc, m_rasterizerState.GetAddressOf());
}
void Skybox::SetState()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	context->RSSetState(m_rasterizerState.Get());
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
}