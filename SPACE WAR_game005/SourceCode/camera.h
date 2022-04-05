//=======================================================================
//カメラに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_CAMERA (1)				//カメラの最大数
#define CAMERA_R_SPEED (0.03f)		//カメラの旋回スピード
#define CAMERA_VR_SPEED (7.0f)		//カメラの移動
#define CAMERA_DISTANCE (300.0f)	//視点と注視点の距離

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 posV;			//現在の視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posR;			//現在の注視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotAsk;			//目的の向き
	float rotDiffer;			//目的の向きとの差
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	D3DVIEWPORT9 viewport;		//ビューポート
	float frotVecX;				//敵とカメラのベクトル計算に必要
	float frotVecZ;				//敵とカメラのベクトル計算に必要
	float frotVecXSub;			//敵とカメラのベクトル計算に必要
	float frotVecZSub;			//敵とカメラのベクトル計算に必要
	bool bRockOn;				//ロックオンしているかどうか
	int nWhoRockOn;				//ロックオンしている対象が誰なのか
	int nCntEnemyDrone;			//敵とドローンの合計の数
	int nEnemyNumber;			//敵とドローンのナンバー保存変数
	float fToPlayerR;			//敵とプレイヤーとの距離保存用

	float ftest;				//テスト用
} Camera;

//========================================================
//プロトタイプ宣言
//========================================================
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(int nIdx);
void DrawCameratxt(void);
Camera *GetCamera(void);

#endif //!_CAMERA_H_

