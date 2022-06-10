#pragma once
#include "Camera.h"
#include "StepTimer.h"
namespace HelloDX11
{
	class GameManager
	{
	public:
		static Camera* MainCamera;
		static DX::StepTimer* StepTimer;
		static std::shared_ptr<DX::DeviceResources> DeviceResources;
	private:
		GameManager();
	};
}