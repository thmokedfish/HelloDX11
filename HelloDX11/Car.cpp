#include "pch.h"
#include "Car.h"
#include"InputManager.h"
#include<algorithm>
using namespace HelloDX11;
using namespace DirectX;
using namespace Windows::System;
Car::Car():RenderObject(),m_speed(0),m_wheelrotation(0),maxspeed(80),maxav(15.0f),ac(0.5f)
{
	m_transform->setRotation(XMMatrixRotationY(XM_PIDIV2));
	for (int i = 0; i < 4; ++i)
	{
		std::shared_ptr<RenderObject> w = std::make_shared<Wheel>();
		this->addChild(w);
		childs[i]->GetTransform()->setScale(XMVectorSet(0.3f, 0.3f, 0.3f, 1));
		childs[i]->GetTransform()->setRotation(XMMatrixRotationZ(-XM_PIDIV2));
	}
	float diffx = 0.17f; float diffy = -0.05f;float diffz= 0.15f;
	//设定轮子位置
	childs[0]->GetTransform()->setPosition(XMVectorSet(diffx,diffy,diffz,1));

	childs[1]->GetTransform()->setPosition(XMVectorSet(-diffx, diffy, diffz, 1));

	childs[2]->GetTransform()->setPosition(XMVectorSet(diffx, diffy, -diffz, 1));

	childs[3]->GetTransform()->setPosition(XMVectorSet(-diffx, diffy, -diffz, 1));
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
	//(s/maxspeed)*maxav，maxav：最大旋转速度
	float av = m_speed * maxav / maxspeed;
	//小车旋转
	//wheelrotation范围(-45,45)，wheelrotation/45以映射到(-1,1)
	m_transform->Rotate(XMMatrixRotationY(av * m_wheelrotation / 45));
	//位移
	XMVECTOR pos = m_transform->getPosition();
	XMVECTOR res = pos + m_speed * 0.002f * m_transform->Forward();
	m_transform->setPosition(res);
	//轮子旋转
	for (auto w : childs)
	{
		float degreesPerSecond = m_speed*60;
		float radiansPerSecond = XMConvertToRadians(degreesPerSecond);
		double frameRotation = m_timer->GetElapsedSeconds() * radiansPerSecond;
		float radians = static_cast<float>(fmod(frameRotation, XM_2PI));
		w->GetTransform()->Rotate(XMMatrixRotationAxis(w->GetTransform()->Up(),radians));
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
	childs[0]->GetTransform()->Rotate(XMMatrixRotationY(radians));
	childs[1]->GetTransform()->Rotate(XMMatrixRotationY(radians));

}

void Car::OnCreateResource()
{
	Geometry::MeshData<geoVPC> mesh = Geometry::CreateBox<geoVPC>(0.3f, 0.15f, 0.4f, { 0.5f,0.5f,1,1 });
	//for (int i = 0; i < mesh.vertexVec.size(); i += 3)
	{
		//	mesh.vertexVec[i].color = { 1,1,1,1 };
	}
	this->CreateResourceWithVertexData(mesh);
}

void Car::OnUpdate()
{
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
