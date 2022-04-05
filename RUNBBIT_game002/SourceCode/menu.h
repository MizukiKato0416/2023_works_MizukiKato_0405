//=======================================================================
//���j���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _MENU_H_
#define _MENU_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_MENU (6)			//���j���[�̍ő吔
#define MENU_TYPE (6)			//���j���[�̎�ނ̐�

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nCounterAnim = 0;	//�A�j���[�V�����J�E���^
	int nPatternAnim = 0;	//�A�j���[�V�����p�^�[��No
	int nType;				//���
	float fMenuWidth;		//���j���[�̉���
	float fMenuHeight;		//���j���[�̏c��
	bool bUse;				//�g�����ǂ���
	bool bSelectUse;		//�I������Ă��邩�ǂ���
} Menu;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitMenu(void);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
void SetMenu(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fMenuWidth, float fMenuHeight);
Menu *GetMenu(void);

#endif //!_MENU_H_

