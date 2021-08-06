#include "CommandQueue.h"

namespace CommandQueue
{
	void Create_Command_Queue(D3D12Global& d3d)
	{
		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

		HRESULT hr = d3d.device->CreateCommandQueue(&desc, IID_PPV_ARGS(&d3d.commandQueue));
		Utils::Validate(hr, L"Error: failed to create command queue!");

#if NAME_D3D_RESOURCES
		d3d.commandQueue->SetName(L"D3D12 Command Queue");
#endif
	}
}