//=======================================================================
//ビルボードに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
//========================================================
//マクロ定義
//========================================================
#define BILLBOARD_WIDTH (1.0f)		//壁の幅
#define BILLBOARD_HEIGHT (1.0f)		//壁の高さ
#define BILLBOARD_DEPTH (0.0f)		//壁の奥行
#define BILLBOARD_TYPE (1)			//壁の種類
#define MAX_BILLBOARD (255)			//壁の最大数


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
	int nShadow;			//影

} BILLBOARD;


//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight);
BILLBOARD *GetBillboard(void);

#endif // !_BILLBOARD_H_