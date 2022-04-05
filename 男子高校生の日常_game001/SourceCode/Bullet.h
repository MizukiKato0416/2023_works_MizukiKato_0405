//=======================================================================
//プレイヤーの弾に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//========================================================
//プロトタイプ宣言
//========================================================
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int nType, float BulletHeight, float BulletWidth);

#endif //!_BULLET_H_
