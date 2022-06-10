#pragma once
#include"Camera.h"
#include"RenderObject.h"
#include"Model.h"
#include "Common/Tools/tgaimage.h"
#include "Geometry.h"

namespace HelloDX11
{
	typedef Geometry::MeshData<Geometry::VertexPosColor> SimpleMesh;
	class HeightmapSampling
	{

	public:
		HeightmapSampling();
		std::shared_ptr<TGAImage> LoadHeightmapTGA(std::string filename);
		std::shared_ptr<SimpleMesh> RequestLoadedMesh(int x, int y, int level);
		void RequestLoadAsync(int x, int y, int level);
		Model Sample(std::vector<float> heightInfos, int layer=0);
		bool LoadWICTex(std::string filename);
		template<class VertexType, class IndexType = UINT>
		Geometry::MeshData<VertexType, IndexType> LoadAndSample(std::string filename, int level=0);
	private:
		int maxLevel;
		std::vector<std::vector<std::shared_ptr<SimpleMesh>>> loadMaps;
	};

};

using namespace HelloDX11;
using namespace Geometry;


template<class VertexType, class IndexType>
Geometry::MeshData<VertexType, IndexType> HeightmapSampling::LoadAndSample(std::string filename, int level)
{
	using namespace DirectX;
	std::shared_ptr<TGAImage> image = LoadHeightmapTGA(filename);
	UINT width = image->get_width();
	UINT height = image->get_height();
	
	MeshData<VertexType, IndexType> meshData;
	meshData.vertexVec.resize(height * width);
	meshData.indexVec.reserve(height * width*3);
	Geometry::Internal::VertexData* vertexDataArr = new Geometry::Internal::VertexData[height * width];
	for (UINT z = 0; z < height; ++z)
	{
		UINT offset = z * width;
		for (UINT x = 0; x < width; ++x)
		{
			float h = image->get(x, z)[0];
			//先实现一个全三角形的
			int idx = offset + x;
			vertexDataArr[idx].pos = XMFLOAT3(x, h*0.2, z);
			vertexDataArr[idx].color = XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f);

		}
	}
	for (UINT i = 0; i < height * width; ++i)
	{
		Geometry::Internal::InsertVertexElement(meshData.vertexVec[i], vertexDataArr[i]);
	}
	int count = 10;  //for debug
	//meshData.indexVec = { 1,0,width , 1, width ,width+1,2,1,width+1,2,width+1,width+2};
	for (UINT z = 0; z < height - 1; ++z)
	{
		if (count == 0) {
			//break;
		}
		int offset = z * width;
		for (UINT x = 0; x < width - 1; ++x)
		{
			if (count == 0) {
				//break;
			}
			else {
				count--;
			}
			UINT idx = offset + x;
			meshData.indexVec.push_back(idx+1);
			meshData.indexVec.push_back(idx);
			meshData.indexVec.push_back(idx + width);
			meshData.indexVec.push_back(idx + 1);
			meshData.indexVec.push_back(idx + width);
			meshData.indexVec.push_back(idx + width + 1);
		}
	}
	return meshData;
}