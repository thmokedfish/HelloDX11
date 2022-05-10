#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
	class Wheel : public RenderObject
	{
	protected:
		void OnCreateResource() override;
	public:
		void OnUpdate() override;
	};
}

