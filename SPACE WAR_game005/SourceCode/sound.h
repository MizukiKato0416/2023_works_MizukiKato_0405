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
	SOUND_LABEL_STAGE1_BGM = 0,			// �X�e�[�W1BGM
	SOUND_LABEL_TITLE_BGM,				// �^�C�g��BGM
	SOUND_LABEL_RESULT_BGM,				// ���U���gBGM
	SOUND_LABEL_MENU_BGM,				// ���j���[BGM
	SOUND_LABEL_CURSOR,					// �J�[�\���ړ�SE
	SOUND_LABEL_DECIDE,					// ����SE
	SOUND_LABEL_RETURN,					// �߂�SE
	SOUND_LABEL_PAUSE,					// �|�[�YSE
	SOUND_LABEL_SLASH_000,				// �a��1
	SOUND_LABEL_SLASH_001,				// �a��2
	SOUND_LABEL_SLASH_002,				// �a��3
	SOUND_LABEL_BULLET,					// �ˌ��p���[
	SOUND_LABEL_BULLET_P,				// �ˌ��p���[
	SOUND_LABEL_TITLE_DECIDE,			// �^�C�g���̌���
	SOUND_LABEL_HIT,					// ����
	SOUND_LABEL_PAUSEOPEN,				// �|�[�Y�I�[�v��
	SOUND_LABEL_TIMEUP,					// �^�C���A�b�v
	SOUND_LABEL_GAMEOVER,				// ����
	SOUND_LABEL_GRADEUP,				// �i��
	SOUND_LABEL_GRADECHARGE,			// �i����
	SOUND_LABEL_GRADEEND,				// �i���I���
	SOUND_LABEL_LOCKON,					// ���b�N�I��
	SOUND_LABEL_POWERUP,				// �p���[�A�b�v
	SOUND_LABEL_SPEEDUP,				// �X�s�[�h�A�b�v
	SOUND_LABEL_DAMAGE,					// �X�s�[�h�A�b�v
	SOUND_LABEL_321,					// 321
	SOUND_LABEL_START,					// �����[��
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

