//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_CAMERA (1)				//�J�����̍ő吔
#define CAMERA_R_SPEED (0.03f)		//�J�����̐���X�s�[�h
#define CAMERA_VR_SPEED (7.0f)		//�J�����̈ړ�
#define CAMERA_DISTANCE (300.0f)	//���_�ƒ����_�̋���

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 posV;			//���݂̎��_
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posR;			//���݂̒����_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotAsk;			//�ړI�̌���
	float rotDiffer;			//�ړI�̌����Ƃ̍�
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 viewport;		//�r���[�|�[�g
	float frotVecX;				//�G�ƃJ�����̃x�N�g���v�Z�ɕK�v
	float frotVecZ;				//�G�ƃJ�����̃x�N�g���v�Z�ɕK�v
	float frotVecXSub;			//�G�ƃJ�����̃x�N�g���v�Z�ɕK�v
	float frotVecZSub;			//�G�ƃJ�����̃x�N�g���v�Z�ɕK�v
	bool bRockOn;				//���b�N�I�����Ă��邩�ǂ���
	int nWhoRockOn;				//���b�N�I�����Ă���Ώۂ��N�Ȃ̂�
	int nCntEnemyDrone;			//�G�ƃh���[���̍��v�̐�
	int nEnemyNumber;			//�G�ƃh���[���̃i���o�[�ۑ��ϐ�
	float fToPlayerR;			//�G�ƃv���C���[�Ƃ̋����ۑ��p

	float ftest;				//�e�X�g�p
} Camera;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
void DrawCameratxt(void);
Camera *GetCamera(void);

#endif //!_CAMERA_H_

