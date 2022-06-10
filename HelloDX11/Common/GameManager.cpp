#include "pch.h"
#include "GameManager.h"
using namespace HelloDX11;

Camera* GameManager::MainCamera;
DX::StepTimer* GameManager::StepTimer;
std::shared_ptr<DX::DeviceResources> GameManager::DeviceResources;
GameManager::GameManager()
{}