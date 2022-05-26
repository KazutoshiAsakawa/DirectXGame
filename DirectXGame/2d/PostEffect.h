#pragma once
#include "Sprite.h"
//#include "DirectXCommon.h"
class PostEffect :
	public Sprite
{
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	PostEffect();

	/// <summary>
	/// 初期化
	/// <summary>
	void Initialize();

	//void Draw(DirectXCommon* dxCom);
	void Draw(ID3D12GraphicsCommandList* cmdList);

private: // メンバ変数
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
};

