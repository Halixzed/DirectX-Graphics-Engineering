#pragma once

#define ShaderFileName		L"shader.hlsl"
#define TexturedShaderFileName   L"TexturedShader.hlsl"
#define VertexShaderName	"VS"
#define PixelShaderName		"PS"
#define TextureName         "Woodbox.bmp"

struct CBuffer
{
    Matrix  WorldViewProjection;
    Matrix  World;
    Vector4 MaterialColour;
    Vector4 AmbientLightColour;
    Vector4 DirectionalLightColour;
    Vector4 DirectionalLightVector;
	Vector4 specColour;
	float specularPower;
	Vector3 pad;

};

struct ObjectVertexStruct {
    Vector3 Position;
    Vector3 Normal;
    Vector2	TextureCoordinate;
};


static D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
{
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }

};

//placeholder mesh data; will be updating progressively
static ObjectVertexStruct _texVertices[] =
{
    { Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 1
    { Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },

    { Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 2
    { Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },

    { Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 3
    { Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },

    { Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 4
    { Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },

    { Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 5
    { Vector3(1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) },

    { Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f) },    // side 6
    { Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f) },
    { Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f) },
    { Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f) }
};

static UINT _texIndices[] = {
			0, 1, 2,       // side 1
			2, 1, 3,
			4, 5, 6,       // side 2
			6, 5, 7,
			8, 9, 10,      // side 3
			10, 9, 11,
			12, 13, 14,    // side 4
			14, 13, 15,
			16, 17, 18,    // side 5
			18, 17, 19,
			20, 21, 22,    // side 6
			22, 21, 23,
};

static ObjectVertexStruct vertices[] =
{
	{ Vector3(-1.0f, -1.0f, 1.0f),  Vector3(0.0f, 0.0f, 0.0f),},    // side 1
	{ Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(-1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),},

	{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f),},    // side 2
	{ Vector3(-1.0f, 1.0f, -1.0f) ,Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, 1.0f, -1.0f) , Vector3(0.0f, 0.0f, 0.0f),},

	{ Vector3(-1.0f, 1.0f, -1.0f) ,Vector3(0.0f, 0.0f, 0.0f),},    // side 3
	{ Vector3(-1.0f, 1.0f, 1.0f) , Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, 1.0f, -1.0f) ,Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, 1.0f, 1.0f),Vector3(0.0f, 0.0f, 0.0f),},

	{ Vector3(-1.0f, -1.0f, -1.0f) , Vector3(0.0f, 0.0f, 0.0f),},    // side 4
	{ Vector3(1.0f, -1.0f, -1.0f) ,Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(-1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, -1.0f, 1.0f) , Vector3(0.0f, 0.0f, 0.0f),},

	{ Vector3(1.0f, -1.0f, -1.0f) , Vector3(0.0f, 0.0f, 0.0f),},    // side 5
	{ Vector3(1.0f, 1.0f, -1.0f) , Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, -1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(1.0f, 1.0f, 1.0f) , Vector3(0.0f, 0.0f, 0.0f)},

	{ Vector3(-1.0f, -1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f),},    // side 6
	{ Vector3(-1.0f, -1.0f, 1.0f) ,Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(-1.0f, 1.0f, -1.0f), Vector3(0.0f, 0.0f, 0.0f),},
	{ Vector3(-1.0f, 1.0f, 1.0f) , Vector3(0.0f, 0.0f, 0.0f),}
};

static UINT indices[] = {
			0, 1, 2,       // side 1
			2, 1, 3,
			4, 5, 6,       // side 2
			6, 5, 7,
			8, 9, 10,      // side 3
			10, 9, 11,
			12, 13, 14,    // side 4
			14, 13, 15,
			16, 17, 18,    // side 5
			18, 17, 19,
			20, 21, 22,    // side 6
			22, 21, 23,
};
 


