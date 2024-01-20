#include "DirectXApp.h"
#include "CubeNode.h"
#include "TexturedCubeNode.h"
#include "GeometricNode.h"
#include "DirectXFramework.h"

DirectXApp app;

Vector3 Camera_Position(0.0f, 20.0f, -90.0f);
Vector3 Focal_Point(0.0f, 0.0f, 0.0f);


void DirectXApp::CreateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();

	//sub-scene graph for teapot
	SceneGraphPointer teapotGraph = make_shared<SceneGraph>(L"TeapotMain");
	sceneGraph->Add(teapotGraph);
	shared_ptr<GeometricNode> teapot01 = make_shared<GeometricNode>(L"Teapot01", Vector4(0, 0, 0.25f, 1.0f));
	teapot01->SetWorldTransform(Matrix::CreateScale(Vector3(2, 2, 2)) * Matrix::CreateTranslation(Vector3(0, 0, 35)));
	teapotGraph->Add(teapot01);

	//sub-scene graph for robot
	SceneGraphPointer bodyGraph = make_shared<SceneGraph>(L"Main");
	sceneGraph->Add(bodyGraph);
	shared_ptr<CubeNode> cube = make_shared<CubeNode>(L"Body", Vector4(0, 0, 0.25f, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(5, 8, 2.5)) * Matrix::CreateTranslation(Vector3(0, 23, 0)));
	bodyGraph->Add(cube);
	cube = make_shared<CubeNode>(L"Left_Leg", Vector4(0.25f, 0, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(1, 7.5, 1)) * Matrix::CreateTranslation(Vector3(-4.0f, 7.5f, 0)));
	bodyGraph->Add(cube);
	cube = make_shared<CubeNode>(L"Right_Leg", Vector4(0.25f, 0, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(1, 7.5, 1)) * Matrix::CreateTranslation(Vector3(4.0f, 7.5f, 0)));
	bodyGraph->Add(cube);
	cube = make_shared<CubeNode>(L"Head", Vector4(0, 0.25f, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(3, 3, 3)) * Matrix::CreateTranslation(Vector3(0, 34, 0)));
	bodyGraph->Add(cube);
	cube = make_shared<CubeNode>(L"Nose", Vector4(0.25f, 0.0f, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(0.6, 0.8, 0.6)) * Matrix::CreateTranslation(Vector3(0, 33, -3)));
	bodyGraph->Add(cube);

	//sub scene graph for robot's arms
	SceneGraphPointer centreSceneGraph = make_shared<SceneGraph>(L"Arms");
	sceneGraph->Add(centreSceneGraph);
	cube = make_shared<CubeNode>(L"Left_Arm", Vector4(0, 0.25f, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(1, 8.5, 1)) * Matrix::CreateTranslation(Vector3(-6, 22, 0)));
	centreSceneGraph->Add(cube);
	cube = make_shared<CubeNode>(L"Right_Arm", Vector4(0, 0.25f, 0, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(1, 8.5, 1)) * Matrix::CreateTranslation(Vector3(6, 22, 0)));
	centreSceneGraph->Add(cube);

	//sub scene graph for textured cube
	SceneGraphPointer test_sceneGraph = GetSceneGraph();
	shared_ptr<TexturedCubeNode> tex_cube = make_shared<TexturedCubeNode>(L"Box", L"Woodbox.bmp");
	tex_cube->SetWorldTransform(Matrix::CreateScale(Vector3(5, 5, 5)) * Matrix::CreateTranslation(Vector3(0, 0, 35)));
	test_sceneGraph->Add(tex_cube);

	//directxframework method to set bg color
	SetBackgroundColour(Vector4(0.1542156899f, 0.124313750f, 0.1319411829f, 1.0f));

	//initializing variables
	_rotationAngle = 0.0f;
	_yOffset = 0.0f;
	_boxOffset = 0.0f;
	_isGoingUp = false;
}


void DirectXApp::UpdateSceneGraph()
{
	SceneGraphPointer sceneGraph = GetSceneGraph();
	_rotationAngle += 0.32f;
	_boxOffset = 20.0f;

	
	SceneNodePointer mainNode = sceneGraph->Find(L"Main");
	SceneNodePointer armsNode = sceneGraph->Find(L"Arms");
	SceneNodePointer texNode = sceneGraph->Find(L"Box");
	SceneNodePointer teapotNode = sceneGraph->Find(L"TeapotMain");

	//sub scene rotation
	mainNode->SetWorldTransform(Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f));
	armsNode->SetWorldTransform(Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f));
	

	//per node transformations
	SceneNodePointer leftArm = armsNode->Find(L"Left_Arm");
	Matrix leftArmTransform = Matrix::CreateScale(Vector3(1, 8.5, 1)) *
		Matrix::CreateTranslation(Vector3(0, -8, 0)) *
		Matrix::CreateRotationX(_rotationAngle * XM_PI / 180.0f) *
		Matrix::CreateTranslation(Vector3(-6, 30, 0));
	leftArm->SetWorldTransform(leftArmTransform);

	
	SceneNodePointer rightArm = armsNode->Find(L"Right_Arm");
	Matrix rightArmTransform = Matrix::CreateScale(Vector3(1, 8.5, 1)) *
		Matrix::CreateTranslation(Vector3(0, -8 ,0)) *
		Matrix::CreateRotationX(_rotationAngle * XM_PI / -180.0f) *
		Matrix::CreateTranslation(Vector3(6, 30, 0));
	rightArm->SetWorldTransform(rightArmTransform);

	SceneNodePointer texBox = texNode->Find(L"Box");
	Matrix texBoxTransform = Matrix::CreateScale(Vector3(5, 5, 5)) * 
		Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f) * 
		Matrix::CreateTranslation(Vector3(-40, 25, 0));      
	texBox->SetWorldTransform(texBoxTransform);

	SceneNodePointer teapot = teapotNode->Find(L"Teapot01");
	Matrix teapotTransform = Matrix::CreateScale(Vector3(2, 2, 2)) * 
		Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f) *
		Matrix::CreateTranslation(Vector3(40, 25, 0));      
	teapot->SetWorldTransform(teapotTransform);
}








