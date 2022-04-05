//=======================================================================
//�Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "main.h"

//========================================================
////�}�N����`
//========================================================
#define MAX_LIFE (1)		//�Q�[�W�̍ő吔
#define MAX_TYPE (1)		//�Q�[�W�̎��
//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	GAUGETYPE_PLAYER = 0,			//�v���C���[
	GAUGETYPE_MAX,
} GAUGETYPE;

//========================================================
//�����̂̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	GAUGETYPE nType;			//�^�C�v
	float fWidth;				//��
	float fHeight;				//����
	bool bUse;					//�g�p���Ă��邩�ǂ���
} Life;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos, GAUGETYPE nType, float fWidth, float fHeight);
Life *GetLife(void);
#endif //!_LIFE_H_
