// load heightmaps and sampling
#include "pch.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <cerrno>
#include <debugapi.h>
#include "HeightmapSampling.h"
using namespace HelloDX11;

std::shared_ptr<TGAImage> HeightmapSampling::LoadHeightmapTGA(std::string filename)
{
	std::shared_ptr<TGAImage> image = std::make_shared<TGAImage>(225,225,TGAImage::GRAYSCALE);
	//image->read_tga_file(filename.c_str());
	std::ifstream in;
	try
	{
		auto platformPath = Windows::Storage::ApplicationData::Current->RoamingFolder->Path;
		std::wstring platformPathW(platformPath->Begin());
		std::string convertedPlatformPath(platformPathW.begin(), platformPathW.end());
		filename = convertedPlatformPath + filename;
		char* res = strerror(errno);
		in.open(filename, std::ios::binary|std::ifstream::in); 
		res = strerror(errno);
		if (!in)
			throw std::system_error(errno, std::system_category(), "failed to open file");
	}
	catch (const std::exception& e)
	{
		std::filesystem::path cwd = std::filesystem::current_path();
		std::cout << cwd.string() << std::endl;
		const char* ee = e.what();
		char* res = strerror(errno);
		std::cout << e.what() << std::endl;

	}
	return image;
}

std::vector<float> HeightmapSampling::LoadHeightmapRAW(std::string filename)
{
	std::vector<float> heightInfos;
	std::ifstream inFile;
	//�����Ʒ�ʽ���ļ�
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
	//�ļ�ָ���ƶ���ĩβ
	inFile.seekg(0, std::ios::end);
	//��СΪ��ǰ��������С
	std::vector<BYTE> inData(inFile.tellg());
	//�ļ�ָ���ƶ�����ͷ
	inFile.seekg(std::ios::beg);
	//��ȡ�߶���Ϣ
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
//Model HeightmapSampling::Sample(std::vector<float> heightInfos, int layer)  // ��Ҫ���ɶ��㷨�ߡ�uv��
//{
//	return NULL;
//}
//Model HeightmapSampling::LoadAndSample(std::string filename, int layer)
//{
//	return NULL;
//}