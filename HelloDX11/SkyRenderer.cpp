#include "pch.h"
//#include <tchar>
#include "SkyRenderer.h"
#include "..\Common\DirectXHelper.h"
#include"Reference/DDSTextureLoader11.h"
#include"Geometry.h"
using namespace HelloDX11;
using namespace DirectX;
void SkyRenderer::Init(ID3D11Device* device)
{
	typedef Geometry::VertexPosColor geoVPC;
	auto loadVSTask = DX::ReadDataAsync(L"Sky_VS.cso");
	auto loadPSTask = DX::ReadDataAsync(L"Sky_PS.cso");
	auto createVSTask = loadVSTask.then([this, device](const std::vector<byte>& fileData)
		{
			device->CreateVertexShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pSkyVS
			);
			device->CreateInputLayout(
				geoVPC::inputLayout,
				ARRAYSIZE(geoVPC::inputLayout),
				&fileData[0],
				fileData.size(),
				&m_pVertexPosLayout);
		});
	auto createPSTask = loadPSTask.then([this,device](const std::vector<byte>& fileData)
		{
			// ******************
			// 创建像素着色器
			//

			device->CreatePixelShader(
				&fileData[0],
				fileData.size(),
				nullptr,
				&m_pSkyPS);
			/*

			CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				m_deviceResources->GetD3DDevice()->CreateBuffer(
					&constantBufferDesc,
					nullptr,
					&m_constantBuffer
				)
			);

			pImpl->m_pCBuffers.assign({
				&pImpl->m_CBFrame,
				});
			// 创建常量缓冲区
			for (auto& pBuffer : pImpl->m_pCBuffers)
			{
				pBuffer->CreateBuffer(device);
			}*/

		});
	auto initResources = (createPSTask && createVSTask).then([this,device]()
		{
			D3D11_DEPTH_STENCIL_DESC skyDepthDesc;
			skyDepthDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			device->CreateDepthStencilState(&skyDepthDesc, m_skyDepthState.GetAddressOf());
			wchar_t b[] = TEXT("HelloSky.dds");
			CreateDDSTextureFromFile(device, b, nullptr, m_textureView.GetAddressOf());
		});

	initResources.then([this]() {
		m_loadingComplete = true;
		});

}

void SkyRenderer::Render(ID3D11DeviceContext* context)
{
	if (!m_loadingComplete)
	{
		return;
	}
	context->IASetInputLayout(m_pVertexPosLayout.Get());
	context->VSSetShader(m_pSkyVS.Get(), nullptr, 0);
	context->PSSetShader(m_pSkyPS.Get(), nullptr, 0);

	UINT strides = sizeof(Geometry::VertexPosColor) ;
	UINT offsets =  0 ;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &strides, &offsets);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);




	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	//context->PSSetSamplers(0, 1, RenderStates::SSLinearWrap.GetAddressOf());
	context->OMSetDepthStencilState(m_skyDepthState.Get(), 1);
	//context->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
	context->DrawIndexed(
		m_indexCount,
		0,
		0
	);
}