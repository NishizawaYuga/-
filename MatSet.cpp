#include "MatSet.h"

MatSet::MatSet() {
	//matWorld_�ɒP�ʍs�����
		/*
			1, 0, 0, 0
			0, 1, 0, 0
			0, 0, 1, 0
			0, 0, 0, 1
		*/
		//�P�ʍs��
	matIdentity.m[0][0] = 1;
	matIdentity.m[1][1] = 1;
	matIdentity.m[2][2] = 1;
	matIdentity.m[3][3] = 1;
}

void MatSet::MatIdentity(WorldTransform& worldTransform) {
	this->worldTransform = worldTransform;

	//�X�P�[�����O�{����s��ɐݒ肷��
	/*
		Sx,0,0,0
		0,Sy,0,0
		0,0,Sz,0
		0,0, 0,1
	*/
	matScale.m[0][0] = this->worldTransform.scale_.x; //Sx
	matScale.m[1][1] = this->worldTransform.scale_.y; //Sy
	matScale.m[2][2] = this->worldTransform.scale_.z; //Sz
	matScale.m[3][3] = 1;						 // 1

	

	//Z����]�s��̊e�v�f��ݒ肷��
	/*
		 cos, sin, 0, 0
		-sin, cos, 0, 0
		   0,   0, 1, 0
		   0,   0, 0, 1
	*/
	matRotZ = matIdentity;
	matRotZ.m[0][0] = cos(this->worldTransform.rotation_.z);
	matRotZ.m[0][1] = sin(this->worldTransform.rotation_.z);
	matRotZ.m[1][0] = -sin(this->worldTransform.rotation_.z);
	matRotZ.m[1][1] = cos(this->worldTransform.rotation_.z);

	//X����]�s��̊e�v�f��ݒ肷��
	/*
		   1,    0,   0, 0
		   0,  cos, sin, 0
		   0, -sin, cos, 0
		   0,    0,   0, 1
	*/
	matRotX = matIdentity;
	matRotX.m[1][1] = cos(this->worldTransform.rotation_.x);
	matRotX.m[1][2] = sin(this->worldTransform.rotation_.x);
	matRotX.m[2][1] = -sin(this->worldTransform.rotation_.x);
	matRotX.m[2][2] = cos(this->worldTransform.rotation_.x);

	//Y����]�s��̊e�v�f��ݒ肷��
	/*
		 cos,   0, -sin, 0
		   0,   1,    0, 0
		 sin,   0,  cos, 0
		   0,   0,    0, 1
	*/
	matRotY = matIdentity;
	matRotY.m[0][0] = cos(this->worldTransform.rotation_.y);
	matRotY.m[0][2] = -sin(this->worldTransform.rotation_.y);
	matRotY.m[2][0] = sin(this->worldTransform.rotation_.y);
	matRotY.m[2][2] = cos(this->worldTransform.rotation_.y);

	//�e���̉�]�s������
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	//�ړ��ʂ�s��ɐݒ肷��
	/*
		 1,  0,  0, 0
		 0,  1,  0, 0
		 0,  0,  1, 0
		Tx, Ty, Tz, 1
	*/
	matTrans.m[3][0] = this->worldTransform.position_.x;
	matTrans.m[3][1] = this->worldTransform.position_.y;
	matTrans.m[3][2] = this->worldTransform.position_.z;

	//���
	this->worldTransform.matWorld_ = matIdentity;
	this->worldTransform.matWorld_ *= matScale;
	this->worldTransform.matWorld_ *= matRot;
	this->worldTransform.matWorld_ *= matTrans;

	//�X�P�[�����O�s��@���@��]�s��@���@���s�ړ��s��̏��Ɋ|���Z

	worldTransform.matWorld_ = this->worldTransform.matWorld_;
}

Matrix4& MatSet2::MatIdentity(WorldTransform& worldTransform) {
	//matWorld_�ɒP�ʍs�����
		/*
			1, 0, 0, 0
			0, 1, 0, 0
			0, 0, 1, 0
			0, 0, 0, 1
		*/
		//�P�ʍs��
	matIdentity.m[0][0] = 1;
	matIdentity.m[1][1] = 1;
	matIdentity.m[2][2] = 1;
	matIdentity.m[3][3] = 1;

	//�X�P�[�����O�{����s��ɐݒ肷��
	/*
		Sx,0,0,0
		0,Sy,0,0
		0,0,Sz,0
		0,0, 0,1
	*/
	matScale.m[0][0] = worldTransform.scale_.x; //Sx
	matScale.m[1][1] = worldTransform.scale_.y; //Sy
	matScale.m[2][2] = worldTransform.scale_.z; //Sz
	matScale.m[3][3] = 1;						 // 1



	//Z����]�s��̊e�v�f��ݒ肷��
	/*
		 cos, sin, 0, 0
		-sin, cos, 0, 0
		   0,   0, 1, 0
		   0,   0, 0, 1
	*/
	matRotZ = matIdentity;
	matRotZ.m[0][0] = cos(worldTransform.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform.rotation_.z);

	//X����]�s��̊e�v�f��ݒ肷��
	/*
		   1,    0,   0, 0
		   0,  cos, sin, 0
		   0, -sin, cos, 0
		   0,    0,   0, 1
	*/
	matRotX = matIdentity;
	matRotX.m[1][1] = cos(worldTransform.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform.rotation_.x);

	//Y����]�s��̊e�v�f��ݒ肷��
	/*
		 cos,   0, -sin, 0
		   0,   1,    0, 0
		 sin,   0,  cos, 0
		   0,   0,    0, 1
	*/
	matRotY = matIdentity;
	matRotY.m[0][0] = cos(worldTransform.rotation_.y);
	matRotY.m[0][2] = -sin(worldTransform.rotation_.y);
	matRotY.m[2][0] = sin(worldTransform.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform.rotation_.y);

	//�e���̉�]�s������
	matRot = matIdentity;
	matRot *= matRotZ;
	matRot *= matRotX;
	matRot *= matRotY;

	//�ړ��ʂ�s��ɐݒ肷��
	/*
		 1,  0,  0, 0
		 0,  1,  0, 0
		 0,  0,  1, 0
		Tx, Ty, Tz, 1
	*/
	matTrans.m[3][0] = worldTransform.position_.x;
	matTrans.m[3][1] = worldTransform.position_.y;
	matTrans.m[3][2] = worldTransform.position_.z;

	//���
	worldTransform.matWorld_ = matIdentity;
	worldTransform.matWorld_ *= matScale;
	worldTransform.matWorld_ *= matRot;
	worldTransform.matWorld_ *= matTrans;

	//�X�P�[�����O�s��@���@��]�s��@���@���s�ړ��s��̏��Ɋ|���Z

	return worldTransform.matWorld_;
}