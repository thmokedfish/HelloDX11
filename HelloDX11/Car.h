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
		Geometry::MeshData<geoVPC> CreateMesh() override;
		void TurnRight();
	public:
		Car();
		void OnUpdate(DX::StepTimer const& timer) override;
	};

}