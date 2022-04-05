//=======================================================================
//影に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define SHADOW_WIDTH (90.0f*1.0f)		//影の幅
#define SHADOW_HEIGHT (0.0f*0.0f)		//影の高さ
#define SHADOW_DEPTH (90.0f*1.0f)		//影の奥行
#define SHADOW_TYPE (1)					//影の種類
#define MAX_SHADOW (128)					//影の最大数


//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリックス
	float fWidth;			//影の横幅
	float fHeight;			//影の縦幅
	float fDepth;			//影の奥行
	int nType;				//影のタイプ
	bool bUse;				//使うかどうか
} SHADOW;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos, bool bUse);
SHADOW *GetShadow(void);

#endif // !_SHADOW_H_