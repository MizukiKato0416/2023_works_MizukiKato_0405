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
	SOUND_LABEL_SLASH_001,				// 斬撃1
	SOUND_LABEL_SLASH_002,				// 斬撃2
	SOUND_LABEL_SLASH_003,				// 斬撃3
	SOUND_LABEL_SLASH_004,				// 敵の斬撃
	SOUND_LABEL_SLASH_005,				// 斬撃4
	SOUND_LABEL_TITLE_DECIDE,			// タイトルの決定
	SOUND_LABEL_DAMAGE,					// ダメージ
	SOUND_LABEL_SELECT,					// カーソル移動
	SOUND_LABEL_PAUSEOPEN,				// ポーズオープン
	SOUND_LABEL_TIMEUP,					// タイムアップ
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

