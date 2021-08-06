#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN			// Exclude rarely-used items from Windows headers.
#endif

#include <Windows.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <DirectXPackedVector.h>

#include <dxgi1_6.h>
#include <dxc/dxcapi.h>
#include <dxc/dxcapi.use.h>
#include "d3dx12.h"

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <memory>

#include "Renderer/Utils/Utils.h"