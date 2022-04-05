//=======================================================================
//�r���{�[�h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define EFFECT_WIDTH (1.0f)			//�G�t�F�N�g�̕�
#define EFFECT_HEIGHT (1.0f)		//�G�t�F�N�g�̍���
#define EFFECT_DEPTH (0.0f)			//�G�t�F�N�g�̉��s
#define EFFECT_TYPE (1)				//�G�t�F�N�g�̎��
#define MAX_EFFECT (10000)			//�G�t�F�N�g�̍ő吔

//========================================================
//�����̎��
//========================================================
typedef enum
{
	EFFEFCT_MOVETYPE_ENEMY_APPEAR = 0,	//�G���o�������Ƃ�
	EFFEFCT_MOVETYPE_ENEMY_DEATH,		//�G�����񂾂Ƃ�
	EFFEFCT_MOVETYPE_PLAYER_HOVER,		//�v���C���[�̃z�o�[
	EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW,	//�v���C���[�̗̑͂����Ȃ��Ƃ�
	EFFEFCT_MOVETYPE_PLAYER_DOWN,		//�v���C���[���_�E�������Ƃ�
	EFFEFCT_MOVETYPE_BULLET,			//�e�̋O��
	EFFEFCT_MOVETYPE_MAX,
} EFFECT_MOVETYPE;

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 scale;		//�X�P�[��
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	int nLife;				//����
	float fWidth;			//�G�t�F�N�g�̉���
	float fHeight;			//�G�t�F�N�g�̏c��
	float fDepth;			//�G�t�F�N�g�̉��s
	bool bUse;				//�g�p���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p
	EFFECT_MOVETYPE nType;	//�^�C�v

} EFFECT;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, D3DXCOLOR col, int nLife, EFFECT_MOVETYPE nType);
EFFECT *GetEffect(void);

#endif // !_EFFECT_H_