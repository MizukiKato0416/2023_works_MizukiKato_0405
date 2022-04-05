//=======================================================================
//�G�̗̓Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _ENEMYLIFE_H_
#define _ENEMYLIFE_H_
#include "main.h"
//========================================================
//�}�N����`
//========================================================
#define ENEMYLIFE_WIDTH (1.0f)		//�Q�[�W�̕�
#define ENEMYLIFE_HEIGHT (1.0f)		//�Q�[�W�̍���
#define ENEMYLIFE_DEPTH (0.0f)		//�Q�[�W�̉��s
#define ENEMYLIFE_TYPE (1)			//�Q�[�W�̎��
#define MAX_ENEMYLIFE (50)			//�Q�[�W�̍ő吔


//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 scale;		//�X�P�[��
	D3DXVECTOR3 move;		//�ړ���
	float fWidth;			//�Q�[�W�̉���
	float fHeight;			//�Q�[�W�̏c��
	float fDepth;			//�Q�[�W�̉��s
	bool bUse;				//�g�p���
	D3DXMATRIX mtxWorld;	//���[���h�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�擾�p
	int nShadow;			//�e

} EnemyLife;


//========================================================
//�v���g�^�C�v�錾
//========================================================
HRESULT InitEnemyLife(void);
void UninitEnemyLife(void);
void UpdateEnemyLife(void);
void DrawEnemyLife(void);
int SetEnemyLife(D3DXVECTOR3 pos, float fWidth, float fHeight);
void SetPositionEnemyLife(int nIdx, D3DXVECTOR3 pos, bool bUse, int nMaxlife, int nLife, float fWidth);
EnemyLife *GetEnemyLife(void);

#endif // !_ENEMYLIFE_H_