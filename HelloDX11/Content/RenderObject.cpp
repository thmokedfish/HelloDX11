#include "pch.h"
#include "RenderObject.h"
#include <Common/DirectXHelper.h>
using namespace HelloDX11;
using namespace DirectX;

RenderObject::RenderObject(const std::shared_ptr<DX::DeviceResources>& deviceResources):m_deviceResources(deviceResources)
{}

void RenderObject::Render()
{
	// 加载是异步的。仅在加载几何图形后才会绘制它。
	if (!m_loadingComplete)
	{
		return;
	}

	for (auto p : childs)
	{
		p->Render();
	}
	auto context = m_deviceResources->GetD3DDeviceContext();

	// 准备常量缓冲区以将其发送到图形设备。
	context->UpdateSubresource1(
		m_modelBuffer.Get(),
		0,
		NULL,
		&m_modelBufferData,
		0,
		0,
		0
	);
	// 每个顶点都是 VertexPositionColor 结构的一个实例。
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
		DXGI_FORMAT_R16_UINT, // 每个索引都是一个 16 位无符号整数(short)。
		0
	);

	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//context->IASetInputLayout(m_inputLayout.Get());
	

	// 将常量缓冲区发送到图形设备。
	context->VSSetConstantBuffers1(
		1,
		1,
		m_modelBuffer.GetAddressOf(),
		nullptr,
		nullptr
	);

	// 绘制对象。
	context->DrawIndexed(
		m_indexCount,
		0,
		0
	);
}
void RenderObject::CreateResources()
{
	for (auto p : childs)
	{
		p->CreateResources();
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
		unsigned short a[10];
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

}
Geometry::MeshData<geoVPC> RenderObject::GetMesh()
{
	return m_mesh;
}
