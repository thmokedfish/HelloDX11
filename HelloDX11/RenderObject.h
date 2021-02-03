#pragma once
#include"pch.h"
#include"InputManager.h"
#include<vector>
#include"Geometry.h"
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
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_constantBuffer;
	protected:
		std::vector<RenderObject*> childs;
		//Geometry::MeshData<geoVPC> mesh;
	public:
		void SetShader();
		void Render();
	};
}
