//=======================================================================
//変化のないMASKに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _MASK_H_
#define _MASK_H_
#include "main.h"

//========================================================
////マクロ定義
//========================================================
#define MAX_MASK (10)			//MASKの最大数
#define MAX_TITLE_HEIGHT (SCREEN_HEIGHT / 2.0f)		//タイトル表示の高さ
//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	MASKTYPE_DAMAGE = 0,		//血しぶきの周りマスク
	MASKTYPE_GAMEOVER,			//ゲームオーバーマスク
	MASKTYPE_TIMEUP ,			//ゲームオーバーマスク
	MASKTYPE_MAX,
} MASKTYPE;

//========================================================
//爆発のの構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	MASKTYPE nType;				//タイプ
	float fWidth;				//幅
	float fHeight;				//高さ
	int col;					//カラー
	bool bUse;					//使用しているかどうか
} MASK;


//========================================================
//プロトタイプ宣言
//========================================================
void InitMask(void);
void UninitMask(void);
void UpdateMask(void);
void DrawMask(void);
void SetMask(D3DXVECTOR3 pos, MASKTYPE nType, float fWidth, float fHeight);
MASK *GetMask(void);
#endif //!_MASK_H_
