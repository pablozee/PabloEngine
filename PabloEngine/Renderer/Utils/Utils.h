#pragma once
#include <Windows.h>
#include "Renderer/Model.h"
#include "Renderer/Texture.h"

namespace Utils
{
	void LoadModel(std::string filepath, Model& model, Material& material);

	void Validate(HRESULT hr, LPWSTR message);
	
//	Texture::TextureInfo LoadTexture(std::string filepath);
}
