//=======================================================================
//�G�̒e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define ENEMYBULLET_WIDTH (1.0f)		//�e�̕�
#define ENEMYBULLET_HEIGHT (1.0f)	//�e�̍���
#define ENEMYBULLET_DEPTH (0.0f)		//�e�̉��s
#define ENEMYBULLET_TYPE (1)			//�e�̎��
#define MAX_ENEMYBULLET (100)		//�e�̍ő吔
#define ENEMYBULLET_SPEED (20.0f)	//�e�̑���

//========================================================
//�����̎��
//========================================================
typedef enum
{
	ENEMYBULLET_MOVETYPE_DRONE001 = 0,	//�h���[��001
	ENEMYBULLET_MOVETYPE_DRONE002,		//�h���[��002
	ENEMYBULLET_MOVETYPE_DRONE003,		//�h���[��003
	ENEMYBULLET_MOVETYPE_BOSS_SMALL,	//�{�X����
	ENEMYBULLET_MOVETYPE_BOSS_BIG,		//�{�X����
	ENEMYBULLET_MOVETYPE_MAX,
} ENEMYBULLET_MOVETYPE;

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 scale;				//�X�P�[��
	D3DXVECTOR3 move;				//�ړ���
	float fWidth;					//�ǂ̉���
	float fHeight;					//�ǂ̏c��
	float fDepth;					//�ǂ̉��s
	bool bUse;						//�g�p���
	D3DXMATRIX mtxWorld;			//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;				//�r���[�}�g���b�N�X�擾�p
	D3DXCOLOR col;					//�J���[
	ENEMYBULLET_MOVETYPE nType;		//�e�̓���
	float fFarPlayer;				//�v���C���[�Ƃ̋���
} ENEMYBULLET;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
int CollisionEnemyBullet(D3DXVECTOR3 *pPos, float fWidth);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight , D3DXCOLOR col, ENEMYBULLET_MOVETYPE nType);
ENEMYBULLET *GetEnemyBullet(void);

#endif // !_ENEMYBULLET_H_