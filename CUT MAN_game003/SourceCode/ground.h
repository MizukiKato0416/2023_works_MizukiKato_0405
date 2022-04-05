//=======================================================================
//メッシュフィールドに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _GROUND_H_
#define _GROUND_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define GROUND_WIDTH (3200.0f*1.0f)		//メッシュフィールドの幅
#define GROUND_HEIGHT (0.0f*1.0)		//メッシュフィールドの高さ
#define GROUND_DEPTH (3200.0f*1.0f)		//メッシュフィールドの奥行
#define GROUND_X (20)					//Xの数
#define GROUND_Z (20)					//Zの数
#define GROUND_TYPE (1)					//メッシュフィールドの種類
#define MAX_GROUND (1)					//メッシュフィールドの最大数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nTileX;				//横のタイル数
	int nTileZ;				//奥行のタイル数
	float fWidth;			//ブロックの横幅
	float fHeight;			//ブロックの縦幅
	float fDepth;			//ブロックの奥行
	bool bUse;				//使うかどうか
} GROUND;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, int nTileX, int nTileZ);
GROUND *GetGround(void);

#endif // !_GROUND_H_