//=======================================================================
//ステージ3に関する処理
//Aouthor: 加藤　瑞葵
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
//グローバル変数宣言
//=======================================================================
bool g_bTutrial2;	//ポーズ機能

//=======================================================================
//初期化処理
//=======================================================================
void InitStage3(void)
{
	g_bTutrial2 = true;


	//各種オブジェの初期化処理
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
//終了処理
//=======================================================================
void UninitStage3(void)
{
	//終了処理
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
//更新処理
//=======================================================================
void UpdateStage3(void)
{
	//スペースキーを押したときの処理
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
	
	//更新処理
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
//描画処理
//=======================================================================
void DrawStage3(void)
{
	//各種オブジェクトの描画処理

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