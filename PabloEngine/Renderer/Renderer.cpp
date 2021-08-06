#include "Renderer.h"
#include "Utils/Utils.h"

void Renderer::Init(ConfigInfo& info)
{
	d3d.width = 1280;
	d3d.height = 960;
	d3d.vsync = false;

	Utils::LoadModel("Models/cinema.obj", model, material);
	
	D3DShaders::Init_Shader_Compiler(shaderCompiler);
}