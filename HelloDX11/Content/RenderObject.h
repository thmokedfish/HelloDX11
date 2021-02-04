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
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		uint32	m_indexCount;
		bool	m_loadingComplete;
	protected:
		ModelConstantBuffer                     	m_modelBufferData;
		std::vector<RenderObject*> childs;
		Geometry::MeshData<geoVPC> m_mesh;
	public:
		virtual void Update(DX::StepTimer const& timer) = 0;
		RenderObject(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		virtual void Render();
		void CreateResources();
		Geometry::MeshData<geoVPC> GetMesh();
		virtual ~RenderObject() = 0;
	};
}
