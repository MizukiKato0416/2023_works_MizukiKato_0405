//=======================================================================
//�X�e�[�W3�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "stage3.h"
#include "Polygon.h"
#include "stage3Bg.h"
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
bool g_bTutrial2;	//�|�[�Y�@�\

//=======================================================================
//����������
//=======================================================================
void InitStage3(void)
{
	g_bTutrial2 = true;


	//�e��I�u�W�F�̏���������
	PlaySound(SOUND_LABEL_BGM001);

	if (g_bTutrial2 == true)
	{
		InitStage3Bg();
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
void UninitStage3(void)
{
	//�I������
	StopSound(SOUND_LABEL_BGM001);

	if (g_bTutrial2 == true)
	{
		UninitStage3Bg();
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
void UpdateStage3(void)
{
	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_LSHIFT) == true)
	{
		if (g_bTutrial2 == true)
		{
			g_bTutrial2 = false;
		}
		else if (g_bTutrial2 == false)
		{
			g_bTutrial2 = true;
		}
	}
	
	//�X�V����
	if (g_bTutrial2 == true)
	{
		UpdateStage3Bg();
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
	else if (g_bTutrial2 == false)
	{
		UpdateTutorial();
	}

	
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawStage3(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��

	if (g_bTutrial2 == true)
	{
		DrawStage3Bg();
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
	else if (g_bTutrial2 == false)
	{
		DrawTutorial();
	}
	
}