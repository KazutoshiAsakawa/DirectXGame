#include "FbxLoader.h"
#include "GameScene.h"
#include "Object3d.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	//safe_delete(spriteBG);
	//safe_delete(lightGroup);
	////safe_delete(object1);
	//safe_delete(model1);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// カメラ生成
	camera.reset(new DebugCamera(WinApp::window_width, WinApp::window_height, input));

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	constexpr UINT bgTexNum = 1;
	if (!Sprite::LoadTexture(bgTexNum, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG.reset(Sprite::Create(bgTexNum, { 0.0f,0.0f }));
	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera.get());

	// テクスチャ2番に読み込み
	constexpr UINT tex1TexNum = 2;
	Sprite::LoadTexture(tex1TexNum, L"Resources/tex1.png");

	// ライト生成
	lightGroup.reset(LightGroup::Create());

	// カメラ注視点をセット
	/*camera->SetTarget({ 0, 20, 0 });
	camera->SetDistance(50.0f);*/
	// カメラ注視点をセット
	camera->SetTarget({ 0,2.5f,0 });
	camera->SetDistance(8.0f);


	// モデル名を指定してファイル読み込み
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("cube");
	// モデル名を指定してファイル読み込み
	model1.reset(FbxLoader::GetInstance()->LoadModelFromFile("boneTest"));

	// デバイスをセット
	Object3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	Object3d::SetCamera(camera.get());
	// グラフィックスパイプライン生成
	Object3d::CreateGraphicsPipeline();

	// 3Dオブジェクト生成とモデルのセット
	object1.reset(new Object3d());
	object1->Initialize();
	object1->SetModel(model1.get());
	object1->PlayAnimation();
	object1->SetRotation({ 0,90,0 });
}

void GameScene::Update()
{
	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	object1->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	object1->Draw(cmdList);

	// パーティクルの描画
	particleMan->Draw(cmdList);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// デバッグテキストの描画
	debugText->DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}