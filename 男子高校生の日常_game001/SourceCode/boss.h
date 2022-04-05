//=======================================================================
//ボスに関する処理
//Aouthor:　加藤　瑞葵
//=======================================================================

#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_BOSS (1)		//敵の最大数
#define BOSS_HEIGHT (450.0f)	//敵の縦の大きさ
#define BOSS_WIDTH (400.0f)	//敵の横の大きさ

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nCounterAnim = 0;	//アニメーションカウンタ
	int nPatternAnim = 0;	//アニメーションパターンNo
	int nType;			//種類
	int nLife;			//体力
	bool bUse;			//使うかどうか
} Boss;

//========================================================
//プロトタイプ宣言
//========================================================
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move,int nLife);
Boss *GetBoss(void);

#endif //!_BOSS_H_

