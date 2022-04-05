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
	SOUND_LABEL_MENU_BGM,				// メニューBGM
	SOUND_LABEL_CURSOR,					// カーソル移動SE
	SOUND_LABEL_DECIDE,					// 決定SE
	SOUND_LABEL_RETURN,					// 戻るSE
	SOUND_LABEL_PAUSE,					// ポーズSE
	SOUND_LABEL_SLASH_000,				// 斬撃1
	SOUND_LABEL_SLASH_001,				// 斬撃2
	SOUND_LABEL_SLASH_002,				// 斬撃3
	SOUND_LABEL_BULLET,					// 射撃パワー
	SOUND_LABEL_BULLET_P,				// 射撃パワー
	SOUND_LABEL_TITLE_DECIDE,			// タイトルの決定
	SOUND_LABEL_HIT,					// 命中
	SOUND_LABEL_PAUSEOPEN,				// ポーズオープン
	SOUND_LABEL_TIMEUP,					// タイムアップ
	SOUND_LABEL_GAMEOVER,				// 死去
	SOUND_LABEL_GRADEUP,				// 進化
	SOUND_LABEL_GRADECHARGE,			// 進化溜
	SOUND_LABEL_GRADEEND,				// 進化終わり
	SOUND_LABEL_LOCKON,					// ロックオン
	SOUND_LABEL_POWERUP,				// パワーアップ
	SOUND_LABEL_SPEEDUP,				// スピードアップ
	SOUND_LABEL_DAMAGE,					// スピードアップ
	SOUND_LABEL_321,					// 321
	SOUND_LABEL_START,					// すたーと
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

