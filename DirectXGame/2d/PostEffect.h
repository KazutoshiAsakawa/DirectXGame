#pragma once
#include "Sprite.h"
//#include "DirectXCommon.h"
class PostEffect :
	public Sprite
{
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	static const float clearColor[4];

	PostEffect();

	/// <summary>
	/// 初期化
	/// <summary>
	void Initialize();

	//void Draw(DirectXCommon* dxCom);
	void Draw(ID3D12GraphicsCommandList* cmdList);


	/// <summary>
	/// シーン描画前処理
	/// <summary>
	/// <param name = "cmdlist">コマンドリスト</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// シーン描画後処理
	/// <summary>
	/// <param name = "cmdlist">コマンドリスト</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// パイプライン生成
	/// </summary>
	void CreateGraphicsPipelineState();

private: // メンバ変数
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff;
	// SRV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;

	// 深度バッファ
	ComPtr<ID3D12Resource> depthBuff;
	// RTV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	// DSV用デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;

	// グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> pipelineState;
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
};

