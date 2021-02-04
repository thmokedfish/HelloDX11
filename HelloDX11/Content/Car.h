#pragma once
#include"RenderObject.h"
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
		void Rotate(float radias);
	public:
		
		void Update(DX::StepTimer const& timer) override;
	};

}