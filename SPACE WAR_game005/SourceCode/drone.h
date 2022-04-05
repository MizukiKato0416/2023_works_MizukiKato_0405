//=======================================================================
//ドローンに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _DRONE_H_
#define _DRONE_H_
#include "main.h"
#include "effect.h"

//========================================================
//マクロ定義
//========================================================
#define DRONE_SPEED (1.0f)								//ドローンの速さ
#define MAX_DRONE (6)									//ドローンの最大数
#define DRONE_MAX_TEXTURE (256)							//テクスチャの最大数
#define DRONE_SEARCH (900.0f)							//プレイヤーを探し出す範囲
#define DRONE_ATTACK (200.0f)							//プレイヤーに攻撃をする範囲
#define DRONE_RAND (float (rand() % 629 + -314) / 100)	//ランダム値
#define DRONE_STOP_TIME (rand() % 300 + 150)			//敵がストップしてる時間
#define DRONE001_LIFE (3)								//ドローン001の体力
#define DRONE002_LIFE (3)								//ドローン002の体力
#define DRONE003_LIFE (10)								//ドローン003の体力

//========================================================
//動きの種類
//========================================================
typedef enum
{
	DRONE_MOVETYPE_MOVE = 0,			//動く
	DRONE_MOVETYPE_STOP,				//止まる
	DRONE_MOVETYPE_TURN,				//回る
	DRONE_MOVETYPE_TO_PLAYER_TURN,		//プレイヤーの方向に向く
	DRONE_MOVETYPE_TO_PLAYER,			//プレイヤーに向かって動く
	DRONE_MOVETYPE_ATTACK,				//攻撃
	DRONE_MOVETYPE_DAMAGE,				//ダメージ食らったとき
	DRONE_MOVETYPE_MAX,
} DRONE_MOVETYPE;

//========================================================
//ドローンの種類
//========================================================
typedef enum
{
	DRONETYPE_001 = 0,		//高いビル
	DRONETYPE_002,			//高いビル
	DRONETYPE_003,			//
	DRONETYPE_MAX,
} DRONETYPE;

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	LPD3DXMESH pMesh;						//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER pBuffMat;					//マテリアル(材質情報)へのポインタ
	DWORD nNumMat;							//マテリアル数
	LPDIRECT3DTEXTURE9 pTexture[DRONE_MAX_TEXTURE];	//テクスチャへのポインタ
	D3DXVECTOR3	pos;						//位置
	D3DXVECTOR3	posOld;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nIdxParent;							//親のインデックス
	D3DXVECTOR3 vtxMin;						//ドローンの頂点の最小値
	D3DXVECTOR3 vtxMax;						//ドローンの頂点の最大値
	bool bUse;								//使うか使わないか
	DRONETYPE Type;							//ドローンの種類
	DRONE_MOVETYPE MoveType;				//ドローンの動きの種類
	float fWidth;							//幅
	float fHeight;							//高さ
	float fDepth;							//奥行
	int nNum;								//影
	bool bTurnDrone;						//回転の慣性
	bool bTurnDrone2;						//接敵してないときの慣性
	bool bDamage;							//ダメージを受けているかどうか
	int nCntStop;							//止まってる時間をカウントする変数
	int nCntMoveTime;						//動いている時間をカウントする変数
	int nLife;								//体力
	float fNumTurnDrone;					//目的のrot
	float fNumDrone;						//目的と現在のrotの差
	float fToPlayerR;						//プレイヤーとの距離
	float fDifferRot;						//目的と現在のrotの差
	float frotVecX;							//プレイヤーの角度を求めるためのベクトル
	float frotVecZ;							//プレイヤーの角度を求めるためのベクトル
	int nIdx;								//影
	int nIdxLife;							//体力ゲージ
	int nIdxEffect[MAX_EFFECT];				//パーティクル
} DRONE;

//========================================================
//プロトタイプ宣言
//========================================================
void InitDrone(void);
void UninitDrone(void);
void UpdateDrone(void);
void DrawDrone(void);
void MoveTypeDrone(int nCntDrone);
void SetDrone(D3DXVECTOR3 pos, D3DXVECTOR3 rot, DRONETYPE Type);
void CollisionDrone(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth);
DRONE *GetDrone(void);
int GetAllDrone(void);

#endif // !_DRONE_H_