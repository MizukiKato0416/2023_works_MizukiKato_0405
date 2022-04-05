//=======================================================================
//ランキングに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _RUNKING_H_
#define _RUNKING_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_RUNKING_POLYGON (8)			//スコアのポリゴンの最大数
#define MAX_RUNKING (6)					//ランキングの最大数
#define RUNKING_POLYGON_HEIGHT (60.0f)	//スコアのポリゴンの縦の大きさ
#define RUNKING_POLYGON_WIDTH (45.0f)		//スコアのポリゴンの横の大きさ
#define RUNKING_RESULT_POS_WIDTH (800.0f)	//リザルト画面でのポリゴンのX座標
#define RUNKING_RESULT_POS_HEIGHT (320.0f)	//リザルト画面でのポリゴンのY座標

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int score;			//スコア
	bool bUse;			//使うかどうか
} Runking;


//========================================================
//プロトタイプ宣言
//========================================================
void InitRunking(void);
void UninitRunking(void);
void UpdateRunking(void);
void DrawRunking(void);
void SetRunking(int nRunking);
//Runking *GetRunking(void)

#endif //!_RUNKING_H_
