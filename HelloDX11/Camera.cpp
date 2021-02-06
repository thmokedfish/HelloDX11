#include "pch.h"
#include "Camera.h"
#include"InputManager.h"
using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::System;
Camera::Camera():following(NULL),eye({ 0.0f, 0.5f, 1.5f, 0.0f }),at({ 0.0f, -0.1f, 0.0f, 0.0f }),up({ 0.0f, 1.0f, 0.0f, 0.0f }){}

DirectX::XMMATRIX Camera::LookAt()
{
	return XMMatrixLookAtRH(eye, at, up);
}
void Camera::OnUpdate()
{
	if (following)
	{
		XMVECTOR diff = eyediff;
		//if (InputManager::GetKey(VirtualKey::Space))
		{
			//diff = XMVector3Transform(eyediff, XMMatrixRotationY(XM_PIDIV2));
		}
		XMVECTOR pos = following->getPosition();

		//if (InputManager::GetKey(VirtualKey::Space))
		{
			eye = pos + diff;
			at = pos + atdiff;
		}
	}

}
void Camera::SetFollow(RenderObject* following)
{
	this->following = following;
	XMVECTOR pos=following->getPosition();
	eyediff = eye - pos;
	atdiff = at -pos;
}