#include "TexturedCubeNode.h"
#include "Geometry.h"
#include "WICTextureLoader.h"



bool TexturedCubeNode::Initialise()
{
	_device = DirectXFramework::GetDXFramework()->GetDevice();
	_deviceContext = DirectXFramework::GetDXFramework()->GetDeviceContext();
	if (_device.Get() == nullptr || _deviceContext.Get() == nullptr)
	{
		return false;
	}

	BuildVertexNormals();
	BuildGeometryBuffers();
	BuildShaders();
	BuildVertexLayout();
	BuildConstantBuffer();
	BuildTexture();
	return true;

}


void TexturedCubeNode::Render()
{
	// Calculate the world x view x projection transformation 
	Matrix projectionTransformation = DirectXFramework::GetDXFramework()->GetProjectionTransformation();
	Matrix viewTransformation = DirectXFramework::GetDXFramework()->GetViewTransformation();

	Matrix _completeTransformation = _cumulativeWorldTransformation * viewTransformation * projectionTransformation;

	CBuffer constantBuffer;
	constantBuffer.World = _completeTransformation;
	constantBuffer.WorldViewProjection = _cumulativeWorldTransformation * viewTransformation * projectionTransformation;
	constantBuffer.MaterialColour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	//constantBuffer.AmbientLightColour = _ambientColour;
	constantBuffer.AmbientLightColour = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	constantBuffer.DirectionalLightVector = Vector4(-1.0f, -1.0f, 1.0f, 0.0f);
	constantBuffer.DirectionalLightColour = Vector4(Colors::Gold);
	constantBuffer.specColour = Vector4(Colors::White);

	constantBuffer.specularPower = 8.0f;


	// Update the constant buffer. Note the layout of the constant buffer must match that in the shader
	_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
	_deviceContext->PSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
	_deviceContext->UpdateSubresource(_constantBuffer.Get(), 0, 0, &constantBuffer, 0, 0);

	_deviceContext->PSSetShaderResources(0, 1, _texture.GetAddressOf());

	// Now render the cube
	// Specify the distance between vertices and the starting point in the vertex buffer
	UINT stride = sizeof(ObjectVertexStruct);
	UINT offset = 0;

	// Set the vertex buffer and index buffer we are going to use
	_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);


	// Specify the layout of the polygons (it will rarely be different to this)
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Specify the layout of the input vertices.  This must match the layout of the input vertices in the shader
	_deviceContext->IASetInputLayout(_layout.Get());

	// Specify the vertex and pixel shaders we are going to use
	_deviceContext->VSSetShader(_vertexShader.Get(), 0, 0);
	_deviceContext->PSSetShader(_pixelShader.Get(), 0, 0);

	// Now draw the first cube
	_deviceContext->DrawIndexed(ARRAYSIZE(_texIndices), 0, 0);

}

void TexturedCubeNode::BuildGeometryBuffers()
{
	// This method uses the arrays defined in Geometry.h
	// 
	// Setup the structure that specifies how big the vertex 
	// buffer should be
	D3D11_BUFFER_DESC vertexBufferDescriptor = { 0 };
	vertexBufferDescriptor.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDescriptor.ByteWidth = sizeof(ObjectVertexStruct) * ARRAYSIZE(_texVertices);
	vertexBufferDescriptor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescriptor.CPUAccessFlags = 0;
	vertexBufferDescriptor.MiscFlags = 0;
	vertexBufferDescriptor.StructureByteStride = 0;

	// Now set up a structure that tells DirectX where to get the
	// data for the vertices from
	D3D11_SUBRESOURCE_DATA vertexInitialisationData = { 0 };
	vertexInitialisationData.pSysMem = &_texVertices;

	// and create the vertex buffer
	ThrowIfFailed(_device->CreateBuffer(&vertexBufferDescriptor, &vertexInitialisationData, _vertexBuffer.GetAddressOf()));

	// Setup the structure that specifies how big the index 
	// buffer should be
	D3D11_BUFFER_DESC indexBufferDescriptor = { 0 };
	indexBufferDescriptor.Usage = D3D11_USAGE_IMMUTABLE;
	indexBufferDescriptor.ByteWidth = sizeof(UINT) * ARRAYSIZE(_texIndices);
	indexBufferDescriptor.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDescriptor.CPUAccessFlags = 0;
	indexBufferDescriptor.MiscFlags = 0;
	indexBufferDescriptor.StructureByteStride = 0;

	// Now set up a structure that tells DirectX where to get the
	// data for the indices from
	D3D11_SUBRESOURCE_DATA indexInitialisationData;
	indexInitialisationData.pSysMem = &_texIndices;

	// and create the index buffer
	ThrowIfFailed(_device->CreateBuffer(&indexBufferDescriptor, &indexInitialisationData, _indexBuffer.GetAddressOf()));

}


void TexturedCubeNode::BuildShaders()
{
	DWORD shaderCompileFlags = 0;
#if defined( _DEBUG )
	shaderCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ComPtr<ID3DBlob> compilationMessages = nullptr;

	//Compile vertex shader
	HRESULT hr = D3DCompileFromFile(TexturedShaderFileName,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		VertexShaderName, "vs_5_0",
		shaderCompileFlags, 0,
		_vertexShaderByteCode.GetAddressOf(),
		compilationMessages.GetAddressOf());

	if (compilationMessages.Get() != nullptr)
	{
		// If there were any compilation messages, display them
		MessageBoxA(0, (char*)compilationMessages->GetBufferPointer(), 0, 0);
	}
	// Even if there are no compiler messages, check to make sure there were no other errors.
	ThrowIfFailed(hr);
	ThrowIfFailed(_device->CreateVertexShader(_vertexShaderByteCode->GetBufferPointer(), _vertexShaderByteCode->GetBufferSize(), NULL, _vertexShader.GetAddressOf()));

	// Compile pixel shader
	hr = D3DCompileFromFile(TexturedShaderFileName,
		nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		PixelShaderName, "ps_5_0",
		shaderCompileFlags, 0,
		_pixelShaderByteCode.GetAddressOf(),
		compilationMessages.GetAddressOf());

	if (compilationMessages.Get() != nullptr)
	{
		// If there were any compilation messages, display them
		MessageBoxA(0, (char*)compilationMessages->GetBufferPointer(), 0, 0);
	}
	ThrowIfFailed(hr);
	ThrowIfFailed(_device->CreatePixelShader(_pixelShaderByteCode->GetBufferPointer(), _pixelShaderByteCode->GetBufferSize(), NULL, _pixelShader.GetAddressOf()));
}

void TexturedCubeNode::BuildVertexLayout()
{
	// Create the vertex input layout. This tells DirectX the format
	// of each of the vertices we are sending to it. The vertexDesc array is
	// defined in Geometry.h

	ThrowIfFailed(_device->CreateInputLayout(vertexDesc, ARRAYSIZE(vertexDesc), _vertexShaderByteCode->GetBufferPointer(), _vertexShaderByteCode->GetBufferSize(), _layout.GetAddressOf()));
}

void TexturedCubeNode::BuildConstantBuffer()
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(CBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	ThrowIfFailed(_device->CreateBuffer(&bufferDesc, NULL, _constantBuffer.GetAddressOf()));
}

void TexturedCubeNode::BuildVertexNormals()
{
	// Create an array for contributing counts
	std::vector<int>contributingCounts(ARRAYSIZE(_texVertices), 0);
	//int contributingCounts[ARRAYSIZE(vertices)] = { 0 };

	// Loop through polygons
	for (size_t i = 0; i < (ARRAYSIZE(_texIndices)); i += 3)
	{
		//calc the normal for polygon
		// Get the 3 indices of the vertices that make up the polygon
		UINT index0 = _texIndices[i];
		UINT index1 = _texIndices[i + 1];
		UINT index2 = _texIndices[i + 2];


		// Get the vertices for those indices

		Vector3 vertex0 = _texVertices[index0].Position;
		Vector3 vertex1 = _texVertices[index1].Position;
		Vector3 vertex2 = _texVertices[index2].Position;
		//XMVECTOR point1 = XMVectorSet(vertex1.Position.x, vertex1.Pos.y, vertex1.Pos.z, 0.0f);

		// Calculate the polygon normal

		Vector3 vectorA = vertex1 - vertex0;
		Vector3 vectorB = vertex2 - vertex0;

		//Vector3 vectorB = vertex2 - vertex0;

		// Calculate the cross product of vectorA and vectorB to get the normal
		Vector3 polygonNormal = vectorA.Cross(vectorB);




		// Add the polygon normal to the vertex normal for each of the 3 vertices
		_texVertices[index0].Normal += polygonNormal;
		_texVertices[index1].Normal += polygonNormal;
		_texVertices[index2].Normal += polygonNormal;

		// Add 1 to the contributing count for each of the vertices
		contributingCounts[index0] += 1;
		contributingCounts[index1] += 1;
		contributingCounts[index2] += 1;
	}

	// Loop through vertices
	for (size_t i = 0; i < ARRAYSIZE(_texVertices); i += 1)
	{
		if (contributingCounts[i] > 0)
		{
			_texVertices[i].Normal /= (contributingCounts[i]);
			_texVertices[i].Normal.Normalize();
		}
		// Divide the summed vertex normals by the number of times they were contributed to
		// Normalize the resulting normal vector

	}
}


void TexturedCubeNode::BuildTexture()
{
	// Note that in order to use CreateWICTextureFromFile, we 
	// need to ensure we make a call to CoInitializeEx in our 
	// Initialise method (and make the corresponding call to 
	// CoUninitialize in the Shutdown method).  Otherwise, 
	// the following call will throw an exception
	ThrowIfFailed(CreateWICTextureFromFile(_device.Get(),
		_deviceContext.Get(),
		_texturename.c_str(),
		nullptr,
		_texture.GetAddressOf()
	));
}