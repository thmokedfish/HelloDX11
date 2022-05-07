#pragma once
#include"pch.h"
#include "..\Common\DeviceResources.h"
#include<vector>
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
		Geometry::MeshData<geoVPC> m_mesh;
		virtual Geometry::MeshData<geoVPC> CreateMesh()=0;
		virtual std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> getDepthDesc();
		virtual std::shared_ptr<D3D11_RASTERIZER_DESC> getRasterizerDesc();
		std::vector<std::shared_ptr<RenderObject>> childs;
		void CreateState();
		void SetState();
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
		void CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void ReleaseDeviceDependentResources();
		//Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() {};
	};
}
