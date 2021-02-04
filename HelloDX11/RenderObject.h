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
		std::shared_ptr<DX::DeviceResources>		m_deviceResources;
		uint32	m_indexCount;
		bool	m_loadingComplete;
		ModelConstantBuffer                     	m_modelBufferData;
	protected:
		DirectX::XMFLOAT3 m_position;
		DirectX::XMMATRIX m_rotation;
		std::vector<std::shared_ptr<RenderObject>> childs;
		Geometry::MeshData<geoVPC> m_mesh;
		void Transform(const DirectX::XMFLOAT4X4& parentModel);
		virtual Geometry::MeshData<geoVPC> CreateMesh()=0;
	public: 
		RenderObject();
		RenderObject(DirectX::XMFLOAT3 position);
		DirectX::XMFLOAT3 getPosition();
		void setPosition(DirectX::XMFLOAT3 pos);
		void Update(DX::StepTimer const& timer);
		virtual void OnUpdate(DX::StepTimer const& timer) = 0;
		virtual void Render(const DirectX::XMMATRIX& parentModel);
		void CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void ReleaseDeviceDependentResources();
		//Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() {};
	};
}
