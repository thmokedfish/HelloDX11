#include "pch.h"
#include "RenderObject.h"
#include <Common/DirectXHelper.h>
using namespace HelloDX11;
using namespace DirectX;
RenderObject::RenderObject():m_position(),m_rotation(XMMatrixIdentity())
{
	m_scale = XMVectorSet(1, 1, 1, 1);
}
const DX::StepTimer* RenderObject::m_timer ;
void RenderObject::Update()
{
	for (auto p : childs)
	{
		p->Update();
	}
	OnUpdate();
}

void RenderObject::Render(const XMMATRIX& parentModel)
{
	XMFLOAT3 scale; 
	XMStoreFloat3(&scale, m_scale);
	XMMATRIX model =XMMatrixScaling(scale.x,scale.y,scale.z)* m_rotation *XMMatrixTranslationFromVector(m_position)* parentModel;
	for (auto p : childs)
	{
		p->Render(model);
		
	}
	//����ת�ú��
	DirectX::XMStoreFloat4x4(&m_modelBufferData.model, XMMatrixTranspose(model));
	auto context = m_deviceResources->GetD3DDeviceContext();
	// ׼�������������Խ��䷢�͵�ͼ���豸��
	context->UpdateSubresource1(
		m_modelBuffer.Get(),
		0,
		NULL,
		&m_modelBufferData,
		0,
		0,
		0
	);
	// ÿ�����㶼�� VertexPositionColor �ṹ��һ��ʵ����
	UINT stride = sizeof(Geometry::VertexPosColor);
	UINT offset = 0;
	context->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
	);

	context->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT, // ÿ����������һ�� 16 λ�޷�������(short)��
		0
	);

	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//context->IASetInputLayout(m_inputLayout.Get());
	

	// ���������������͵�ͼ���豸��
	context->VSSetConstantBuffers1(
		1,
		1,
		m_modelBuffer.GetAddressOf(),
		nullptr,
		nullptr
	);

	// ���ƶ���
	context->DrawIndexed(
		m_indexCount,
		0,
		0
	);
}
void RenderObject::CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources)
{
	for (auto p : childs)
	{
		p->CreateResources(deviceResources);
	}
	m_deviceResources = deviceResources;
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&constantBufferDesc,
			nullptr,
			&m_modelBuffer
		)
	);
	m_mesh = CreateMesh();
	std::vector<geoVPC> v = m_mesh.vertexVec;
	int vsize = v.size();
	static geoVPC* vertices = new geoVPC[vsize];
	std::copy(v.begin(), v.end(), vertices);

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(geoVPC) * vsize, D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
		)
	);



	int indexSize = m_mesh.indexVec.size();
	//unsigned short a[10];
	static unsigned short* meshIndices = new unsigned short[indexSize];
	std::copy(m_mesh.indexVec.begin(), m_mesh.indexVec.end(), meshIndices);
	//m_indexCount = ARRAYSIZE(meshIndices);
	m_indexCount = m_mesh.indexVec.size();

	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = meshIndices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short) * m_indexCount, D3D11_BIND_INDEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&m_indexBuffer
		)
	);

}

DirectX::XMVECTOR RenderObject::getPosition() { return m_position; }
void RenderObject::setPosition(XMVECTOR pos) { m_position = pos; }
void RenderObject::setScale(DirectX::XMVECTOR scale) { m_scale = scale; }
void RenderObject::setRotation(XMMATRIX rotation) { m_rotation = rotation; }
void RenderObject::Rotate(XMMATRIX trans)
{
	m_rotation = m_rotation * trans;
}

DirectX::XMVECTOR RenderObject::Forward()
{

	XMVECTOR origin = XMVectorSet(0, 0, 1, 1);
	
	return XMVector4Transform(origin, m_rotation);
}
DirectX::XMVECTOR RenderObject::Right()
{

	XMVECTOR origin = XMVectorSet(1, 0,0 , 1);

	return XMVector4Transform(origin, m_rotation);
}
DirectX::XMVECTOR RenderObject::Up()
{

	XMVECTOR origin = XMVectorSet(0, 1, 0, 1);

	return XMVector4Transform(origin, m_rotation);
}
void RenderObject::ReleaseDeviceDependentResources()
{
	m_inputLayout.Reset();
	m_modelBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
}
void RenderObject::addChild(std::shared_ptr<RenderObject> child)
{
	childs.push_back(child);
}