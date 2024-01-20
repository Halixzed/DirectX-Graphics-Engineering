#pragma once

#pragma once 
#include "SceneNode.h"
#include "DirectXFramework.h"

class GeometricNode : public SceneNode
{
public:
	GeometricNode(wstring name) : GeometricNode(name, Vector4(0.25f, 0.25f, 0.25f, 1.0f)) {};
	GeometricNode(wstring name, const Vector4 matColour) : SceneNode(name) { _matColour = matColour; };
	~GeometricNode(void) {};
	bool Initialise();
	void Render();
	//virtual void Shutdown() {};


private:

	ComPtr<ID3D11Device>			_device;
	ComPtr<ID3D11DeviceContext>		_deviceContext;
	//ComPtr<ID3D11ShaderResourceView> _texture;
	wstring _shapeName;

	ComPtr<ID3D11Buffer>			_vertexBuffer;
	ComPtr<ID3D11Buffer>			_indexBuffer;

	ComPtr<ID3DBlob>				_vertexShaderByteCode = nullptr;
	ComPtr<ID3DBlob>				_pixelShaderByteCode = nullptr;
	ComPtr<ID3D11VertexShader>		_vertexShader;
	ComPtr<ID3D11PixelShader>		_pixelShader;
	ComPtr<ID3D11InputLayout>		_layout;
	ComPtr<ID3D11Buffer>			_constantBuffer;

	Vector4							_matColour;
	Vector4							_ambientColour;



	void BuildGeometryBuffers();
	void BuildShaders();
	void BuildVertexLayout();
	void BuildConstantBuffer();

};
