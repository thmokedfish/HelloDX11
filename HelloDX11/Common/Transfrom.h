#pragma once
#include"pch.h"
#include<vector>
#include "Common/Object.h"
namespace HelloDX11
{
	class Transform
	{
	private:
		//此乃相对位置/朝向/大小
		DirectX::XMFLOAT3 m_position;
		DirectX::XMFLOAT4X4 m_rotation;
		DirectX::XMFLOAT3 m_scale;
		std::shared_ptr<Transform> m_parent;
	public:
		Transform();
		Transform(const Transform& cpy);
		std::vector<std::shared_ptr<Transform>> childs;
		DirectX::XMVECTOR Forward();
		DirectX::XMVECTOR Right();
		DirectX::XMVECTOR Up();
		std::shared_ptr<Transform> const getParent();
		void setParent(std::shared_ptr<Transform> parent);
		const DirectX::XMVECTOR& getPosition();
		const DirectX::XMFLOAT3& getLocalPosition();
		void setPosition(const DirectX::XMFLOAT3& pos);
		void setPosition(const DirectX::XMVECTOR& pos);
		void setLocalPosition(const DirectX::XMFLOAT3& pos);
		void setLocalPosition(const DirectX::XMVECTOR& pos);
		void setScale(DirectX::XMFLOAT3 scale);
		void setScale(DirectX::XMVECTOR scale);
		void setRotation(DirectX::XMFLOAT4X4 rotation);
		void setRotation(DirectX::XMMATRIX rotation);
		void Rotate(DirectX::XMMATRIX trans_matrix);
		DirectX::XMMATRIX GetModelMatrix();
		static std::shared_ptr<Transform> root;
	};
}