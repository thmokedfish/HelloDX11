#pragma once
#include"Camera.h"
#include"RenderObject.h"
#include"Model.h"
#include "Common/Tools/tgaimage.h"
#include "Geometry.h"

namespace HelloDX11
{
	class HeightmapSampling
	{
	public:
		HeightmapSampling() {};
		std::shared_ptr<TGAImage> LoadHeightmapTGA(std::string filename);
		//std::vector<float> LoadHeightmapTGA(std::string filename);
		std::vector<float> LoadHeightmapRAW(std::string filename);
		Model Sample(std::vector<float> heightInfos, int layer=0);  // 需要生成顶点法线、uv等
		//Model LoadAndSample(std::string filename, int layer = 0);  
		template<class VertexType, class IndexType = UINT>
		Geometry::MeshData<VertexType, IndexType> LoadAndSample(std::string filename, int layer=0);
	};



};

using namespace HelloDX11;
using namespace Geometry;
template<class VertexType, class IndexType>
Geometry::MeshData<VertexType, IndexType> HeightmapSampling::LoadAndSample(std::string filename, int layer)
{
	using namespace DirectX;
	std::shared_ptr<TGAImage> image = LoadHeightmapTGA(filename);
	int width = image->get_width();
	int height = image->get_height();
	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(height * width);
	meshData.indexVec.reserve(height * width);
	Geometry::Internal::VertexData* vertexDataArr = new Geometry::Internal::VertexData[height * width];
	for (int z = 0; z < height; ++z)
	{
		int offset = z * width;
		for (int x = 0; x < width; ++x)
		{
			float h = image->get(x, z)[0];
			//先实现一个全三角形的
			int idx = offset + x;
			vertexDataArr[idx].pos = XMFLOAT3(x, h*0.2, z);
			vertexDataArr[idx].color = XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f);

		}
	}
	for (int i = 0; i < height * width; ++i)
	{
		Geometry::Internal::InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
	}
	for (int z = 0; z < height - 1; ++z)
	{
		int offset = z * width;
		for (int x = 0; x < width; x += 2)
		{
			int idx = offset + x;
			meshData.indexVec.push_back(idx + 1);
			meshData.indexVec.push_back(idx);
			meshData.indexVec.push_back(idx + width);
			//meshData.indexVec.push_back(idx + width);
			//meshData.indexVec.push_back(idx + 1);
			//meshData.indexVec.push_back(idx + width + 1);
		}
	}
	return meshData;
}