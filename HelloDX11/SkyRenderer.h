#pragma once
#include"pch.h"
namespace HelloDX11
{
	class SkyRenderer
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureView;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_pSkyVS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pSkyPS;
		Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pVertexPosLayout;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_skyDepthState; 
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_vertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>		m_indexBuffer;
		bool m_loadingComplete;
	public:
		void Init(ID3D11Device* device);
		void Render(ID3D11DeviceContext* context);
	};
}