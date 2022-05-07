#pragma once
#include"pch.h"
#include<vector>
namespace HelloDX11
{
	class Transform
	{
	private:
		std::shared_ptr<Transform> parent;
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT4X4 m_rotation;
		DirectX::XMFLOAT3 m_scale;
	public:
		Transform();
		Transform(const Transform& cpy);
		DirectX::XMVECTOR Forward();
		DirectX::XMVECTOR Right();
		DirectX::XMVECTOR Up();
		const DirectX::XMFLOAT3& getPosition();
		void setPosition(const DirectX::XMFLOAT3& pos);
		void setPosition(const DirectX::XMVECTOR& pos);
		void setScale(DirectX::XMFLOAT3 scale);
		void setScale(DirectX::XMVECTOR scale);
		void setRotation(DirectX::XMFLOAT4X4 rotation);
		void setRotation(DirectX::XMMATRIX rotation);
		void Rotate(DirectX::XMMATRIX trans_matrix);
		DirectX::XMMATRIX GetModelMatrix();
	};

}