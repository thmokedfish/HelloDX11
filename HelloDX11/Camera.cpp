#include "pch.h"
#include "Camera.h"
#include"InputManager.h"
using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::System;
Camera::Camera():following(NULL),eyeorigin({ 0.0f, 1, 1.5f, 0.0f }),atorigin({ 0.0f, -0.1f, 0.0f, 0.0f }),up({ 0.0f, 1.0f, 0.0f, 0.0f }){
	eye = eyeorigin;
	at=atorigin;
}

DirectX::XMMATRIX Camera::LookAt()
{
	return XMMatrixLookAtRH(eye, at, up);
}
void Camera::OnUpdate()
{
	if (following)
	{
		float mouseX = InputManager::GetMouseX();
		float mouseY = InputManager::GetMouseY();
		float sensitivity = 0.002f;
		//第三人称
		XMVECTOR atV = atorigin - eyeorigin;
		//先绕x轴
		atV = XMVector3Transform(atV, XMMatrixRotationX(sensitivity * mouseY));
		atV = XMVector3Transform(atV, XMMatrixRotationY(sensitivity * mouseX));
		at = atV + eyeorigin;


		XMVECTOR cardiff = XMLoadFloat3(&following->GetTransform().getPosition()) - carorigin;

		eye = eyeorigin + cardiff;
		at += cardiff;

	}

}
void Camera::SetFollow(RenderObject* following)
{
	this->following = following;
	carorigin = XMLoadFloat3(&following->GetTransform().getPosition());
	
	//eyediff = eye - pos;
	//atdiff = at -pos;

	
}
DirectX::XMVECTOR Camera::getPosition() { return eye; }