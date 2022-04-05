//=======================================================================
//���b�V���t�B�[���h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _GROUND_H_
#define _GROUND_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define GROUND_WIDTH (3200.0f*1.0f)		//���b�V���t�B�[���h�̕�
#define GROUND_HEIGHT (0.0f*1.0)		//���b�V���t�B�[���h�̍���
#define GROUND_DEPTH (3200.0f*1.0f)		//���b�V���t�B�[���h�̉��s
#define GROUND_X (20)					//X�̐�
#define GROUND_Z (20)					//Z�̐�
#define GROUND_TYPE (1)					//���b�V���t�B�[���h�̎��
#define MAX_GROUND (1)					//���b�V���t�B�[���h�̍ő吔

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	int nTileX;				//���̃^�C����
	int nTileZ;				//���s�̃^�C����
	float fWidth;			//�u���b�N�̉���
	float fHeight;			//�u���b�N�̏c��
	float fDepth;			//�u���b�N�̉��s
	bool bUse;				//�g�����ǂ���
} GROUND;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, int nTileX, int nTileZ);
GROUND *GetGround(void);

#endif // !_GROUND_H_