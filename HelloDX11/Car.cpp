#include "pch.h"
#include "Car.h"
using namespace HelloDX11;
using namespace DirectX;
Car::Car():RenderObject()
{
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<RenderObject> w = std::make_shared<Wheel>();
		childs.push_back(w);
	}
	//设定轮子位置
	childs[0]->setPosition(XMFLOAT3(0.5f, 0, 0.5f));
	childs[1]->setPosition(XMFLOAT3(0.5f, 0, -0.5f));
	childs[2]->setPosition(XMFLOAT3(-0.5f, 0, 0.5f));
	childs[3]->setPosition(XMFLOAT3(-0.5f, 0, -0.5f));
}
void Car::MoveForward()
{

}
void Car::MoveBackward()
{

}
void Car::TurnLeft()
{

}
Geometry::MeshData<geoVPC> Car::CreateMesh()
{
	return Geometry::CreateBox<geoVPC>(0.2f, 0.2f, 0.4f);
}
void Car::TurnRight()
{

}
void Car::OnUpdate(DX::StepTimer const& timer)
{
	float degreesPerSecond = 45;

	float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
	double totalRotation = timer.GetTotalSeconds() * radiansPerSecond;
	float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
	
	m_rotation= XMMatrixTranspose(XMMatrixRotationY(radians));
}
