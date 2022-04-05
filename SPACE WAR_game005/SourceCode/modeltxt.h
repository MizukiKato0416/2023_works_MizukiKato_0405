//=======================================================================
//モデルに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MODELTXT_H_
#define _MODELTXT_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_MODELTXT (512)				//モデルの最大数
#define MODELTXT_MAX_TEXTURE (512)		//テクスチャの最大数

//========================================================
//モデルの種類
//========================================================
typedef enum
{
	MODELTXTTYPE_BUILDING_HIGH = 0,			//高いビル
	MODELTXTTYPE_BUILDING_HIGH_02,			//高いビル
	MODELTXTTYPE_BUILDING_LOW,				//低いビル
	MODELTXTTYPE_BUILDING_LOW_02,			//低いビル
	MODELTXTTYPE_CAR,						//車
	MODELTXTTYPE_MAX,
} MODELTXTTYPE;

//========================================================
//8頂点の構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos[8];			//8頂点の位置保存用変数
	D3DXVECTOR3 rot[8];			//8頂点の回転保存用変数
	D3DXMATRIX mtxWorld[8];		//8頂点のワールドマトリックス保存用変数
	float fVecX[4];				//当たり判定に使うベクトル
	float fVecX2[4];			//当たり判定に使うベクトル
	float fVecZ[4];				//当たり判定に使うベクトル
	float fVecZ2[4];			//当たり判定に使うベクトル

} VTX;

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;				//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;			//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;					//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[MODELTXT_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	int nIdxModelTxtParent;			//親のインデックス
	D3DXVECTOR3 vtxMin;				//モデルの頂点の最小値
	D3DXVECTOR3 vtxMax;				//モデルの頂点の最大値
	bool bUse;						//使うか使わないか
	MODELTXTTYPE Type;				//モデルの種類
	float fWidth;					//幅
	float fHeight;					//高さ
	float fDepth;					//奥行
	int nNum;						//影
	int nType;						//モデルの種類
	VTX Vtx;						//頂点構造体

} MODELTXT;

//========================================================
//プロトタイプ宣言
//========================================================
void InitModelTxt(void);
void UninitModelTxt(void);
void UpdateModelTxt(void);
void DrawModelTxt(void);
void CollisionModelTxt(D3DXVECTOR3 *pMove, D3DXVECTOR3 *pPosMother, D3DXVECTOR3 *pPosMotherOld, float fWidth);
bool CollisionModelTxtBool(D3DXVECTOR3 *pPos);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
MODELTXT *GetModelTxt(void);

#endif // !_MODELTXT_H_