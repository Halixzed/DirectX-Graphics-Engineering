#pragma once
//--------------------------------------------------------------------------------------
// File: GeometricObject.h
//
// Adapted from files in the Microsoft DirectX Toolkit to use the SimpleMath library
// and simplify the usage.  
// 
// Normals are always returned set to (0, 0, 0) since it is expected that the normals 
// will be calculated.
// 
// Parts copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//
//--------------------------------------------------------------------------------------

#include "SimpleMath.h"
#include <vector>

using namespace std;
using namespace DirectX;
using namespace SimpleMath;

// Structure of a single vertex for all vertices generated by these functions.  This must match the
// structure of the input vertex in the shader

struct GeoStruct
{
    Vector3		Position;
    Vector3		Normal;
};

//--------------------------------------------------------------------------------------------------------
// ComputeBox
//
// Input Parameters:
//
// vertices         : A reference to a vector of ObjectVertexStruct structures.  This will be populated with the vertices for the box.
// indices          : A reference to a vector of unsigned ints.  This will be populated with the indices for the box.
// size             : A reference to a Vector3 containing the size of the box requested in the X, Y and Z dimensions.
//
// Output Parameters:
//
// vertices         : This contains the vertices for the box.
// indices          : This contains the indices for the box
//
//--------------------------------------------------------------------------------------------------------


void ComputeBox(vector<GeoStruct>& vertices, vector<UINT>& indices, const Vector3& size);

//--------------------------------------------------------------------------------------------------------
// ComputeSphere
//
// Input Parameters:
//
// vertices         : A reference to a vector of ObjectVertexStruct structures.  This will be populated with the vertices for the sphere.
// indices          : A reference to a vector of unsigned ints.  This will be populated with the indices for the sphere.
// diameter         : The required diameter of the sphere
// tesselation      : The number of polygons that make up the diameter of the sphere.  Higher numbers give a smoother effect,
//                    but, of course, result in many more vertices.  Must be more than 3.
//
// Output Parameters:
//
// vertices         : This contains the vertices for the sphere.
// indices          : This contains the indices for the sphere.
//
//--------------------------------------------------------------------------------------------------------

void ComputeSphere(vector<GeoStruct>& vertices, vector<UINT>& indices, float diameter, size_t tessellation);

//--------------------------------------------------------------------------------------------------------
// ComputeCylinder
//
// Input Parameters:
//
// vertices         : A reference to a vector of ObjectVertexStruct structures.  This will be populated with the vertices for the cylinder.
// indices          : A reference to a vector of unsigned ints.  This will be populated with the indices for the cylinder.
// height           : The required height of the cylinder
// diameter         : The required diameter of the cylinder
// tesselation      : Defines the smoothness of the cylinder.  Higher numbers give a smoother effect,
//                    but, of course, result in many more vertices.  Must be more than 3.
//
// Output Parameters:
//
// vertices         : This contains the vertices for the cylinder.
// indices          : This contains the indices for the cylinder.
//
//--------------------------------------------------------------------------------------------------------

void ComputeCylinder(vector<GeoStruct>& vertices, vector<UINT>& indices, float height, float diameter, size_t tessellation);

//--------------------------------------------------------------------------------------------------------
// ComputeCone
//
// Input Parameters:
//
// vertices         : A reference to a vector of ObjectVertexStruct structures.  This will be populated with the vertices for the cone.
// indices          : A reference to a vector of unsigned ints.  This will be populated with the indices for the cone.
// diameter         : The required diameter of the base of the cone
// height           : The required height of the cone
// tesselation      : Defines the smoothness of the cone.  Higher numbers give a smoother effect,
//                    but, of course, result in many more vertices.  Must be more than 3.
//
// Output Parameters:
//
// vertices         : This contains the vertices for the cone.
// indices          : This contains the indices for the cone.
//
//--------------------------------------------------------------------------------------------------------

void ComputeCone(vector<GeoStruct>& vertices, vector<UINT>& indices, float diameter, float height, size_t tessellation);

//--------------------------------------------------------------------------------------------------------
// ComputeTeapot.  Generate the model of a teapot.
//
// Input Parameters:
//
// vertices         : A reference to a vector of ObjectVertexStruct structures.  This will be populated with the vertices for the teapot.
// indices          : A reference to a vector of unsigned ints.  This will be populated with the indices for the teapot.
// size             : The size of the teapot in all dimensions.
//
// Output Parameters:
//
// vertices         : This contains the vertices for the teapot.
// indices          : This contains the indices for the teapot.
//
//--------------------------------------------------------------------------------------------------------

void ComputeTeapot(vector<GeoStruct>& vertices, vector<UINT>& indices, float size);

void CalculateNormals(vector<GeoStruct>& vertices, vector<UINT>& indices);
