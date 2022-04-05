//=======================================================================
//�X�e�[�W2�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "game.h"
#include "Polygon.h"
#include "bg.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "explosion.h"
#include "item.h"
#include "enemy.h"
#include "boss.h"
#include "score.h"
#include "life.h"
#include "special.h"
#include "sound.h"
#include "input.h"
#include "tutorial.h"
 
//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
bool g_bTutrial;	//�|�[�Y�@�\

//=======================================================================
//����������
//=======================================================================
void InitGame(void)
{
	g_bTutrial = true;

	//�e��I�u�W�F�̏���������

	PlaySound(SOUND_LABEL_BGM001);

	if (g_bTutrial == true)
	{
		InitBg();
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
void UninitGame(void)
{
	StopSound(SOUND_LABEL_BGM001);

	//�I������
	if (g_bTutrial == true)
	{
		UninitBg();
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
void UpdateGame(void)
{
	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetKeyboardTrigger(DIK_LSHIFT) == true)
	{
		if (g_bTutrial == true)
		{
			g_bTutrial = false;
		}
		else if (g_bTutrial == false)
		{
			g_bTutrial = true;
		}
	}

	//�X�V����
	if (g_bTutrial == true)
	{
		UpdateBg();
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
	else if (g_bTutrial == false)
	{
		UpdateTutorial();
	}


}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawGame(void)
{
	//�e��I�u�W�F�N�g�̕`�揈��
	if (g_bTutrial == true)
	{
		DrawBg();
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
	else if (g_bTutrial == false)
	{
		DrawTutorial();
	}

}