#pragma once
#include "Sprite.h"
//#include "DirectXCommon.h"
class PostEffect
{
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	/// <summary>
		/// 頂点データ構造体
		/// </summary>
	struct VertexPosUv
	{
		DirectX::XMFLOAT3 pos; // xyz座標
		DirectX::XMFLOAT2 uv;  // uv座標
	};
	/// <summary>
	/// 定数バッファ用データ構造体
	/// </summary>
	struct ConstBufferData
	{
		DirectX::XMFLOAT4 color;	// 色 (RGBA)
		DirectX::XMMATRIX mat;	// ３Ｄ変換行列
	};

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

	static void SetDevice(ID3D12Device* device);

private: // メンバ変数
	static ID3D12Device* device_;

	// テクスチャバッファ
	ComPtr<ID3D12Resource> texBuff[2];
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

	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// ワールド行列
	DirectX::XMMATRIX matWorld{};
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	DirectX::XMFLOAT2 position{};
	// 色
	DirectX::XMFLOAT4 color = { 1, 1, 1, 1 };
};

