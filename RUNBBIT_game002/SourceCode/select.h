//=======================================================================
//メニュー選択に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _SELECT_H_
#define _SELECT_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_SELECT (1)			//メニュー選択の最大数
#define SELECT_TYPE (1)			//メニュー選択の種類の数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nType;			//種類
	float fSelectWidth;	//メニュー選択の横幅
	float fSelectHeight;	//メニュー選択の縦幅
	bool bUse;			//使うかどうか
	bool bMenu1;			//使うかどうか
	bool bMenu2;			//使うかどうか
	bool bMenu3;			//使うかどうか
} Select;

//========================================================
//プロトタイプ宣言
//========================================================
void InitSelect(void);
void UninitSelect(void);
void UpdateSelect(void);
void DrawSelect(void);
void SetSelect(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fSelectWidth, float fSelectHeight);
Select *GetSelect(void);

#endif //!_SELECT_H_
