//=======================================================================
//メッシュフィールドに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define MESHFIELD_WIDTH (800.0f*1.0)		//メッシュフィールドの幅
#define MESHFIELD_HEIGHT (0.0f*1.0)			//メッシュフィールドの高さ
#define MESHFIELD_DEPTH (800.0f*1.0f)		//メッシュフィールドの奥行
#define MESHFIELD_X (255)						//Xの数
#define MESHFIELD_Z (255)						//Zの数
#define MESHFIELD_TYPE (1)					//メッシュフィールドの種類
#define MAX_MESHFIELD (1)					//メッシュフィールドの最大数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float fWidth;			//ブロックの横幅
	float fHeight;			//ブロックの縦幅
	float fDepth;			//ブロックの奥行
	bool bUse;				//使うかどうか
} MESHFIELD;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);
MESHFIELD *GetMeshField(void);

#endif // !_MESHFIELD_H_