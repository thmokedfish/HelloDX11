#include "pch.h"
#include "RenderObject.h"
using namespace HelloDX11;
using namespace DirectX;
RenderObject::RenderObject():m_transform(std::make_shared<Transform>())
{
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
void RenderObject::OnUpdate()
{
	// ����ʵ��
}
std::shared_ptr<Transform> RenderObject::GetTransform()
{
	return m_transform;
}

void RenderObject::Render(const XMMATRIX& parentModel)
{
	XMMATRIX model = m_transform->GetModelMatrix() * parentModel;
	for (auto p : childs)
	{
		p->Render(model);
		
	}
	//����ת�ú��
	DirectX::XMStoreFloat4x4(&m_modelBufferData.model, XMMatrixTranspose(model));
	auto context = m_deviceResources->GetD3DDeviceContext();

	SetState();

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
		DXGI_FORMAT_R32_UINT, // ÿ����������һ�� 16 λ�޷�������(short)��
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
	OnCreateResource();
}


void RenderObject::addChild(std::shared_ptr<RenderObject> child)
{
	childs.push_back(child);
	child->GetTransform()->setParent(m_transform);
	m_transform->childs.push_back(child->GetTransform());
}


void RenderObject::ReleaseDeviceDependentResources()
{
	m_inputLayout.Reset();
	m_modelBuffer.Reset();
	m_vertexBuffer.Reset();
	m_indexBuffer.Reset();
	for (auto p : childs)
	{
		p->ReleaseDeviceDependentResources();
	}
}
std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> RenderObject::getDepthDesc()
{
	std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> depthDesc = std::make_shared<D3D11_DEPTH_STENCIL_DESC>();
	depthDesc->DepthEnable = true;
	depthDesc->DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDesc->DepthFunc = D3D11_COMPARISON_LESS;
	return depthDesc;
}

std::shared_ptr<D3D11_RASTERIZER_DESC> RenderObject::getRasterizerDesc()
{
	std::shared_ptr<D3D11_RASTERIZER_DESC> rasterizerDesc = std::make_shared<D3D11_RASTERIZER_DESC>();
	ZeroMemory(rasterizerDesc.get(), sizeof(*rasterizerDesc));
	rasterizerDesc->FillMode = D3D11_FILL_SOLID;
	rasterizerDesc->CullMode = D3D11_CULL_BACK;
	rasterizerDesc->FrontCounterClockwise = true;
	rasterizerDesc->DepthClipEnable = true;
	return rasterizerDesc;
}

void RenderObject::CreateState(){

	std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> depthDesc = getDepthDesc();

	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	device->CreateDepthStencilState(depthDesc.get(), m_depthStencilState.GetAddressOf());

	std::shared_ptr< D3D11_RASTERIZER_DESC> rasterizerDesc = getRasterizerDesc();
	device->CreateRasterizerState(rasterizerDesc.get(), m_rasterizerState.GetAddressOf());

}
void RenderObject::SetState()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	context->RSSetState(m_rasterizerState.Get());
	context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
}