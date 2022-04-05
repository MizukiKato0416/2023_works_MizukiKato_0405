//=======================================================================
//�ω��̂Ȃ�MASK�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _MASK_H_
#define _MASK_H_
#include "main.h"

//========================================================
////�}�N����`
//========================================================
#define MAX_MASK (10)			//MASK�̍ő吔
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//�^�C�g���\���̍���
//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	MASKTYPE_DAMAGE = 0,		//�����Ԃ��̎���}�X�N
	MASKTYPE_GAMEOVER,			//�Q�[���I�[�o�[�}�X�N
	MASKTYPE_TIMEUP ,			//�Q�[���I�[�o�[�}�X�N
	MASKTYPE_MAX,
} MASKTYPE;

//========================================================
//�����̂̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	MASKTYPE nType;				//�^�C�v
	float fWidth;				//��
	float fHeight;				//����
	int col;					//�J���[
	bool bUse;					//�g�p���Ă��邩�ǂ���
} MASK;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitMask(void);
void UninitMask(void);
void UpdateMask(void);
void DrawMask(void);
void SetMask(D3DXVECTOR3 pos, MASKTYPE nType, float fWidth, float fHeight);
MASK *GetMask(void);
#endif //!_MASK_H_
