//=======================================================================
//ジャグラーステージに関する処理
//Aouthor: 加藤　瑞葵
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
//グローバル変数宣言
//=======================================================================

//=======================================================================
//初期化処理
//=======================================================================
void InitJuggler(void)
{
	//各種オブジェの初期化処理
	InitScore();
	InitTime();
	InitSlot();
	Initbg();

	//オブジェクトの配置
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 1.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 2.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 3.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);
	SetSlot(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f * 4.6f, 0.0f), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f);

	StopSound();
	PlaySound(SOUND_LABEL_GAME_BGM);
}

//=======================================================================
//終了処理
//=======================================================================
void UninitJuggler(void)
{
	//終了処理
	UninitScore();
	UninitTime();
	UninitSlot();
	Uninitbg();
}

//=======================================================================
//更新処理
//=======================================================================
void UpdateJuggler(void)
{
	//更新処理
	UpdateScore();
	Updatebg();
	UpdateTime();
	UpdateSlot();
}

//=======================================================================
//描画処理
//=======================================================================
void DrawJuggler(void)
{
	//各種オブジェクトの描画処理
	Drawbg();
	DrawScore();
	DrawTime();
	DrawSlot();
}