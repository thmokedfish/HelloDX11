#pragma once

namespace HelloDX11
{
	// 用于向顶点着色器发送 MVP 矩阵的常量缓冲区。
	struct ModelViewProjectionConstantBuffer
	{
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};
	struct ModelConstantBuffer
	{
		ModelConstantBuffer()
		{
			for (int i = 0; i < 4; ++i)
			{
				model(i,i) = 1;
			}
		}
		DirectX::XMFLOAT4X4 model;
	};
	// 用于向顶点着色器发送每个顶点的数据。
	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};
}