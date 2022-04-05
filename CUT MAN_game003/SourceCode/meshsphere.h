//=======================================================================
//メッシュフィールド(球体)に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MESHSPHERE_H_
#define _MESHSPHERE_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define MESHSPHERE_WIDTH (5000.0f*1.0f)		//メッシュフィールドの幅



#define MESHSPHERE_HEIGHT (6000.0f*1.0f)		//メッシュフィールドの高さ
#define MESHSPHERE_DEPTH (1000.0f*1.0f)		//メッシュフィールドの奥行
#define MESHSPHERE_X (32)					//Xの数
#define MESHSPHERE_Y (8)					//Yの数(X / 2 - 1)
#define MESHSPHERE_TYPE (1)					//メッシュフィールドの種類
#define MAX_MESHSPHERE (1)					//メッシュフィールドの最大数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float fWidth;			//ブロックの横幅
	float fHeight;			//ブロックの縦幅
	float fDepth;			//ブロックの奥行
	bool bUse;				//使うかどうか
	
} MESHSPHERE;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitMeshSphere(void);
void UninitMeshSphere(void);
void UpdateMeshSphere(void);
void DrawMeshSphere(void);
MESHSPHERE *GetMeshSphere(void);

#endif // !_MESHSPHERE_H_