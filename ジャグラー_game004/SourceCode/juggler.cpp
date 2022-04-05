//=======================================================================
//�W���O���[�X�e�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "time.h"
#include "juggler.h"
#include "slot.h"
#include "bg.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

//=======================================================================
//����������
//=======================================================================
void InitJuggler(void)
{
	//�e��I�u�W�F�̏���������
	InitScore();
	InitTime();
	InitSlot();
	Initbg();

	//�I�u�W�F�N�g�̔z�u
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 1.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 2.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 3.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 4.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);

	StopSound();
	PlaySound(SOUND_LABEL_GAME_BGM);
}

//=======================================================================
//�I������
//=======================================================================
void UninitJuggler(void)
{
	//�I������
	UninitScore();
	UninitTime();
	UninitSlot();
	Uninitbg();
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateJuggler(void)
{
	//�X�V����
	UpdateScore();
	Updatebg();
	UpdateTime();
	UpdateSlot();
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawJuggler(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	Drawbg();
	DrawScore();
	DrawTime();
	DrawSlot();
}