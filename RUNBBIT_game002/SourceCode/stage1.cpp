//=======================================================================
//�X�e�[�W1�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "stage1.h"
#include "bg.h"
#include "bg2.h"
#include "bg3.h"
#include "player.h"
#include "block.h"
#include "enemy.h"
#include "input.h"
#include "time.h"
#include "item.h"
#include "score.h"
#include "menu.h"
#include "select.h"
#include "fade.h"
#include "word.h"
#include "sound.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
bool g_bTutrial1;	//�|�[�Y�@�\
bool g_bTutrial2;	//�|�[�Y�@�\
int g_aMapData[MAX_LINE][MAX_COLUMN];	//�X�e�[�W�f�[�^

//=======================================================================
//����������
//=======================================================================
void InitStage1(void)
{
	StopSound(SOUND_LABEL_RESULT_BGM);
	PlaySound(SOUND_LABEL_STAGE1_BGM);

	g_bTutrial1 = true;
	g_bTutrial2 = false;


	//�e��I�u�W�F�̏���������

	if (g_bTutrial1 == true)
	{
		InitBg();
		InitBg2();
		InitBg3();
		InitBlock();
		InitEnemy();
		InitPlayer();
		InitScore();
		InitTime();
		//InitLife();
		//InitItemUi();
		InitItem();
		InitMenu();
		InitSelect();
		InitWord();
	}
	SetSelect(D3DXVECTOR3(SCREEN_WIDTH / 4.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 70.0f, 70.0f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f, 0.0f), 3, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 2.0f, 0.0f), 4, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 4.0f * 3.0f, 0.0f), 5, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 400.0f * 1.2f, 70.0f * 1.2f);


	//=======================================================================
	//�X�e�[�W�f�[�^�̓ǂݍ���
	//=======================================================================

	//���[�h����
	FILE *pFile;
	pFile = fopen("data/STAGE/Stage1.csv", "r");
	int nCntX = 0, nCntY = 0;
	char aLine[7000];
	while (fgets(aLine, 7000, pFile) != NULL)
	{
		nCntX = 0;
		char *pToken = strtok(aLine, ",");
		while (pToken != NULL)
		{
			int nNum = atoi(pToken);
			g_aMapData[nCntY][nCntX] = nNum;
			pToken = strtok(NULL,",");
			nCntX++;
		}
		nCntY++;
	}
	fclose(pFile);


	//=============================================
	//�u���b�N�̐ݒu
	//=============================================

	for (int nCntY = 0; nCntY < MAX_LINE; nCntY++)
	{
		for (int nCntX = 0; nCntX < MAX_COLUMN; nCntX++)
		{
			if (g_aMapData[nCntY][nCntX] == 1)		//1*1�u���b�N
			{
				//D3DXVECTOR3 pos = D3DXVECTOR3(0.0f + 50.0f* nCntX, 0.0f + 50.0f * nCntY, 0);
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 40.0f, 40.0f, 1.0f, 1.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 2)
			{
				SetEnemy(D3DXVECTOR3(20.0f + 40.0f* nCntX, 40.0f + 40.0f * nCntY, 0.0f), 0, D3DXVECTOR3(-0.5f, 0.0f, 0.0f), 1, 40.0f, 40.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 3)
			{
				SetItem(D3DXVECTOR3(20.0f + 40.0f* nCntX, 40.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
			}
			else if (g_aMapData[nCntY][nCntX] == 4)		//4*1�u���b�N
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 40.0f, 160.0f, 1.0f, 4.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 5)		//�G���˕Ԃ�
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 1, 40.0f, 40.0f, 1.0f, 1.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 6)		//6*1�u���b�N
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 40.0f, 240.0f, 1.0f, 6.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 7)		//���U�T
			{
				SetEnemy(D3DXVECTOR3(20.0f + 40.0f* nCntX, 40.0f + 40.0f * nCntY, 0.0f), 0, D3DXVECTOR3(-2.0f, 0.0f, 0.0f), 1, 40.0f, 40.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 10)		//���ɓ����u���b�N
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), 2, 1, 160.0f, 40.0f, 4.0f, 1.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 9)		//���ɓ����u���b�N
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 3, 1, 80.0f, 40.0f, 2.0f, 1.0f);
			}
			else if (g_aMapData[nCntY][nCntX] == 22)		//2*1�u���b�N
			{
				SetMoveBlock(D3DXVECTOR3(0.0f + 40.0f* nCntX, 0.0f + 40.0f * nCntY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, 1, 40.0f, 80.0f, 1.0f, 2.0f);
			}

		}
	}
	SetWord(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT);
	//SetWord(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 400.0f);
}

//=======================================================================
//�I������
//=======================================================================
void UninitStage1(void)
{
	//�I������
	StopSound(SOUND_LABEL_STAGE1_BGM);

	UninitBg();
	UninitBg2();
	UninitBg3();
	UninitItem();
	UninitBlock();
	UninitEnemy();
	UninitPlayer();
	UninitScore();
	UninitTime();
	UninitMenu();
	UninitSelect();
	UninitWord();
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateStage1(void)
{
	//P�L�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		if (g_bTutrial1 == true)
		{
			g_bTutrial1 = false;
			PlaySound(SOUND_LABEL_PAUSE);
			StopSound(SOUND_LABEL_STAGE1_BGM);
		}
	}

	//�X�V����
	if (g_bTutrial1 == true)
	{
		UpdateBg();
		UpdateBg2();
		UpdateBg3();
		//UpdateEffect();
		UpdateEnemy();
		UpdateItem();
		UpdatePlayer();
		UpdateBlock();
		//UpdateExplosion();
		UpdateScore();
		UpdateTime();
		//UpdateLife();
		//UpdateItemUi();
	}
	else if (g_bTutrial1 == false && g_bTutrial1 == false)
	{
		UpdateWord();
		UpdateMenu();
		UpdateSelect();

		Select *pSelect;
		//�Z���N�g�̎擾
		pSelect = GetSelect();

		//�G���^�[�L�[���������Ƃ��̏���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (pSelect->bMenu1 == true)
			{
				if (pSelect->nType == 0)
				{
					if (g_bTutrial1 == false)
					{
						PlaySound(SOUND_LABEL_RETURN);
						PlaySound(SOUND_LABEL_STAGE1_BGM);
						g_bTutrial1 = true;
					}
				}
			}
			else if (pSelect->bMenu2 == true)
			{
				if (pSelect->nType == 0)
				{
					g_bTutrial1 = true;
					SetFade(MODE_STAGE1);
					PlaySound(SOUND_LABEL_DECIDE);
				}
			}
			else if (pSelect->bMenu3 == true)
			{
				if (pSelect->nType == 0)
				{
					SetFade(MODE_TITLE);
					PlaySound(SOUND_LABEL_RETURN);
				}
			}
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawStage1(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��

	if (g_bTutrial1 == true)
	{
		DrawBg();
		DrawBlock();
		DrawItem();
		DrawEnemy();
		DrawPlayer();
		DrawBg2();
		DrawBg3();
		DrawScore();
		DrawTime();
	}
	else if (g_bTutrial1 == false && g_bTutrial1 == false)
	{
		DrawBg();
		DrawBlock();
		DrawItem();
		DrawEnemy();
		DrawPlayer();
		DrawBg2();
		DrawBg3();
		DrawScore();
		DrawTime();
		DrawWord();
		DrawMenu();
		DrawSelect();
	}

}