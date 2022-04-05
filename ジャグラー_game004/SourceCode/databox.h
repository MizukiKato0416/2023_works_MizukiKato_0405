#ifndef _DATABOX_H_
#define _DATABOX_H_

#include "main.h"

typedef enum
{
	EAWASE_ANIMALS = 0,
	EAWASE_SHAPE,
	EAWASE_CARS,
	EAWASE_MAX
}Eawase;

//総括データ++++++++++++++++++++++++++++

typedef struct
{
	bool bPause;		//ポーズ
	int nFever;			//フィーバーゲージ(MAX300)
	bool bFever;		//フィーバー中か判別
	int nFeverTime;		//フィーバー終了までの残り時間
	bool nTitleNum;		//タイトル番号
	bool bFeverMan;
	bool bOK;
}Data;

//---------------------------------

//プロトタイプ宣言
void Initdata(void);		//完全初期化
void Resetdata(void);		//初期化
Data *GetData(void);

#endif //_DATABOX_H_