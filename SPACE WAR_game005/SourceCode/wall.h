//=======================================================================
//�ǂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define WALL_WIDTH (800.0f)		//�ǂ̕�
#define WALL_HEIGHT (600.0f)	//�ǂ̍���
#define WALL_DEPTH (0.0f)		//�ǂ̉��s
#define WALL_TYPE (1)			//�ǂ̎��
#define MAX_WALL (4)			//�ǂ̍ő吔


//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 scale;		//�X�P�[��
	float fWidth;			//�ǂ̉���
	float fHeight;			//�ǂ̏c��
	float fDepth;			//�ǂ̉��s
	bool bUse;				//�g�p���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nNum;				//�Ǎ\����
} WALL;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);

#endif // !_WALL_H_