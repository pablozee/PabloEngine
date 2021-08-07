#include "RTVDescriptorHeap.h"

namespace RTVDescriptorHeaps
{
	void Create_RTV_Descriptor_Heaps(D3D12Global& d3d, D3D12Resources &resources)
	{
		// Describe the RTV descriptor heap
		D3D12_DESCRIPTOR_HEAP_DESC rtvDesc = {};
		rtvDesc.NumDescriptors = 2;
		rtvDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		// Create the RTV heap
		HRESULT hr = d3d.device->CreateDescriptorHeap(&rtvDesc, IID_PPV_ARGS(&resources.rtvHeap));
		Utils::Validate(hr, L"Error: failed to create RTV descriptor heap!");

#if NAME_D3D_RESOURCES
		resources.rtvHeap->SetName(L"RTV Descriptor Heap");
#endif

		resources.rtvDescSize = d3d.device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}
}