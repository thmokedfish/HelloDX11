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
		float maxav;
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
		Geometry::MeshData<geoVPC> CreateMesh() override;
	public:
		Car();
		void OnUpdate() override;
	};

}