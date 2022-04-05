//=======================================================================
//ステージ1に関する処理
//Aouthor: 加藤　瑞葵
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
//グローバル変数宣言
//=======================================================================
bool g_bTutrial1;	//ポーズ機能

//=======================================================================
//初期化処理
//=======================================================================
void InitStage1(void)
{
	g_bTutrial1 = true;


	//各種オブジェの初期化処理
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
//終了処理
//=======================================================================
void UninitStage1(void)
{
	//終了処理
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
//更新処理
//=======================================================================
void UpdateStage1(void)
{
	//スペースキーを押したときの処理
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
	
	//更新処理
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
//描画処理
//=======================================================================
void DrawStage1(void)
{
	//各種オブジェクトの描画処理

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