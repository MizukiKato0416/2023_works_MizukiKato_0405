//=======================================================================
//ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "main.h"

//========================================================
////マクロ定義
//========================================================
#define MAX_LIFE (1)		//ゲージの最大数
#define MAX_TYPE (1)		//ゲージの種類
//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	GAUGETYPE_PLAYER = 0,			//プレイヤー
	GAUGETYPE_MAX,
} GAUGETYPE;

//========================================================
//爆発のの構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	GAUGETYPE nType;			//タイプ
	float fWidth;				//幅
	float fHeight;				//高さ
	bool bUse;					//使用しているかどうか
} Life;


//========================================================
//プロトタイプ宣言
//========================================================
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);
void SetLife(D3DXVECTOR3 pos, GAUGETYPE nType, float fWidth, float fHeight);
Life *GetLife(void);
#endif //!_LIFE_H_
