//=======================================================================
//�����L���O�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _RUNKING_H_
#define _RUNKING_H_
#include "main.h"

//========================================================
//�}�N����`
//========================================================
#define MAX_RUNKING_POLYGON (8)			//�X�R�A�̃|���S���̍ő吔
#define MAX_RUNKING (6)					//�����L���O�̍ő吔
#define RUNKING_POLYGON_HEIGHT (60.0f)	//�X�R�A�̃|���S���̏c�̑傫��
#define RUNKING_POLYGON_WIDTH (45.0f)		//�X�R�A�̃|���S���̉��̑傫��
#define RUNKING_RESULT_POS_WIDTH (800.0f)	//���U���g��ʂł̃|���S����X���W
#define RUNKING_RESULT_POS_HEIGHT (320.0f)	//���U���g��ʂł̃|���S����Y���W

//========================================================
//�\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int score;			//�X�R�A
	bool bUse;			//�g�����ǂ���
} Runking;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitRunking(void);
void UninitRunking(void);
void UpdateRunking(void);
void DrawRunking(void);
void SetRunking(int nRunking);
//Runking *GetRunking(void)

#endif //!_RUNKING_H_
