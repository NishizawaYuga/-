#include "TitleScene.h"
#include <cassert>

void TitleScene::Initialize()
{
	
	nextScene_ = Scene::TITLE;

	//�t�@�C�������w�肵�ăe�N�X�`����ǂݍ���
	drawBas_->LoadTexture(0, "Title.png");
	
	spriteBG = new Sprite();
	spriteBG->Initialize(drawBas_, 0);
	spriteBG->SetAnchorPoint({ 0.0f, 0.0f });

	// �w�i�X�v���C�g����
	//spriteBG = Sprite::Create(1, { 0.0f,0.0f });
}

void TitleScene::Update()
{
	changeFlag_ = false;
	/*if (input->TriggerKey(DIK_SPACE)) {*/
		changeFlag_ = true;
		nextScene_ = Scene::GAME;
	}
//}

void TitleScene::Draw()
{
#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	drawBas_->PreDraw();

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>
	spriteBG->Draw();

	// �X�v���C�g�`��㏈��
	drawBas_->PostDraw;
	// �[�x�o�b�t�@�N���A
	//dxBas_->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	//Model::PreDraw(commandList);

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>
	// 3D���f���`�� 

	// 3D�I�u�W�F�N�g�`��㏈��
	//Model::PostDraw();
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	drawBas_->PreDraw();

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>


	// �X�v���C�g�`��㏈��
	drawBas_->PostDraw;

#pragma endregion

}
