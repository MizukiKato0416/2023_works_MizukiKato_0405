//=======================================================================
//変化のないUIに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _UI_H_
#define _UI_H_
#include "main.h"

//========================================================
////マクロ定義
//========================================================
#define MAX_UI (10)		//uiの最大数
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//タイトル表示の高さ
//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	UITYPE_PLAYER = 0,			//プレイヤー
	UITYPE_TITLE,				//タイトル
	UITYPE_START,				//スタートUI
	UITYPE_PAUSE,				//ポーズUI
	UITYPE_CONTINUE,			//続ける
	UITYPE_EXIT,				//出る
	UITYPE_MAX,
} UITYPE;

//========================================================
//爆発のの構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	UITYPE nType;				//タイプ
	float fWidth;				//幅
	float fHeight;				//高さ
	int col;					//カラー
	bool bUse;					//使用しているかどうか
} UI;


//========================================================
//プロトタイプ宣言
//========================================================
void InitUi(void);
void UninitUi(void);
void UpdateUi(void);
void DrawUi(void);
void SetUi(D3DXVECTOR3 pos, UITYPE nType, float fWidth, float fHeight);
UI *GetUi(void);
int GetPauseUi(void);
#endif //!_UI_H_
