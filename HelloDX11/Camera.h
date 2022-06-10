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
		Transform m_transform;
		float sensitivity = 0.002f;
		float speed = 10;
	private:
		DirectX::XMVECTOR _handleInputVector();
		void _thirdPerspectiveUpdate();
		void _firstPerspectiveUpdate();
		DirectX::XMFLOAT3 atorigin;
		DirectX::XMFLOAT3 at;
		DirectX::XMFLOAT3 up;
		DirectX::XMFLOAT3 target_origin;
		DirectX::XMFLOAT3 eyeorigin;
		//DirectX::XMVECTOR eyediff;
		//DirectX::XMVECTOR atdiff;
		RenderObject* following;
	};

}