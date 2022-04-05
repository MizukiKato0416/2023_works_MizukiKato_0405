//=======================================================================
//�r���{�[�h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define BILLBOARD_WIDTH (1.0f)		//�ǂ̕�
#define BILLBOARD_HEIGHT (1.0f)		//�ǂ̍���
#define BILLBOARD_DEPTH (0.0f)		//�ǂ̉��s
#define BILLBOARD_TYPE (1)			//�ǂ̎��
#define MAX_BILLBOARD (255)			//�ǂ̍ő吔


//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 scale;		//�X�P�[��
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//�ǂ̉���
	float fHeight;			//�ǂ̏c��
	float fDepth;			//�ǂ̉��s
	bool bUse;				//�g�p���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p
	int nShadow;			//�e

} BILLBOARD;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight);
BILLBOARD *GetBillboard(void);

#endif // !_BILLBOARD_H_