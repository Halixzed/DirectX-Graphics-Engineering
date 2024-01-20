#pragma once 
#include "SceneNode.h"
#include "DirectXFramework.h"

class TexturedCubeNode : public SceneNode
{
public:
	TexturedCubeNode(wstring name, wstring texturename) : TexturedCubeNode(name, Vector4(0.25f, 0.25f, 0.25f, 1.0f), texturename) {};
	TexturedCubeNode(wstring name, const Vector4 ambientColour, wstring texturename) : SceneNode(name), _ambientColour(ambientColour), _texturename(texturename) {};
	~TexturedCubeNode(void) {};
	bool Initialise();
	void Render();
	//virtual void Shutdown() {};


private:

	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;
	ComPtr<ID3D11ShaderResourceView> _texture;
	wstring _texturename;

	ComPtr<ID3D11Buffer>			_vertexBuffer;
	ComPtr<ID3D11Buffer>			_indexBuffer;

	ComPtr<ID3DBlob>				_vertexShaderByteCode = nullptr;
	ComPtr<ID3DBlob>				_pixelShaderByteCode = nullptr;
	ComPtr<ID3D11VertexShader>		_vertexShader;
	ComPtr<ID3D11PixelShader>		_pixelShader;
	ComPtr<ID3D11InputLayout>		_layout;
	ComPtr<ID3D11Buffer>			_constantBuffer;

	Vector4							_ambientColour;



	void BuildVertexNormals();
	void BuildGeometryBuffers();
	void BuildShaders();
	void BuildVertexLayout();
	void BuildConstantBuffer();
	void BuildTexture();

};
