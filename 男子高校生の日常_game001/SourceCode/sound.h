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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_shot000,		// ショット音
	SOUND_LABEL_shotSP000,		// ショット音
	SOUND_LABEL_ENEMY_DAMAGE000,		// 敵の被弾音
	SOUND_LABEL_DAMAGE000,		// ダメージ音
	SOUND_LABEL_START000,		// 決定音
	SOUND_LABEL_START001,		// 決定音
	SOUND_LABEL_EXPLOTION000,		// スタート音
	SOUND_LABEL_CURE000,		// 回復音
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
