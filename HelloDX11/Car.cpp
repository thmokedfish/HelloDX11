#include "pch.h"
#include "Car.h"
#include"InputManager.h"
#include<algorithm>
using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::System;
Car::Car():RenderObject(),m_speed(0),m_wheelrotation(0),maxspeed(1.2f),ac(0.02f)
{
	setRotation(XMMatrixRotationY(XM_PIDIV2));
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<RenderObject> w = std::make_shared<Wheel>();
		childs.push_back(w);
		childs[i]->setScale(XMVectorSet(0.3f, 0.3f, 0.3f, 1));
		childs[i]->setRotation(XMMatrixRotationZ(-XM_PIDIV2));
	}
	float diffx = 0.17f; float diffy = -0.05f;float diffz= 0.15f;
	//设定轮子位置
	childs[0]->setPosition(XMVectorSet(diffx,diffy,diffz,1));

	childs[1]->setPosition(XMVectorSet(-diffx, diffy, diffz, 1));

	childs[2]->setPosition(XMVectorSet(diffx, diffy, -diffz, 1));

	childs[3]->setPosition(XMVectorSet(-diffx, diffy, -diffz, 1));
}
void Car::Move()
{
	if (carstate == MoveState::STOP)
	{
		m_speed += m_speed > 0 ? -ac : ac;
	}
	else if (carstate==MoveState::BACK)
	{
		if (m_speed >-maxspeed )
		{
			m_speed -= ac;
		}
	}
	else
	{
		if (m_speed < maxspeed)
		{
			m_speed += ac;
		}
	}
	m_rotation *= XMMatrixRotationY(m_speed*m_wheelrotation/30);

	//位移
	m_position+= m_speed*0.002f*Forward();
	//轮子旋转
	for (auto w : childs)
	{
		float degreesPerSecond = m_speed*60;
		float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
		double frameRotation = m_timer->GetElapsedSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(frameRotation, XM_2PI));
		w->Rotate(XMMatrixRotationAxis(w->Up(),radians));
	}
}
void Car::Turn()
{
	float degreesPerSecond = 75;
	float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
	double frameRotation = m_timer->GetElapsedSeconds() * radiansPerSecond;
	float radians = static_cast<float>(fmod(frameRotation, XM_2PI));
	if (wheelstate == WheelState::RECOVER)
	{
		radians *= m_wheelrotation > 0 ? -1 : 1;

	}
	else
	{
		radians *= wheelstate == WheelState::LEFT ? 1 : -1;
	}
	m_wheelrotation += radians;
	if (m_wheelrotation > XM_PIDIV4 || m_wheelrotation < -XM_PIDIV4)
	{
		m_wheelrotation -= radians;
		return;
	}
	childs[0]->Rotate(XMMatrixRotationY(radians));
	childs[1]->Rotate(XMMatrixRotationY(radians));

}
Geometry::MeshData<geoVPC> Car::CreateMesh()
{
	Geometry::MeshData<geoVPC> mesh = Geometry::CreateBox<geoVPC>(0.3f, 0.15f, 0.4f, { 0.5f,0.5f,1,1 });
	for (int i = 0; i < mesh.vertexVec.size(); i += 3)
	{
		mesh.vertexVec[i].color = { 1,1,1,1 };
	}
	return mesh;
}
//double hellotime = 0;
void Car::OnUpdate()
{
	//float degreesPerSecond = 45;
	//float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
	//double totalRotation = m_timer->GetElapsedSeconds() * radiansPerSecond;
	//float radians = static_cast<float>(fmod(totalRotation, XM_2PI));
	//Rotate(XMMatrixRotationY(radians));
	//先不写状态机了 丑了点
	if (InputManager::GetKey(VirtualKey::W))
	{
		carstate = MoveState::FORWARD;
	}
	else if (InputManager::GetKey(VirtualKey::S))
	{
		carstate = MoveState::BACK;
	}
	else
	{
		carstate = MoveState::STOP;
	}
	if (InputManager::GetKey(VirtualKey::A))
	{
		wheelstate = WheelState::LEFT;
	}
	else if (InputManager::GetKey(VirtualKey::D))
	{
		wheelstate = WheelState::RIGHT;
	}
	else
	{
		wheelstate = WheelState::RECOVER;
	}

	Turn();
	
	Move();
	
}
