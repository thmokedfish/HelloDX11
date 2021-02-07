#pragma once
#include"pch.h"
#include "..\Common\DeviceResources.h"
#include<vector>
#include "Geometry.h"
#include "Content\ShaderStructures.h"
#include "..\Common\StepTimer.h"
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
		DirectX::XMVECTOR m_position;
		DirectX::XMMATRIX m_rotation;
		DirectX::XMVECTOR m_scale;
		std::vector<std::shared_ptr<RenderObject>> childs;
		Geometry::MeshData<geoVPC> m_mesh;
		virtual Geometry::MeshData<geoVPC> CreateMesh()=0;
		virtual void CreateState();
		virtual void SetState();
	public:
		RenderObject();
		DirectX::XMVECTOR Forward();
		DirectX::XMVECTOR Right();
		DirectX::XMVECTOR Up();
		static const DX::StepTimer* m_timer;
		DirectX::XMVECTOR getPosition();
		void addChild(std::shared_ptr<RenderObject> child);
		void setPosition(DirectX::XMVECTOR pos);
		void setScale(DirectX::XMVECTOR scale);
		void setRotation(DirectX::XMMATRIX rotation);
		void Rotate(DirectX::XMMATRIX transform);
		void Update();
		virtual void OnUpdate() = 0;
		virtual void Render(const DirectX::XMMATRIX& parentModel);
		void CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void ReleaseDeviceDependentResources();
		//Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() {};
	};
}
