//=======================================================================
//���j���[�I���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _SELECT_H_
#define _SELECT_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_SELECT (1)			//���j���[�I���̍ő吔
#define SELECT_TYPE (1)			//���j���[�I���̎�ނ̐�

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nType;			//���
	float fSelectWidth;	//���j���[�I���̉���
	float fSelectHeight;	//���j���[�I���̏c��
	bool bUse;			//�g�����ǂ���
	bool bMenu1;			//�g�����ǂ���
	bool bMenu2;			//�g�����ǂ���
	bool bMenu3;			//�g�����ǂ���
} Select;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
void SetSelect(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fSelectWidth, float fSelectHeight);
Select *GetSelect(void);

#endif //!_SELECT_H_
