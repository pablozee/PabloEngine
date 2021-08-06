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
	IDXGIFactory4*			factory = nullptr;
	IDXGIAdapter1*			adapter = nullptr;
	ID3D12Device5*			device = nullptr;

	int						width = 1280;
	int						height = 960;
	bool					vsync = false;
};

