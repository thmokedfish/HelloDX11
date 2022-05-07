#include "pch.h"
#include "Model.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "model.h"
using namespace HelloDX11;
Model::Model(const char* filename) : verts_(), faces_(), normals_(), uvs_()
//, normalmap_() 
{
}
/*
void Model::load_texture(std::string filename, const char* suffix, TGAImage& img) {
	std::string texfile(filename);
	size_t dot = texfile.find_last_of(".");
	if (dot != std::string::npos) {
		texfile = texfile.substr(0, dot) + std::string(suffix);
		img.flip_vertically();
	}
}*/

Model::~Model() {
}

bool Model::LoadFromFile(const char* filename)
{
	std::ifstream in;
	in.open(filename, std::ifstream::in);
	if (in.fail()) return false;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) {
			iss >> trash;
			DirectX::XMFLOAT3 v;
			iss >> v.x;
			iss >> v.y;
			iss >> v.z;
			verts_.push_back(v);
			continue;
		}
		if (!line.compare(0, 2, "vt"))
		{
			iss >> trash >> trash;
			DirectX::XMFLOAT2 vt;
			iss >> vt.x;
			iss >> vt.y;
			uvs_.push_back(vt);
			continue;
		}
		if (!line.compare(0, 2, "f ")) {
			std::vector<DirectX::XMINT2> f;
			int itrash, idx, ivt;
			iss >> trash;
			while (iss >> idx >> trash >> ivt >> trash >> itrash) {
				idx--; // in wavefront obj all indices start at 1, not zero
				ivt--;
				f.push_back(DirectX::XMINT2(idx, ivt));
			}
			faces_.push_back(f);
			continue;
		}
		if (!line.compare(0, 2, "vn"))
		{
			iss >> trash >> trash;
			DirectX::XMFLOAT3 vn;
			iss >> vn.x;
			iss >> vn.y;
			iss >> vn.z;
			normals_.push_back(vn);
			continue;
		}
	}
	//load_texture(filename, "_nm.tga", normalmap_);
}

int Model::nverts() {
	return (int)verts_.size();
}
int Model::nvts() {
	return (int)uvs_.size();
}

int Model::nfaces() {
	return (int)faces_.size();
}

std::vector<DirectX::XMINT2> Model::face(int idx) {
	return faces_[idx];
}
DirectX::XMFLOAT3 Model::vert(int i) {
	return verts_[i];
}
DirectX::XMFLOAT3 Model::vert(int iface, int nthvert)
{
	return this->verts_[face(iface)[nthvert].x];
}

DirectX::XMFLOAT2 Model::uv(int i)
{
	return uvs_[i];
}

DirectX::XMFLOAT2 Model::uv(int iface, int nthvert)
{
	return this->uvs_[face(iface)[nthvert].y];
}

/*
DirectX::XMFLOAT3 Model::normal(DirectX::XMFLOAT2 uvf) {
	DirectX::XMINT2 uv(uvf[0] * normalmap_.get_width(), uvf[1] * normalmap_.get_height());
	TGAColor c = normalmap_.get(uv[0], uv[1]);
	DirectX::XMFLOAT3 res;
	for (int i = 0; i < 3; i++)
		res[2 - i] = (float)c[i] / 255.f * 2.f - 1.f;
	return res;
}*/

DirectX::XMFLOAT3 Model::normal(int i)
{
	return normals_[i];
}

DirectX::XMFLOAT3 Model::normal(int iface, int nthvert)
{
	DirectX::XMFLOAT3* n = &this->normals_[face(iface)[nthvert].x];
	DirectX::XMVECTOR v = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(n));
	DirectX::XMStoreFloat3(n, v);
	return *n;
}
