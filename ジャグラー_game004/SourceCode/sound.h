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
//=================================
//BGM
//=================================
	SOUND_LABEL_TITLE_BGM = 0,			// タイトルBGM
	SOUND_LABEL_GAME_BGM,				//ゲームのBGM
	SOUND_LABEL_FEVER_BGM,				//フィーバー時のBGM
	SOUND_LABEL_RESULT_BGM,				// リザルトBGM
//=================================
//SE
//=================================
	SOUND_LABEL_DRUM_SE,				//タイトル名が出てくる時のSE
	SOUND_LABEL_ENTER_SE,				//エンターを押したときのSE
	SOUND_LABEL_FEVER_SE,				//フィーバーの時のSE
	SOUND_LABEL_ROLL_SE,				//スペース押したときSE
	SOUND_LABEL_SPACE_SE,				//スペース押したときSE←この二つは同時に
	SOUND_LABEL_TITLE_SE,				//タイトルでエンターSE
	SOUND_LABEL_SCORE_SE,				//スコア
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

