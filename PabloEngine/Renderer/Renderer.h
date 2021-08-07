#pragma once

#include "Common.h"

#include "Structures.h"
#include "Model.h"

#include "D3DShaders.h"
#include "Device.h"
#include "CommandQueue.h"
#include "CommandAllocator.h"
#include "Fence.h"
#include "SwapChain.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using Microsoft::WRL::ComPtr;

using namespace DirectX;

class Renderer
{
public:
	Renderer()
	{}

	~Renderer()
	{}

	void Init(ConfigInfo& config, HWND window);

	void Update();

	void Render();

	void Cleanup();

protected:
	Renderer(const Renderer& rhs) = delete;
	Renderer& operator=(const Renderer& rhs) = delete;

	Model model;
	Material material;

//	DXRGlobal dxr = {};
	D3D12Global d3d = {};
//	D3D12Resources resources = {};
	D3D12ShaderCompilerInfo shaderCompiler;
};