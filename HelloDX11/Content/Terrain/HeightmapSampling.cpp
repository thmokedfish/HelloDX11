// load heightmaps and sampling
#include "pch.h"
#include<fstream>
#include <filesystem>
#include<iostream>
#include "HeightmapSampling.h"
using namespace HelloDX11;


std::vector<float> HeightmapSampling::LoadHeightmap(std::string filename)
{
	std::vector<float> heightInfos;
	std::ifstream inFile;
	//二进制方式打开文件
	try
	{
		inFile.open(filename.c_str(), std::ios::binary); 
		if (!inFile)
			throw std::system_error(errno, std::system_category(), "failed to open " + filename);
	}
	catch (const std::exception& e)
	{
		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << cwd.string() << std::endl;
		const char* ee = e.what();
		std::cout << e.what() << std::endl;
		return heightInfos;
	}
	//文件指针移动到末尾
	inFile.seekg(0, std::ios::end);
	//大小为当前缓冲区大小
	std::vector<BYTE> inData(inFile.tellg());
	//文件指针移动到开头
	inFile.seekg(std::ios::beg);
	//读取高度信息
	inFile.read((char*)&inData[0], inData.size());
	inFile.close();

	heightInfos.resize(inData.size());
	for (int i = 0; i < inData.size(); ++i)
	{
		heightInfos[i] = inData[i];
		std::cout << i << " " << heightInfos[i] << std::endl;
	}

	return heightInfos;
}
//Model HeightmapSampling::Sample(std::vector<float> heightInfos, int layer)  // 需要生成顶点法线、uv等
//{
//	return NULL;
//}
//Model HeightmapSampling::LoadAndSample(std::string filename, int layer)
//{
//	return NULL;
//}