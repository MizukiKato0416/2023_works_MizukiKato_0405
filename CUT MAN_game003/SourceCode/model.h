//=======================================================================
//モデルに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MODEL_SPEED (3.0f)			//モデルの速さ
#define MAX_MODEL (10)				//モデルの最大数
#define MODEL_MAX_TEXTURE (256)		//テクスチャの最大数

//========================================================
//モデルの種類
//========================================================
typedef enum
{
	BUILDING_HIGH = 0,			//高いビル
	BUILDING_HIGH_02,			//高いビル
	BUILDING_LOW,				//低いビル
	BUILDING_LOW_02,			//低いビル
	CAR,						//車
	TYPE_MAX,
} MODELTYPE;

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;					//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[MODEL_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nIdxModelParent;			//親のインデックス
	D3DXVECTOR3 vtxMin;		//モデルの頂点の最小値
	D3DXVECTOR3 vtxMax;		//モデルの頂点の最大値
	bool bUse;				//使うか使わないか
	MODELTYPE Type;			//モデルの種類
	float fWidth;			//幅
	float fHeight;			//高さ
	float fDepth;			//奥行
	int nNum;				//影
} MODEL;

//========================================================
//プロトタイプ宣言
//========================================================
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE Type);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
MODEL *GetModel(void);

#endif // !_MODEL_H_