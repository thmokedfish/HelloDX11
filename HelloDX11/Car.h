#pragma once
#include"RenderObject.h"
#include"Wheel.h"
namespace HelloDX11
{
	class Car :public RenderObject
	{

	private:
		float m_speed;
		float m_wheelrotation;
		float maxspeed;
		//最大转速
		float maxav;
		//加速度
		float ac;
	private:
		enum MoveState
		{
			FORWARD,BACK,STOP
		};
		enum WheelState
		{
			LEFT, RIGHT,RECOVER
		};
		MoveState carstate;
		WheelState wheelstate;
		void Move();
		void Turn();
		//Geometry::MeshData<geoVPC> GetMesh() override;
		void OnCreateResource() override;
	public:
		Car();
		void OnUpdate() override;
	};

}