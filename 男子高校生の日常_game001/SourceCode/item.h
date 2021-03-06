//=======================================================================
//アイテムに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_ITEM (128)				//アイテムの最大数
#define ITEM_TYPE (4)				//アイテムの種類
#define ITEM_HEIGHT (30.0f)		//アイテムの縦の大きさ
#define ITEM_WIDTH (30.0f)		//アイテムの大きさ

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nType;			//種類
	bool bUse;			//使うかどうか
} Item;

//========================================================
//プロトタイプ宣言
//========================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 move, int ntype);
Item *GetItem(void);

#endif //!_ITEM_H_