#pragma once
#include"Camera.h"
#include"RenderObject.h"
namespace HelloDX11
{
	class Skybox:public RenderObject
	{
	public:
		void SetFollow(Camera* cam);
	protected:
		//Geometry::MeshData<geoVPC> GetMesh() override;
		void OnCreateResource() override;
		virtual std::shared_ptr<D3D11_DEPTH_STENCIL_DESC> getDepthDesc() override;
		virtual std::shared_ptr<D3D11_RASTERIZER_DESC> getRasterizerDesc() override;
	private:
		Camera* camera;
		DirectX::XMMATRIX cam_pos;
		void OnUpdate() override;
		
	};
}

