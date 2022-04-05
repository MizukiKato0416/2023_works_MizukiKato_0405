//=======================================================================
//�Î~��Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _PICTURE_H_
#define _PICTURE_H_
#include "main.h"

//========================================================
////�}�N����`
//========================================================
#define MAX_PICTURE (1)			//PICTURE�̍ő吔
//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	PICTURETYPE_SETSUNEI = 0,	//��ʏ��
	PICTURETYPE_SOUSA,			//�������
	PICTURETYPE_TAOSE,			//���蕶��
	PICTURETYPE_MAX,
} PICTURETYPE;

//========================================================
//�����̂̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	PICTURETYPE nType;			//�^�C�v
	float fWidth;				//��
	float fHeight;				//����
	bool bUse;					//�g�p���Ă��邩�ǂ���
} PICTURE;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitPicture(void);
void UninitPicture(void);
void UpdatePicture(void);
void DrawPicture(void);
PICTURE *GetPicture(void);
#endif //!_PICTURE_H_
