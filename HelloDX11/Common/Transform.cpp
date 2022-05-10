#include "pch.h"
#include "Common/Transfrom.h"
#include<iostream>
using namespace HelloDX11;
using namespace DirectX;

Transform::Transform():m_position(), m_rotation(XMFLOAT4X4()), m_scale(XMFLOAT3(1,1,1))
{
	XMStoreFloat4x4(&m_rotation, XMMatrixIdentity());
}
Transform::Transform(const Transform& cpy)
{
	std::cout << "tranform copy constructor" << std::endl;
}
const DirectX::XMFLOAT3& Transform::getPosition() { return m_position; }
void Transform::setPosition(const XMFLOAT3& pos) { m_position = pos; }
void Transform::setPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&m_position, pos);
}
void Transform::setScale(DirectX::XMFLOAT3 scale) { m_scale = scale; }
void Transform::setScale(DirectX::XMVECTOR scale)
{
	XMStoreFloat3(&m_scale, scale);
}
void Transform::setRotation(XMFLOAT4X4 rotation) { m_rotation = rotation; }
void Transform::setRotation(XMMATRIX rotation)
{
	XMStoreFloat4x4(&m_rotation, rotation);
}

DirectX::XMVECTOR Transform::Forward()
{
	XMVECTOR origin = XMVectorSet(0, 0, 1, 1);
	XMMATRIX rot = XMLoadFloat4x4(&m_rotation);
	return XMVector4Transform(origin, rot);
}
DirectX::XMVECTOR Transform::Right()
{
	XMVECTOR origin = XMVectorSet(1, 0, 0, 1);
	XMMATRIX rot = XMLoadFloat4x4(&m_rotation);
	return XMVector4Transform(origin, rot);
}

DirectX::XMVECTOR Transform::Up()
{
	XMVECTOR origin = XMVectorSet(0, 1, 0, 1);
	XMMATRIX rot = XMLoadFloat4x4(&m_rotation);
	return XMVector4Transform(origin, rot);
}
void Transform::Rotate(DirectX::XMMATRIX trans_matrix)
{
	XMMATRIX rot = XMLoadFloat4x4(&m_rotation);
	XMStoreFloat4x4(&m_rotation, rot * trans_matrix);
}

XMMATRIX Transform::GetModelMatrix()
{
	XMMATRIX rot = XMLoadFloat4x4(&m_rotation);
	XMVECTOR translation = XMLoadFloat3(&m_position);
	return XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z) * rot * XMMatrixTranslationFromVector(translation);
}
