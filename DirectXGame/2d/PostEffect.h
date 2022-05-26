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
	/// ������
	/// <summary>
	void Initialize();

	//void Draw(DirectXCommon* dxCom);
	void Draw(ID3D12GraphicsCommandList* cmdList);

private: // �����o�ϐ�
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	// SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
};

