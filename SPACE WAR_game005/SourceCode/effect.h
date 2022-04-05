//=======================================================================
//ビルボードに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define EFFECT_WIDTH (1.0f)			//エフェクトの幅
#define EFFECT_HEIGHT (1.0f)		//エフェクトの高さ
#define EFFECT_DEPTH (0.0f)			//エフェクトの奥行
#define EFFECT_TYPE (1)				//エフェクトの種類
#define MAX_EFFECT (10000)			//エフェクトの最大数

//========================================================
//動きの種類
//========================================================
typedef enum
{
	EFFEFCT_MOVETYPE_ENEMY_APPEAR = 0,	//敵が出現したとき
	EFFEFCT_MOVETYPE_ENEMY_DEATH,		//敵が死んだとき
	EFFEFCT_MOVETYPE_PLAYER_HOVER,		//プレイヤーのホバー
	EFFEFCT_MOVETYPE_PLAYER_LIFE_LOW,	//プレイヤーの体力が少ないとき
	EFFEFCT_MOVETYPE_PLAYER_DOWN,		//プレイヤーがダウンしたとき
	EFFEFCT_MOVETYPE_BULLET,			//弾の軌道
	EFFEFCT_MOVETYPE_MAX,
} EFFECT_MOVETYPE;

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 scale;		//スケール
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	int nLife;				//寿命
	float fWidth;			//エフェクトの横幅
	float fHeight;			//エフェクトの縦幅
	float fDepth;			//エフェクトの奥行
	bool bUse;				//使用状態
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用
	EFFECT_MOVETYPE nType;	//タイプ

} EFFECT;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, D3DXCOLOR col, int nLife, EFFECT_MOVETYPE nType);
EFFECT *GetEffect(void);

#endif // !_EFFECT_H_