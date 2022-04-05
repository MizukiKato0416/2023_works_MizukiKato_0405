//=======================================================================
//敵体力ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _ENEMYLIFE_H_
#define _ENEMYLIFE_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define ENEMYLIFE_WIDTH (1.0f)		//ゲージの幅
#define ENEMYLIFE_HEIGHT (1.0f)		//ゲージの高さ
#define ENEMYLIFE_DEPTH (0.0f)		//ゲージの奥行
#define ENEMYLIFE_TYPE (1)			//ゲージの種類
#define MAX_ENEMYLIFE (50)			//ゲージの最大数


//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 scale;		//スケール
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//ゲージの横幅
	float fHeight;			//ゲージの縦幅
	float fDepth;			//ゲージの奥行
	bool bUse;				//使用状態
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用
	int nShadow;			//影

} EnemyLife;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitEnemyLife(void);
void UninitEnemyLife(void);
void UpdateEnemyLife(void);
void DrawEnemyLife(void);
int SetEnemyLife(D3DXVECTOR3 pos, float fWidth, float fHeight);
void SetPositionEnemyLife(int nIdx, D3DXVECTOR3 pos, bool bUse, int nMaxlife, int nLife, float fWidth);
EnemyLife *GetEnemyLife(void);

#endif // !_ENEMYLIFE_H_