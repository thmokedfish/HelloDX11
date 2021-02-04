#pragma once
#include "RenderObject.h"
namespace HelloDX11
{
	class Wheel : public RenderObject
	{
	public:
		Wheel(const std::shared_ptr<DX::DeviceResources>& deviceResources) :RenderObject(deviceResources) {}
		void Update(DX::StepTimer const& timer) override;
	};
}

