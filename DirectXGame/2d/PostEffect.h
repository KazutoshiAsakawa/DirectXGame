#pragma once
#include "Sprite.h"
//#include "DirectXCommon.h"
class PostEffect :
	public Sprite
{
public:
	PostEffect();

	//void Draw(DirectXCommon* dxCom);
	void Draw(ID3D12GraphicsCommandList* cmdList);
};

