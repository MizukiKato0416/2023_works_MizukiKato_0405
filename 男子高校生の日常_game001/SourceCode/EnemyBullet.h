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
#define MAX_ENEMY_BULLET (128)				//�e�̍ő吔
#define ENEMY_BULLET_WIDTH_HEIGHT (30.0f)		//�����`�̒e�̏c�̑傫��
#define MAX_ENEMY_BULLET_TYPE (14)		//�e�̎��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	int nType;					//���
	float EnemyBulletHeight;	//�e�̏c�̑傫��
	float EnemyBulletWidth;		//�e�̉��̑傫��
	bool bUse;					//�g�p���Ă��邩�ǂ���
} EnemyBullet;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type, float EnemyBulletHeight, float EnemyBulletWidth);
EnemyBullet *GetEnemyBullet(void);

#endif //!_ENEMYBULLET_H_

