//=======================================================================
//�T�E���h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// �T�E���h�t�@�C��
//=================================
typedef enum
{
//=================================
//BGM
//=================================
	SOUND_LABEL_TITLE_BGM = 0,			// �^�C�g��BGM
	SOUND_LABEL_GAME_BGM,				//�Q�[����BGM
	SOUND_LABEL_FEVER_BGM,				//�t�B�[�o�[����BGM
	SOUND_LABEL_RESULT_BGM,				// ���U���gBGM
//=================================
//SE
//=================================
	SOUND_LABEL_DRUM_SE,				//�^�C�g�������o�Ă��鎞��SE
	SOUND_LABEL_ENTER_SE,				//�G���^�[���������Ƃ���SE
	SOUND_LABEL_FEVER_SE,				//�t�B�[�o�[�̎���SE
	SOUND_LABEL_ROLL_SE,				//�X�y�[�X�������Ƃ�SE
	SOUND_LABEL_SPACE_SE,				//�X�y�[�X�������Ƃ�SE�����̓�͓�����
	SOUND_LABEL_TITLE_SE,				//�^�C�g���ŃG���^�[SE
	SOUND_LABEL_SCORE_SE,				//�X�R�A
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

