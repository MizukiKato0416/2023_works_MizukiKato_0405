//=======================================================================
//�{�X�Ɋւ��鏈��
//Aouthor:�@�����@����
//=======================================================================

#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_BOSS (1)		//�G�̍ő吔
#define BOSS_HEIGHT (450.0f)	//�G�̏c�̑傫��
#define BOSS_WIDTH (400.0f)	//�G�̉��̑傫��

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nCounterAnim = 0;	//�A�j���[�V�����J�E���^
	int nPatternAnim = 0;	//�A�j���[�V�����p�^�[��No
	int nType;			//���
	int nLife;			//�̗�
	bool bUse;			//�g�����ǂ���
} Boss;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move,int nLife);
Boss *GetBoss(void);

#endif //!_BOSS_H_

