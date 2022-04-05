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
#define MAX_UI (20)		//ui�̍ő吔
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//�^�C�g���\���̍���
//========================================================
//�Q�[�W�̎��
//========================================================
typedef enum
{
	UITYPE_PLAYER = 0,			//�v���C���[
	UITYPE_TITLE,				//�^�C�g��
	UITYPE_START,				//�X�^�[�gUI
	UITYPE_BLACKMASK,			//�u���b�N�}�X�N
	UITYPE_PAUSE,				//�|�[�YUI
	UITYPE_CONTINUE,			//������
	UITYPE_EXIT,				//�o��
	UITYPE_EVOLUTION,			//�i���Q�[�W�O�g
	UITYPE_GAMESTART,			//�Q�[���X�^�[�g
	UITYPE_TUTORIAL,			//�`���[�g���A��
	UITYPE_BACKTITLE,			//�^�C�g���ɖ߂�
	UITYPE_GUN,					//�e
	UITYPE_SOWRD,				//��
	UITYPE_PLAYER_SPEED,		//�X�s�[�h�^�C�v
	UITYPE_PLAYER_POWER,		//�p���[�^�C�v
	UITYPE_BUTTON_Y,			//Y�{�^��
	UITYPE_3,					//3
	UITYPE_2,					//2
	UITYPE_1,					//1
	UITYPE_321START,			//321�X�^�[�g
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
	bool bCol;					//�J���[��ς��邽�߂ɕK�v
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
