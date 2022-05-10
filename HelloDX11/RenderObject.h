#pragma once
#include"pch.h"
#include "..\Common\DeviceResources.h"
#include<vector>
#include <Common/DirectXHelper.h>
#include "Geometry.h"
#include "Content\ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "Common/Transfrom.h"
namespace HelloDX11
{
	typedef Geometry::VertexPosColor geoVPC;
	class RenderObject
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_modelBuffer;
		uint32	m_indexCount;
		bool	m_loadingComplete;
		ModelConstantBuffer                     	m_modelBufferData;
	protected:
		std::shared_ptr<DX::DeviceResources>		m_deviceResources;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState>	m_rasterizerState;
		Transform m_transform;
		//void* m_mesh;
		//virtual Geometry::MeshData<class T> GetMesh()=0;
		virtual std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> getDepthDesc();
		virtual std::shared_ptr<D3D11_RASTERIZER_DESC> getRasterizerDesc();
		std::vector<std::shared_ptr<RenderObject>> childs;
		void CreateState();
		void SetState();
		virtual void OnCreateResource()=0;
		template<class T>
		void CreateResourceWithVertexData(Geometry::MeshData<T> mesh);
	public:
		RenderObject();
		void Update();
		Transform& GetTransform();
		static const DX::StepTimer* m_timer;
		/*
		* Both XMVECTOR and XMMATRIX have alignment requirements, so it is not recommended to use them directly as class/struct variables. 
		* If you are following that advice, then you need to use XMStoreFloat4x4 and XMLoadFloat4x4 to convert between XMFLOAT4X4 and XMMATRIX
		*/
		virtual void OnUpdate() = 0;
		void addChild(std::shared_ptr<RenderObject> child);
		virtual void Render(const DirectX::XMMATRIX& parentModel);
		//virtual void SetVertexShader(std::string shaderName);
		//std::string GetVertexShader();
		//virtual void SetPixelShader(std::string shaderName);
		//std::string GetPixelShader();
		void CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void ReleaseDeviceDependentResources();
		//Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() {};
	};

}
using namespace HelloDX11;
//子类OnCreateResource时调用
template<class T>
void RenderObject::CreateResourceWithVertexData(Geometry::MeshData<T> mesh)
{
	auto v = mesh.vertexVec;
	int vsize = v.size();
	static T* vertices = new T[vsize];
	std::copy(v.begin(), v.end(), vertices);

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = vertices;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(T) * vsize, D3D11_BIND_VERTEX_BUFFER);
	DX::ThrowIfFailed(
		m_deviceResources->GetD3DDevice()->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
		)
	);
	int indexSize = mesh.indexVec.size();
	//unsigned short a[10];
	static unsigned short* meshIndices = new unsigned short[indexSize];
	std::copy(mesh.indexVec.begin(), mesh.indexVec.end(), meshIndices);
	//m_indexCount = ARRAYSIZE(meshIndices);
	m_indexCount = mesh.indexVec.size();

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
	CreateState();
}