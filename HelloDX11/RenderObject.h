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
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT4X4 m_rotation;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>	m_inputLayout;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>	m_vertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>	m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_modelBuffer;
		std::shared_ptr<DX::DeviceResources>		m_deviceResources;
		uint32	m_indexCount;
		bool	m_loadingComplete;
	protected:
		ModelConstantBuffer                     	m_modelBufferData;
		std::vector<RenderObject*> childs;
		Geometry::MeshData<geoVPC> m_mesh;
		void Transform(const DirectX::XMFLOAT4X4& parentModel);
	public: 
		RenderObject();
		RenderObject(DirectX::XMFLOAT3 position);
		virtual void Update(DX::StepTimer const& timer);
		virtual void Render();
		void CreateResources(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		void ReleaseDeviceDependentResources();
		Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() {};
	};
}
