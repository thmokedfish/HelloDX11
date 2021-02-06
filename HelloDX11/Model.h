#pragma once
#include <vector>
namespace HelloDX11
{
	class Model
	{
	private:
		std::vector<DirectX::XMFLOAT3> verts_;//ÿ������һ����������
		std::vector<DirectX::XMFLOAT2> uvs_;//ÿ������һ��������������
		std::vector<std::vector<DirectX::XMINT2> > faces_;//ÿ������һ�飨3����һ���棩������������/����������������
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