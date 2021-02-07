#pragma once
#include"pch.h"
#include"Geometry.h"
#include"RenderObject.h"
#include "Content\ShaderStructures.h"
#include "..\Common\StepTimer.h"
#include "..\Common\DeviceResources.h"
namespace HelloDX11
{
	class Camera
	{
	public:
		Camera();
		DirectX::XMMATRIX LookAt();
		void SetFollow(RenderObject* following);
		void OnUpdate();
		DirectX::XMVECTOR getPosition();
		
	private:
		DirectX::XMVECTOR atorigin;
		DirectX::XMVECTOR eye;
		DirectX::XMVECTOR at;
		DirectX::XMVECTOR up;
		DirectX::XMVECTOR carorigin;
		DirectX::XMVECTOR eyeorigin;
		//DirectX::XMVECTOR eyediff;
		//DirectX::XMVECTOR atdiff;
		RenderObject* following;
	};

}