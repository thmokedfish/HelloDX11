#pragma once
#include"RenderObject.h"
#include"Wheel.h"
namespace HelloDX11
{
	class Car :public RenderObject
	{

	private:
		enum Direction
		{
			LEFT, RIGHT, FORWARD
		};
		Direction state;
		void MoveForward();
		void MoveBackward();
		void TurnLeft();
		void TurnRight();
		void Rotate(float radians);
		Wheel wheels[4];
	public:
		Car();
		void Update(DX::StepTimer const& timer) override;
	};

}