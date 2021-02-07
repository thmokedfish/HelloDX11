#pragma once
#include"Camera.h"
#include"RenderObject.h"
#include"Camera.h"
namespace HelloDX11
{
	class Skybox:public RenderObject
	{
	public:
		void SetFollow(Camera* cam);
	protected:
		Geometry::MeshData<geoVPC> CreateMesh() override;
		void CreateState() override;
		void SetState() override;
	private:
		Camera* camera;
		DirectX::XMMATRIX cam_pos;
		void OnUpdate() override;
		
	};
}

