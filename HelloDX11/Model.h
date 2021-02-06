#pragma once
#include <vector>
namespace HelloDX11
{
	class Model
	{
	private:
		std::vector<DirectX::XMFLOAT3> verts_;//每个代表一个顶点坐标
		std::vector<DirectX::XMFLOAT2> uvs_;//每个代表一个顶点纹理坐标
		std::vector<std::vector<DirectX::XMINT2> > faces_;//每个代表一组（3个，一个面）顶点坐标索引/顶点纹理坐标索引
		std::vector<DirectX::XMFLOAT3> normals_; //vertix normal
		//TGAImage normalmap_;
		//TGAImage diffusemap_;
		//TGAImage specularmap_;
	public:
		//void load_texture(std::string filename, const char* suffix, TGAImage& img);
		Model(const char* filename);
		~Model();
		int nverts();
		int nfaces();
		int nvts();
		DirectX::XMFLOAT3 vert(int i);
		DirectX::XMFLOAT3 vert(int iface, int nthvert);
		DirectX::XMFLOAT2 uv(int i);
		DirectX::XMFLOAT2 uv(int iface, int nthvert);
		DirectX::XMFLOAT3 normal(DirectX::XMFLOAT2 uvf);
		DirectX::XMFLOAT3 normal(int i);
		DirectX::XMFLOAT3 normal(int iface, int nthvert);
		std::vector<DirectX::XMINT2> face(int idx);

	};
}