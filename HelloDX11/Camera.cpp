#include "pch.h"
#include "Camera.h"
#include"InputManager.h"
#include "Common/GameManager.h"
using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::System;
Camera::Camera() :m_transform(), following(NULL), eyeorigin(0.0f, 1, 1.5f), atorigin(0.0f, -0.1f, 0.0f), up(0.0f, 1.0f, 0.0f)
{
	GameManager::MainCamera = this;
	m_transform.setPosition(eyeorigin);
	at = atorigin;
}

DirectX::XMMATRIX Camera::LookAt()
{
	return XMMatrixLookAtRH(m_transform.getPosition(), XMLoadFloat3(&at), XMLoadFloat3(&up));
}
void Camera::OnUpdate()
{
	float mouseX = InputManager::GetMouseX();
	float mouseY = InputManager::GetMouseY();
	XMVECTOR v_eyeorigin = XMLoadFloat3(&eyeorigin);
	XMVECTOR v_atorigin = XMLoadFloat3(&atorigin);
	XMVECTOR atV = v_atorigin - v_eyeorigin;
	XMMATRIX rotate_transform = XMMatrixRotationX(sensitivity * mouseY) * XMMatrixRotationY(sensitivity * mouseX);
	atV = XMVector3Transform(atV, rotate_transform);
	XMVECTOR cur_pos;
	if (following)
	{
		//µÚÈýÈË³Æ
		XMVECTOR v_target_origin = XMLoadFloat3(&target_origin);
		XMVECTOR targetdiff = following->GetTransform()->getPosition() - v_target_origin;
		cur_pos = v_eyeorigin + targetdiff;
		_thirdPerspectiveUpdate();
	}
	else
	{
		XMVECTOR raw_input = _handleInputVector();
		raw_input = XMVector3Transform(raw_input, rotate_transform);
		cur_pos = m_transform.getPosition() + raw_input *speed* GameManager::StepTimer->GetElapsedSeconds();
		_firstPerspectiveUpdate();
	}
	m_transform.setPosition(cur_pos);
	atV += cur_pos;
	XMStoreFloat3(&at, atV);
}
XMVECTOR Camera::_handleInputVector()
{
	XMVECTOR input_v = XMVECTOR({ 0,0,0,0 });
	if (InputManager::GetKey(VirtualKey::W))
	{
		input_v += XMVECTOR({ 0,0,-1,0 });
	}
	if (InputManager::GetKey(VirtualKey::S))
	{
		input_v += XMVECTOR({ 0,0,1,0 });
	}
	if (InputManager::GetKey(VirtualKey::A))
	{
		input_v += XMVECTOR({ -1,0,0,0 });
	}
	else if (InputManager::GetKey(VirtualKey::D))
	{
		input_v += XMVECTOR({ 1,0,0,0 });
	}
	return input_v;
}
void Camera::_thirdPerspectiveUpdate()
{
}
void Camera::_firstPerspectiveUpdate()
{
}
void Camera::SetFollow(RenderObject* following)
{
	this->following = following;
	XMStoreFloat3(&target_origin, following->GetTransform()->getPosition());
}
DirectX::XMVECTOR Camera::getPosition() { return m_transform.getPosition(); }