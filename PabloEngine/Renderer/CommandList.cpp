#include "CommandList.h"

namespace CommandList
{
	void Create_Command_List(D3D12Global& d3d)
	{
		HRESULT hr = d3d.device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, d3d.commandAllocator[d3d.frameIndex], nullptr, IID_PPV_ARGS(&d3d.commandList));
		hr = d3d.commandList->Close();
		Utils::Validate(hr, L"Error: failed to create the command list!");

#if NAME_D3D_RESOURCES
		d3d.commandList->SetName(L"D3D12 Command List");
#endif
	}

	void Reset_Command_List(D3D12Global& d3d)
	{
		// Reset the commnad allocator for the current frame
		HRESULT hr = d3d.commandAllocator[d3d.frameIndex]->Reset();
		Utils::Validate(hr, L"Error: failed to reset command allocator!");

		// Reset the command list for the current frame
		hr = d3d.commandList->Reset(d3d.commandAllocator[d3d.frameIndex], nullptr);
		Utils::Validate(hr, L"Error: failed to reset command list!");
	}
}