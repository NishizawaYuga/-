#pragma once
#include "DirectXCommon.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Input.h"

struct Timer {	//�C�[�W���O�p�f�[�^
	float nowTime;	//�o�ߎ���
	bool beginCount;	//�J�E���g�J�n�̃t���O
	int slash;	//�a��ꂽ�ԍ�
};

struct Block {	//���ۂɏ����Ŏg������̃f�[�^
	WorldTransform pos;	//���g�̍��W
	bool isCut;	//���g���a��ꂽ���ǂ����̃t���O
	bool cutted;	//�a���I������t���O
	Timer timer;
	bool create;	//��������Ă邩�̃t���O
};

class Stage {
public:
	//������
	void Initialize(Model* model,float anyPosY);
	//�X�V
	void Update(Vector3 player,bool cutFlag);
	//�e�X�g�p�X�V
	void UpdateTest();
	//�`��
	void Draw(ViewProjection viewProjection);
private:
	//�ǂ̑��ꂪ�v���C���[�ƈ�ԋ߂����`�F�b�N
	void CheckPos(Vector3* player);
	//�O�̃u���b�N���a���Ă����玩�����Y����֐�
	void CheckIfCut();
private:
	//���[���h���W
	Block block[32][32];
	//�u���b�N��
	const int blockNum = 32;
	//���f��
	Model* model = nullptr;
	//�Y����ʒu(�^���I����2�u���b�N���Y����)
	const double slippingNumbers = 0.39;
	//�ړ�����
	const float maxTime = 30;

	//debug�p(���Z�b�g)
	Input* input_ = nullptr;
	float resetPosY[32];
};
