#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
	class Wheel : public RenderObject
	{
	public:
		void Update(DX::StepTimer const& timer) override;
		void Rotate(float radians);
	};
}

