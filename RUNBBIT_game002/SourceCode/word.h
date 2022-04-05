//=======================================================================
//文字表示に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _WORD_H_
#define _WORD_H_
#include "main.h"

//========================================================
//マクロ定義
//========================================================
#define MAX_WORD (5)			//文字の最大数
#define WORD_TYPE (6)			//文字の種類の数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	int nType;			//種類
	int nCnt;			//カウント
	float fWordWidth;	//敵の横幅
	float fWordHeight;	//敵の縦幅
	bool bUse;			//使うかどうか
} Word;

//========================================================
//プロトタイプ宣言
//========================================================
void InitWord(void);
void UninitWord(void);
void UpdateWord(void);
void DrawWord(void);
void SetWord(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move, float fWordWidth, float fWordHeight);
Word *GetWord(void);

#endif //!_WORD_H_

