//=======================================================================
//弾に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define BULLET_WIDTH (1.0f)		//弾の幅
#define BULLET_HEIGHT (1.0f)	//弾の高さ
#define BULLET_DEPTH (0.0f)		//弾の奥行
#define BULLET_TYPE (1)			//弾の種類
#define MAX_BULLET (100)		//弾の最大数


//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 scale;		//スケール
	D3DXVECTOR3 move;		//移動量
	float fWidth;			//壁の横幅
	float fHeight;			//壁の縦幅
	float fDepth;			//壁の奥行
	bool bUse;				//使用状態
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	D3DXMATRIX mtxView;		//ビューマトリックス取得用

} BULLET;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight);
BULLET *GetBullet(void);

#endif // !_BULLET_H_