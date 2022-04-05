//=======================================================================
//ステージ2に関する処理
//Aouthor: 加藤　瑞葵
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
//グローバル変数宣言
//=======================================================================
bool g_bTutrial;	//ポーズ機能

//=======================================================================
//初期化処理
//=======================================================================
void InitGame(void)
{
	g_bTutrial = true;

	//各種オブジェの初期化処理

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
//終了処理
//=======================================================================
void UninitGame(void)
{
	StopSound(SOUND_LABEL_BGM001);

	//終了処理
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
//更新処理
//=======================================================================
void UpdateGame(void)
{
	//スペースキーを押したときの処理
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

	//更新処理
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
//描画処理
//=======================================================================
void DrawGame(void)
{
	//各種オブジェクトの描画処理
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