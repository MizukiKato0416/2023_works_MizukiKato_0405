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
#define MAX_ENEMY_BULLET (128)				//弾の最大数
#define ENEMY_BULLET_WIDTH_HEIGHT (30.0f)		//正方形の弾の縦の大きさ
#define MAX_ENEMY_BULLET_TYPE (14)		//弾の種類

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 move;			//移動量
	int nType;					//種類
	float EnemyBulletHeight;	//弾の縦の大きさ
	float EnemyBulletWidth;		//弾の横の大きさ
	bool bUse;					//使用しているかどうか
} EnemyBullet;

//========================================================
//プロトタイプ宣言
//========================================================
void InitEnemyBullet(void);
void UninitEnemyBullet(void);
void UpdateEnemyBullet(void);
void DrawEnemyBullet(void);
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int type, float EnemyBulletHeight, float EnemyBulletWidth);
EnemyBullet *GetEnemyBullet(void);

#endif //!_ENEMYBULLET_H_

