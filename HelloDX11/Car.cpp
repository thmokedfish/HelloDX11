#include "pch.h"
#include "Car.h"
using namespace HelloDX11;
using namespace DirectX;
void Car::MoveForward()
{

}
void Car::MoveBackward()
{

}
void Car::TurnLeft()
{

}

void Car::TurnRight()
{

}
void Car::Update(DX::StepTimer const& timer)
{
	float degreesPerSecond = 45;
	// 将度转换成弧度，然后将秒转换为旋转角度
	float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
	double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
	float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
	Rotate(radians);
	//if input w
	//wheel rotate x
	//if input a/d
	//wheel rotate y
}

void Car::Rotate(float radians)
{
	XMMATRIX model = XMMatrixTranspose(XMMatrixRotationY(radians));
	model = XMMatrixTranspose(XMMatrixRotationZ(XM_PIDIV2)) * model;
	XMStoreFloat4x4(&m_modelBufferData.model, model);
}