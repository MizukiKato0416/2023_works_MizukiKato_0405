//=======================================================================
//�n�C�X�R�A�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _HISCORE_H_
#define _HISCORE_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_HI_SCORE_POLYGON (8)			//�X�R�A�̃|���S���̍ő吔
#define HI_SCORE_POLYGON_HEIGHT (70.0f)	//�X�R�A�̃|���S���̏c�̑傫��
#define HI_SCORE_POLYGON_WIDTH (35.0f)		//�X�R�A�̃|���S���̉��̑傫��
#define HI_SCORE_POLYGON_POS_WIDTH (800.0f)		//�X�R�A�̃|���S���̉��̑傫��
#define HI_SCORE_POLYGON_POS_HEIGHT (450.0f)		//�X�R�A�̃|���S���̉��̑傫��


//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
} HiScore;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitHiScore(void);
void UninitHiScore(void);
void UpdateHiScore(void);
void DrawHiScore(void);
void SetHiScore(int nHiScore);

//Score *GetScore(void)

#endif //!_HISCORE_H_

