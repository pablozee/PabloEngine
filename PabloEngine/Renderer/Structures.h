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
	ID3D12Resource*					vertexBuffer = nullptr;
	D3D12_VERTEX_BUFFER_VIEW		vertexBufferView;
	ID3D12Resource*					indexBuffer = nullptr;
	D3D12_INDEX_BUFFER_VIEW			indexBufferView;

	ID3D12DescriptorHeap*			rtvHeap = nullptr;

	ID3D12Resource*					texture = nullptr;
	ID3D12Resource*					textureUploadResource = nullptr;

	UINT							rtvDescSize = 0;
};

static const D3D12_HEAP_PROPERTIES UploadHeapProperties =
{
	D3D12_HEAP_TYPE_UPLOAD,
	D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
	D3D12_MEMORY_POOL_UNKNOWN,
	0, 0
};

static const D3D12_HEAP_PROPERTIES DefaultHeapProperties =
{
	D3D12_HEAP_TYPE_DEFAULT,
	D3D12_CPU_PAGE_PROPERTY_UNKNOWN,
	D3D12_MEMORY_POOL_UNKNOWN,
	0, 0
};