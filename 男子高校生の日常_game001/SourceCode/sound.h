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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_shot000,		// �V���b�g��
	SOUND_LABEL_shotSP000,		// �V���b�g��
	SOUND_LABEL_ENEMY_DAMAGE000,		// �G�̔�e��
	SOUND_LABEL_DAMAGE000,		// �_���[�W��
	SOUND_LABEL_START000,		// ���艹
	SOUND_LABEL_START001,		// ���艹
	SOUND_LABEL_EXPLOTION000,		// �X�^�[�g��
	SOUND_LABEL_CURE000,		// �񕜉�
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
