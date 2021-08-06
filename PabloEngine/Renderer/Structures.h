#pragma once
#include <Windows.h>
#include <string>

struct ConfigInfo
{
	int width				= 640;
	int height				= 360;
	bool vsync				= false;
	std::string model		= "";
	HINSTANCE instance		= NULL;
};

struct D3D12Global
{
	int width				= 1280;
	int height				= 960;
	bool vsync				= false;

};

