#include "pch.h"
#include "Common/Transfrom.h"
#include<iostream>
using namespace HelloDX11;
using namespace DirectX;

std::shared_ptr<Transform> Transform::root = std::make_shared<Transform>();;

Transform::Transform():m_position(), m_rotation(XMFLOAT4X4()), m_scale(XMFLOAT3(1,1,1))
{
	m_parent = root;
	XMStoreFloat4x4(&m_rotation, XMMatrixIdentity());
}
Transform::Transform(const Transform& cpy)
{
	std::cout << "tranform copy constructor" << std::endl;
}

std::shared_ptr<Transform> const Transform::getParent()
{
	if (!m_parent)
	{
		return root;
	}
	return m_parent;
}
void Transform::setParent(std::shared_ptr<Transform> parent)
{
	//¸üÐÂposµÈ
	if (parent == nullptr)
	{
		parent = root;
	}
	XMVECTOR abs_pos = getPosition();
	XMFLOAT3 abs_store;
	XMStoreFloat3(&abs_store, abs_pos);
	XMMATRIX inverse_trans = XMMatrixInverse(nullptr, parent->GetModelMatrix());
	XMVECTOR pos_v = XMVector3Transform(abs_pos, inverse_trans);
	XMStoreFloat3(&m_position, pos_v);
	m_parent = parent;
}
const DirectX::XMVECTOR& Transform::getPosition()
{
	XMVECTOR relat_pos = XMLoadFloat3(&m_position);
	XMVECTOR cal_pos = XMVector3Transform(relat_pos, m_parent->GetModelMatrix());
	return cal_pos;
}

const DirectX::XMFLOAT3& Transform::getLocalPosition()
{
	return m_position;
}
void Transform::setPosition(const XMFLOAT3& abs_pos)
{
	XMVECTOR pos_v = XMLoadFloat3(&abs_pos);
	return this->setPosition(pos_v);
}
void Transform::setPosition(const XMVECTOR& abs_pos)
{
	XMVECTOR v = XMVector3Transform(abs_pos, XMMatrixInverse(nullptr, m_parent->GetModelMatrix()));
	XMStoreFloat3(&m_position, v);
}
void Transform::setLocalPosition(const XMFLOAT3& pos) { m_position = pos; }
void Transform::setLocalPosition(const XMVECTOR& pos)
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
