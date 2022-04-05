//=======================================================================
//�ω��̂Ȃ�UI�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//========================================================
////�}�N����`
//========================================================
#define MAX_UI (10)		//ui�̍ő吔
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//�^�C�g���\���̍���
//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	UITYPE_PLAYER = 0,			//�v���C���[
	UITYPE_TITLE,				//�^�C�g��
	UITYPE_START,				//�X�^�[�gUI
	UITYPE_PAUSE,				//�|�[�YUI
	UITYPE_CONTINUE,			//������
	UITYPE_EXIT,				//�o��
	UITYPE_MAX,
} UITYPE;

//========================================================
//�����̂̍\���̂̒�`
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu
	UITYPE nType;				//�^�C�v
	float fWidth;				//��
	float fHeight;				//����
	int col;					//�J���[
	bool bUse;					//�g�p���Ă��邩�ǂ���
} UI;


//========================================================
//�v���g�^�C�v�錾
//========================================================
void InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void SetUi(D3DXVECTOR3 pos, UITYPE nType, float fWidth, float fHeight);
UI *GetUi(void);
int GetPauseUi(void);
#endif //!_UI_H_
