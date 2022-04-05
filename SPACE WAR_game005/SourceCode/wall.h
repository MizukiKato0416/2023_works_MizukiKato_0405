//=======================================================================
//壁に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define WALL_WIDTH (800.0f)		//壁の幅
#define WALL_HEIGHT (600.0f)	//壁の高さ
#define WALL_DEPTH (0.0f)		//壁の奥行
#define WALL_TYPE (1)			//壁の種類
#define MAX_WALL (4)			//壁の最大数


//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 scale;		//スケール
	float fWidth;			//壁の横幅
	float fHeight;			//壁の縦幅
	float fDepth;			//壁の奥行
	bool bUse;				//使用状態
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	int nNum;				//壁構造体
} WALL;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);

#endif // !_WALL_H_