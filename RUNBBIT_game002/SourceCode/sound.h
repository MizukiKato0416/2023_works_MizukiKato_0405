//=======================================================================
//サウンドに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//=================================
// サウンドファイル
//=================================
typedef enum
{
	SOUND_LABEL_STAGE1_BGM = 0,			// ステージ1BGM
	SOUND_LABEL_TITLE_BGM,				// タイトルBGM
	SOUND_LABEL_RESULT_BGM,				// リザルトBGM
	SOUND_LABEL_CURSOR,					// カーソル移動SE
	SOUND_LABEL_DECIDE,					// 決定SE
	SOUND_LABEL_RETURN,					// 戻るSE
	SOUND_LABEL_PAUSE,					// ポーズSE
	SOUND_LABEL_PLAYER_JUMP,			// プレイヤーのジャンプSE
	SOUND_LABEL_PLAYER_DAMAGE,			// プレイヤーのダメージSE
	SOUND_LABEL_ENEMY_KILL,				// 敵が倒されたときのSE
	SOUND_LABEL_ITEM_CARROT,			// 人参アイテムの取得SE
	SOUND_LABEL_TIME_UP,				// タイムアップSE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif

