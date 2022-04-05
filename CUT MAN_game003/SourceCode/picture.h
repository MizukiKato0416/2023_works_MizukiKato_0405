//=======================================================================
//静止画に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _PICTURE_H_
#define _PICTURE_H_
#include "main.h"

//========================================================
////マクロ定義
//========================================================
#define MAX_PICTURE (1)			//PICTUREの最大数
//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	PICTURETYPE_SETSUNEI = 0,	//画面情報
	PICTURETYPE_SOUSA,			//操作説明
	PICTURETYPE_TAOSE,			//煽り文句
	PICTURETYPE_MAX,
} PICTURETYPE;

//========================================================
//爆発のの構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	PICTURETYPE nType;			//タイプ
	float fWidth;				//幅
	float fHeight;				//高さ
	bool bUse;					//使用しているかどうか
} PICTURE;


//========================================================
//プロトタイプ宣言
//========================================================
void InitPicture(void);
void UninitPicture(void);
void UpdatePicture(void);
void DrawPicture(void);
PICTURE *GetPicture(void);
#endif //!_PICTURE_H_
