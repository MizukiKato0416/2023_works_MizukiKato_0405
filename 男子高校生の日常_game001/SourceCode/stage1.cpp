//=======================================================================
//�X�e�[�W1�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "stage1.h"
#include "Polygon.h"
#include "stage1Bg.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "life.h"
#include "special.h"
#include "Item.h"
#include "sound.h"
#include "input.h"
#include "tutorial.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
bool g_bTutrial1;	//�|�[�Y�@�\

//=======================================================================
//����������
//=======================================================================
void InitStage1(void)
{
	g_bTutrial1 = true;


	//�e��I�u�W�F�̏���������
	PlaySound(SOUND_LABEL_BGM001);

	if (g_bTutrial1 == true)
	{
		InitStage1Bg();
		InitItem();
		InitPolygon();
		InitBullet();
		InitEnemyBullet();
		InitEnemy();
		InitBoss();
		InitExplosion();
		InitScore();
		InitLife();
		InitSpecial();
		InitTutorial();
	}
	
	
}

//=======================================================================
//�I������
//=======================================================================
void UninitStage1(void)
{
	//�I������
	StopSound(SOUND_LABEL_BGM001);

	if (g_bTutrial1 == true)
	{
		UninitStage1Bg();
		UninitItem();
		UninitPolygon();
		UninitBullet();
		UninitEnemyBullet();
		UninitEnemy();
		UninitBoss();
		UninitExplosion();
		UninitScore();
		UninitLife();
		UninitSpecial();
		UninitTutorial();
	}
	
	
	
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateStage1(void)
{
	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_LSHIFT) == true)
	{
		if (g_bTutrial1 == true)
		{
			g_bTutrial1 = false;
		}
		else if (g_bTutrial1 == false)
		{
			g_bTutrial1 = true;
		}
	}
	
	//�X�V����
	if (g_bTutrial1 == true)
	{
		UpdateStage1Bg();
		UpdateItem();
		UpdatePolygon();
		UpdateBullet();
		UpdateEnemyBullet();
		UpdateEnemy();
		UpdateBoss();
		UpdateExplosion();
		UpdateScore();
		UpdateLife();
		UpdateSpecial();
	}
	else if (g_bTutrial1 == false)
	{
		UpdateTutorial();
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
		DrawStage1Bg();
		DrawItem();
		DrawPolygon();
		DrawBullet();
		DrawEnemyBullet();
		DrawEnemy();
		DrawBoss();
		DrawExplosion();
		DrawScore();
		DrawLife();
		DrawSpecial();
		
	}
	else if (g_bTutrial1 == false)
	{
		DrawTutorial();
	}
	
}