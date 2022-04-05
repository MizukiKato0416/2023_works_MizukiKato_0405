//=======================================================================
//ハイスコアに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _HISCORE_H_
#define _HISCORE_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_HI_SCORE_POLYGON (8)			//スコアのポリゴンの最大数
#define HI_SCORE_POLYGON_HEIGHT (70.0f)	//スコアのポリゴンの縦の大きさ
#define HI_SCORE_POLYGON_WIDTH (35.0f)		//スコアのポリゴンの横の大きさ
#define HI_SCORE_POLYGON_POS_WIDTH (800.0f)		//スコアのポリゴンの横の大きさ
#define HI_SCORE_POLYGON_POS_HEIGHT (450.0f)		//スコアのポリゴンの横の大きさ


//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
} HiScore;


//========================================================
//プロトタイプ宣言
//========================================================
void InitHiScore(void);
void UninitHiScore(void);
void UpdateHiScore(void);
void DrawHiScore(void);
void SetHiScore(int nHiScore);

//Score *GetScore(void)

#endif //!_HISCORE_H_

