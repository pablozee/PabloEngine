#pragma once

#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

using namespace Microsoft::WRL;

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

	::ComPtr<IDXGIFactory4> m_DxgiFactory;
	::ComPtr<IDXGISwapChain> m_SwapChain;
	::ComPtr<ID3D12Device> m_Device;

	::ComPtr<ID3D12Fence> m_Fence;
	UINT64 m_CurrentFence = 0;

	::ComPtr<ID3D12CommandQueue> m_CommandQueue;
	::ComPtr<ID3D12CommandAllocator> m_DirectCmdListAlloc;
	::ComPtr<ID3D12GraphicsCommandList> m_CommandList;

	static const int SwapChainBufferCount = 2;
	int m_CurrentBackBuffer = 0;
	::ComPtr<ID3D12Resource> m_SwapChainBuffer[SwapChainBufferCount];
	::ComPtr<ID3D12Resource> m_DepthStencilBuffer;

	::ComPtr<ID3D12DescriptorHeap> m_RtvHeap;
	::ComPtr<ID3D12DescriptorHeap> m_DsvHeap;

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
};