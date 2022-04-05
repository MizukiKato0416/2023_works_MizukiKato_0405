//=======================================================================
//�e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define BULLET_WIDTH (1.0f)		//�e�̕�
#define BULLET_HEIGHT (1.0f)	//�e�̍���
#define BULLET_DEPTH (0.0f)		//�e�̉��s
#define BULLET_TYPE (1)			//�e�̎��
#define MAX_BULLET (500)		//�e�̍ő吔
#define BULLET_SPEED (60.0f)	//�e�̑���

//========================================================
//�����̎��
//========================================================
typedef enum
{
	BULLET_MOVETYPE_NOMAL = 0,	//�m�[�}��
	BULLET_MOVETYPE_SPEED,		//�X�s�[�h
	BULLET_MOVETYPE_POWER,		//�p���[
	BULLET_MOVETYPE_MAX,
} BULLET_MOVETYPE;

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
	D3DXCOLOR col;			//�J���[
	BULLET_MOVETYPE nType;	//�e�̎��
} BULLET;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight , D3DXCOLOR col);
int CollisionBullet(D3DXVECTOR3 *pPos, float fWidth);
BULLET *GetBullet(void);

#endif // !_BULLET_H_