#include "VertexBuffer.h"
#include "Buffer.h"

namespace VertexBuffer
{
	void Create_Vertex_Buffer(D3D12Global& d3d, D3D12Resources& resources, Model& model)
	{
		// Create the vertex buffer resource
		Buffer::D3D12BufferCreateInfo info(((UINT)model.vertices.size() * sizeof(Vertex)), D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_GENERIC_READ);
		Buffer::Create_Buffer(d3d, info, &resources.vertexBuffer);
#if NAME_D3D_RESOURCES
		resources.vertexBuffer->SetName(L"Vertex Buffer");
#endif

		// Copy the vertex data to the vertex buffer
		UINT8* pVertexDataBegin;
		D3D12_RANGE readRange = {};
		HRESULT hr = resources.vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin));
		Utils::Validate(hr, L"Error: failed to map vertex buffer!");

		memcpy(pVertexDataBegin, model.vertices.data(), info.size);
		resources.vertexBuffer->Unmap(0, nullptr);

		// Initialize the vertex buffer view
		resources.vertexBufferView.BufferLocation = resources.vertexBuffer->GetGPUVirtualAddress();
		resources.vertexBufferView.StrideInBytes = sizeof(Vertex);
		resources.vertexBufferView.SizeInBytes = static_cast<UINT>(info.size);
	}
}