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
#define MAX_UI (20)		//uiの最大数
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//タイトル表示の高さ
//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	UITYPE_PLAYER = 0,			//プレイヤー
	UITYPE_TITLE,				//タイトル
	UITYPE_START,				//スタートUI
	UITYPE_BLACKMASK,			//ブラックマスク
	UITYPE_PAUSE,				//ポーズUI
	UITYPE_CONTINUE,			//続ける
	UITYPE_EXIT,				//出る
	UITYPE_EVOLUTION,			//進化ゲージ外枠
	UITYPE_GAMESTART,			//ゲームスタート
	UITYPE_TUTORIAL,			//チュートリアル
	UITYPE_BACKTITLE,			//タイトルに戻る
	UITYPE_GUN,					//銃
	UITYPE_SOWRD,				//剣
	UITYPE_PLAYER_SPEED,		//スピードタイプ
	UITYPE_PLAYER_POWER,		//パワータイプ
	UITYPE_BUTTON_Y,			//Yボタン
	UITYPE_3,					//3
	UITYPE_2,					//2
	UITYPE_1,					//1
	UITYPE_321START,			//321スタート
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
	bool bCol;					//カラーを変えるために必要
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
