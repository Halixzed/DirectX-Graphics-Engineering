#pragma once
#include "DirectXFramework.h"

class DirectXApp : public DirectXFramework
{
public:
	void CreateSceneGraph();
	void UpdateSceneGraph();

	float _rotationAngle{ 0 };
	float _yOffset{ 0 };
	float _boxOffset{ 0 };
	bool _isGoingUp;

};

