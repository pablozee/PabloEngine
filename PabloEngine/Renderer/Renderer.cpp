#include "Renderer.h"
#include "Utils/Utils.h"

void Renderer::Init(ConfigInfo& info, HWND window)
{
	d3d.width = 1280;
	d3d.height = 960;
	d3d.vsync = false;

	Utils::LoadModel("Models/cinema.obj", model, material);
	
	D3DShaders::Init_Shader_Compiler(shaderCompiler);

	Device::Create_Device(d3d);

	CommandQueue::Create_Command_Queue(d3d);
	CommandAllocator::Create_Command_Allocator(d3d);

	Fence::Create_Fence(d3d);

	SwapChain::Create_SwapChain(d3d, window);

	CommandList::Create_Command_List(d3d);
	CommandList::Reset_Command_List(d3d);

	RTVDescriptorHeaps::Create_RTV_Descriptor_Heaps(d3d, resources);
	BackBufferRTV::Create_BackBuffer_RTV(d3d, resources);

	VertexBuffer::Create_Vertex_Buffer(d3d, resources, model);
	IndexBuffer::Create_Index_Buffer(d3d, resources, model);


}