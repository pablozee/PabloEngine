#pragma once
#include <Windows.h>
#include <DirectXMath.h>
#include <vector>
#include <string>

using namespace DirectX;

static bool CompareVector3WithEpsilon(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
{
	const XMFLOAT3 vector3Epsilon = XMFLOAT3(0.00001f, 0.00001f, 0.00001f);
	return XMVector3NearEqual(XMLoadFloat3(&lhs), XMLoadFloat3(&rhs), XMLoadFloat3(&vector3Epsilon)) == TRUE;
}

static bool CompareVector2WithEpsilon(const XMFLOAT2& lhs, const XMFLOAT2& rhs)
{
	const XMFLOAT2 vector2Epsilon = XMFLOAT2(0.00001f, 0.00001f);
	return XMVector3NearEqual(XMLoadFloat2(&lhs), XMLoadFloat2(&rhs), XMLoadFloat2(&vector2Epsilon)) == TRUE;
}

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT2 uv;

	bool operator==(const Vertex& v) const
	{
		if (CompareVector3WithEpsilon(position, v.position))
		{
			if (CompareVector2WithEpsilon(uv, v.uv)) return true;
			return true;
		}
		return false;
	}

	Vertex& operator=(const Vertex& v)
	{
		position = v.position;
		uv = v.uv;
		return *this;
	}
};

struct Model
{
	std::vector<Vertex>		vertices;
	std::vector<uint32_t>	indices;
};

struct Material
{
	std::string name		= "defaultMaterial";
	std::string texturePath = "";
	float textureResolution = 512;
};