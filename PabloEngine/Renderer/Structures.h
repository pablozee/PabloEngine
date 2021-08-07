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
	IDXGIFactory4*					factory = nullptr;
	IDXGIAdapter1*					adapter = nullptr;
	ID3D12Device5*					device = nullptr;
	
	ID3D12GraphicsCommandList4*		commandList = nullptr;
	ID3D12CommandQueue*				commandQueue = nullptr;
	ID3D12CommandAllocator*			commandAllocator[2] = { nullptr, nullptr };

	IDXGISwapChain3*				swapChain = nullptr;
	ID3D12Resource*					backBuffer[2] = { nullptr, nullptr };
	
	ID3D12Fence*					fence = nullptr;
	UINT64							fenceValues[2] = { 0, 0 };
	HANDLE							fenceEvent;
	UINT							frameIndex = 0;

	int								width = 1280;
	int								height = 960;
	bool							vsync = false;
};

struct D3D12Resources
{
	ID3D12DescriptorHeap*			rtvHeap = nullptr;

	UINT							rtvDescSize = 0;
};