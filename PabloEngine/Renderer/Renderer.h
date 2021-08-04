#pragma once

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"
#include <array>
#include <vector>
#include <unordered_map>
#include <memory>

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

	bool Get4xMsaaState() const;
	void Set4xMsaaState(bool value) const;

	bool Initialize();
	void OnResize();
	void Update(const GameTimer& gt);
	void Draw(const GameTimer& gt);

	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	
protected:
	Renderer(const Renderer& rhs) = delete;
	Renderer& operator=(const Renderer& rhs) = delete;

	void CreateRtvAndDsvDescriptorHeaps();

	bool InitDirect3D();
	void CreateCommandObjects();
	void CreateSwapChain();

	void FlushCommandQueue();

	ID3D12Resource* CurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepethStencilView() const;

	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

	// Set true to use $X MSAA
	bool m_4xMsaaState = false;
	UINT m_4xMsaaQuality = 0;

	ComPtr<IDXGIFactory4> m_DxgiFactory;
	ComPtr<IDXGISwapChain> m_SwapChain;
	ComPtr<ID3D12Device> m_Device;

	ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_CurrentFence = 0;

	ComPtr<ID3D12CommandQueue> m_CommandQueue;
	ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	static const int SwapChainBufferCount = 2;
	int m_CurrentBackBuffer = 0;
	ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
	ComPtr<ID3D12Resource> m_DepthStencilBuffer;

	ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

	D3D12_VIEWPORT m_ScreenViewport;
	D3D12_RECT m_ScissorRect;

	UINT m_RtvDescriptorSize = 0;
	UINT m_DsvDescriptorSize = 0;
	UINT m_CbvSrvUavDescriptorSize = 0;

	D3D_DRIVER_TYPE m_D3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT m_BackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT m_DepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int m_ClientWidth = 800;
	int m_ClientHeight = 600;

private:
	void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	void LoadTextures();
	void BuildRootSignature();
	void BuildDescriptorHeaps();
	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void BuildRenderItems();
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:
	std::vector<std::unique_ptr<FrameResource>> m_FrameResources;
	FrameResource* m_CurrentFrameResource = nullptr;
	int m_CurrentFrameResourceIndex = 0;

	UINT m_CbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> m_RootSignature = nullptr;

	ComPtr<ID3D12DescriptorHeap> m_SrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>	m_Geometries;
	std::unordered_map<std::string, std::unique_ptr<Material>>		m_Materials;
	std::unordered_map<std::string, std::unique_ptr<Texture>>		m_Textures;
	std::unordered_map<std::string, ComPtr<ID3DBlob>>				m_Shaders;
	std::unordered_map<std::string, ComPtr<ID3D12PipelineState>>	m_PSOs;

	std::vector<D3D12_INPUT_ELEMENT_DESC> m_InputLayout;

	std::vector<std::unique_ptr<RenderItem>> m_AllRenderItems;

	std::vector<RenderItem*> m_OpaqueRenderItems;

	PassConstants m_MainPassCB;

	XMFLOAT3 m_EyePos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT4X4 m_View = MathHelper::Identity4x4();
	XMFLOAT4X4 m_Proj = MathHelper::Identity4x4();

	float m_Theta = 1.5f * XM_PI;
	float m_Phi = 0.2f * XM_PI;
	float m_Radius = 15.0f;

	POINT mLastMousePos;
};