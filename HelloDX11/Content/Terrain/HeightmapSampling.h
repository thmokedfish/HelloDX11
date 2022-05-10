#pragma once
#include"Camera.h"
#include"RenderObject.h"
#include"Model.h"
#include "Common/Tools/tgaimage.h"

namespace HelloDX11
{
	class HeightmapSampling
	{
	public:
		HeightmapSampling() {};
		std::shared_ptr<TGAImage> LoadHeightmapTGA(std::string filename);
		//std::vector<float> LoadHeightmapTGA(std::string filename);
		std::vector<float> LoadHeightmapRAW(std::string filename);
		Model Sample(std::vector<float> heightInfos, int layer=0);  // ��Ҫ���ɶ��㷨�ߡ�uv��
		Model LoadAndSample(std::string filename, int layer = 0);  
		
	};
};