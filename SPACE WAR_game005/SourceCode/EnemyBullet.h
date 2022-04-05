//=======================================================================
//敵の弾に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _ENEMYBULLET_H_
#define _ENEMYBULLET_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define ENEMYBULLET_WIDTH (1.0f)		//弾の幅
#define ENEMYBULLET_HEIGHT (1.0f)	//弾の高さ
#define ENEMYBULLET_DEPTH (0.0f)		//弾の奥行
#define ENEMYBULLET_TYPE (1)			//弾の種類
#define MAX_ENEMYBULLET (100)		//弾の最大数
#define ENEMYBULLET_SPEED (20.0f)	//弾の速さ

//========================================================
//動きの種類
//========================================================
typedef enum
{
	ENEMYBULLET_MOVETYPE_DRONE001 = 0,	//ドローン001
	ENEMYBULLET_MOVETYPE_DRONE002,		//ドローン002
	ENEMYBULLET_MOVETYPE_DRONE003,		//ドローン003
	ENEMYBULLET_MOVETYPE_BOSS_SMALL,	//ボス普通
	ENEMYBULLET_MOVETYPE_BOSS_BIG,		//ボス特大
	ENEMYBULLET_MOVETYPE_MAX,
} ENEMYBULLET_MOVETYPE;

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 scale;				//スケール
	D3DXVECTOR3 move;				//移動量
	float fWidth;					//壁の横幅
	float fHeight;					//壁の縦幅
	float fDepth;					//壁の奥行
	bool bUse;						//使用状態
	D3DXMATRIX mtxWorld;			//ワールドマトリックス
	D3DXMATRIX mtxView;				//ビューマトリックス取得用
	D3DXCOLOR col;					//カラー
	ENEMYBULLET_MOVETYPE nType;		//弾の動き
	float fFarPlayer;				//プレイヤーとの距離
} ENEMYBULLET;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
int CollisionEnemyBullet(D3DXVECTOR3 *pPos, float fWidth);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight , D3DXCOLOR col, ENEMYBULLET_MOVETYPE nType);
ENEMYBULLET *GetEnemyBullet(void);

#endif // !_ENEMYBULLET_H_