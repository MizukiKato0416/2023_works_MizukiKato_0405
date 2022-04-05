//=======================================================================
//�����\���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _WORD_H_
#define _WORD_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_WORD (5)			//�����̍ő吔
#define WORD_TYPE (6)			//�����̎�ނ̐�

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nType;			//���
	int nCnt;			//�J�E���g
	float fWordWidth;	//�G�̉���
	float fWordHeight;	//�G�̏c��
	bool bUse;			//�g�����ǂ���
} Word;

//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitWord(void);
void UninitWord(void);
void UpdateWord(void);
void DrawWord(void);
void SetWord(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fWordWidth, float fWordHeight);
Word *GetWord(void);

#endif //!_WORD_H_

