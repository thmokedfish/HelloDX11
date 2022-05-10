#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
    class Ground : public RenderObject
    {
	protected:
		void OnCreateResource() override;
	public:
		void OnUpdate() override;
    };
}

