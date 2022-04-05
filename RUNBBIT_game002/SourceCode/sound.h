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
	SOUND_LABEL_CURSOR,					// �J�[�\���ړ�SE
	SOUND_LABEL_DECIDE,					// ����SE
	SOUND_LABEL_RETURN,					// �߂�SE
	SOUND_LABEL_PAUSE,					// �|�[�YSE
	SOUND_LABEL_PLAYER_JUMP,			// �v���C���[�̃W�����vSE
	SOUND_LABEL_PLAYER_DAMAGE,			// �v���C���[�̃_���[�WSE
	SOUND_LABEL_ENEMY_KILL,				// �G���|���ꂽ�Ƃ���SE
	SOUND_LABEL_ITEM_CARROT,			// �l�Q�A�C�e���̎擾SE
	SOUND_LABEL_TIME_UP,				// �^�C���A�b�vSE
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

