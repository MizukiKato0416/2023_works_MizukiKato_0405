//=======================================================================
//進化ゲージに関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _EVOLUTIONGAUGE_H_
#define _EVOLUTIONGAUGE_H_
#include "main.h"

//========================================================
////マクロ定義
//========================================================
#define MAX_EVOLUTIONGAUGE (1)			//ゲージの最大数
#define MAX_EVOLUTIONGAUGE_ADD (20)		//ゲージのたまる最大数
#define EVOLUTIONGAUGE_WIDTH (450.0f)	//ゲージの横幅
#define EVOLUTIONGAUGE_HEIGHT (50.0f)	//ゲージの縦幅

//========================================================
//ゲージの種類
//========================================================
typedef enum
{
	EVOLUTION_GAUGETYPE_PLAYER = 0,			//プレイヤー
	EVOLUTION_GAUGETYPE_MAX,
} EVOLUTION_GAUGETYPE;

//========================================================
//爆発のの構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	EVOLUTION_GAUGETYPE nType;		//タイプ
	float fWidth;					//幅
	float fHeight;					//高さ
	float fCnt;						//現在のゲージ量
	bool bUse;						//使用しているかどうか
	bool bGaugeMax;					//ゲージがマックスかどうか
	bool bEvolution;				//進化中かどうか
	int nTransparency;				//透明度
	int nCounter;					//透明度を変えるカウンター
} EvolutionGauge;

//========================================================
//プロトタイプ宣言
//========================================================
void InitEvolutionGauge(void);
void UninitEvolutionGauge(void);
void UpdateEvolutionGauge(void);
void DrawEvolutionGauge(void);
void SetEvolutionGauge(D3DXVECTOR3 pos, EVOLUTION_GAUGETYPE nType, float fWidth, float fHeight);
void SetAddEvolutionGauge(float fGauge);
EvolutionGauge *GetEvolutionGauge(void);
#endif //!_EVOLUTIONGAUGE_H_
