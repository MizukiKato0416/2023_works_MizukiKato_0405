//=======================================================================
//メニューに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _MENU_H_
#define _MENU_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_MENU (6)			//メニューの最大数
#define MENU_TYPE (6)			//メニューの種類の数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int nCounterAnim = 0;	//アニメーションカウンタ
	int nPatternAnim = 0;	//アニメーションパターンNo
	int nType;				//種類
	float fMenuWidth;		//メニューの横幅
	float fMenuHeight;		//メニューの縦幅
	bool bUse;				//使うかどうか
	bool bSelectUse;		//選択されているかどうか
} Menu;

//========================================================
//プロトタイプ宣言
//========================================================
void InitMenu(void);
void UninitMenu(void);
void UpdateMenu(void);
void DrawMenu(void);
void SetMenu(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fMenuWidth, float fMenuHeight);
Menu *GetMenu(void);

#endif //!_MENU_H_

