//=======================================================================
//�e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define SHADOW_WIDTH (90.0f*1.0f)		//�e�̕�
#define SHADOW_HEIGHT (0.0f*0.0f)		//�e�̍���
#define SHADOW_DEPTH (90.0f*1.0f)		//�e�̉��s
#define SHADOW_TYPE (1)					//�e�̎��
#define MAX_SHADOW (128)					//�e�̍ő吔


//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	float fWidth;			//�e�̉���
	float fHeight;			//�e�̏c��
	float fDepth;			//�e�̉��s
	int nType;				//�e�̃^�C�v
	bool bUse;				//�g�����ǂ���
} SHADOW;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos, bool bUse);
SHADOW *GetShadow(void);

#endif // !_SHADOW_H_