// load heightmaps and sampling
#include "pch.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <cerrno>
#include <debugapi.h>
#include "HeightmapSampling.h"
#include "Common/Tools/WICTextureLoader11.h"
#include "Common/GameManager.h"
#include <ppltasks.h>
#include <format>
using namespace Geometry;
using namespace HelloDX11;

HeightmapSampling::HeightmapSampling():maxLevel(3)
{
	loadMaps.resize(maxLevel);
	for (int i = 0; i < maxLevel; ++i)
	{
		int count= std::pow(4, maxLevel - i);
		loadMaps[i].resize(count);
	}
}

// 同步 取
std::shared_ptr<SimpleMesh> HeightmapSampling::RequestLoadedMesh(int x, int y,int level)
{
	if (level >= loadMaps.size()) 
	{
		return nullptr;
	}
	int width = std::pow(2, maxLevel - level);
	int idx = x * width + y;
	if (idx >= loadMaps[level].size())
	{
		return nullptr;
	}
	return loadMaps[level][idx];
}

void HeightmapSampling::RequestLoadAsync(int x, int y, int level)
{
	std::string filename = "test_texture";
	//std::string filename1 = 
	auto task = Concurrency::create_task([this, filename, level]() {
		this->LoadAndSample<Geometry::VertexPosColor>(filename, level);
		}
	);
	//task.then([this,level](SimpleMesh mesh) {
	//	int idx = 0;
	//	//loadMaps[level][idx] = mesh;
	//	}
	//);
}


std::shared_ptr<TGAImage> HeightmapSampling::LoadHeightmapTGA(std::string filename)
{
	std::shared_ptr<TGAImage> image = std::make_shared<TGAImage>(225, 225, TGAImage::GRAYSCALE);
	image->read_tga_file(filename);
	TGAColor c = image->get(0, 0);
	return image;
}



bool HeightmapSampling::LoadWICTex(std::string filename)
{
	return true;
}

//Model HeightmapSampling::Sample(std::vector<float> heightInfos, int layer)  // 需要生成顶点法线等
//{
//	return NULL;
//}

