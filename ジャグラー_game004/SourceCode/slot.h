//=======================================================================
//スロット部分に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#ifndef _SLOT_H_
#define _SLOT_H_

//========================================================
//マクロ定義
//========================================================
#define MAX_SLOT (4)				//スロットの最大数
#define SLOT_SPEED0 (0.002f)		//スロットの初期の速さ
#define SLOT_SPEED1 (-0.003f)		//スロットの初期の速さ
#define SLOT_SPEED2 (0.004f)		//スロットの初期の速さ
#define SLOT_SPEED3 (-0.005f)		//スロットの初期の速さ
#define SLOT_ACCEL (1.5f)			//スロットの加速度

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動速度
	D3DXVECTOR3 firstmove;	//移動速度の初期値
	float fTexU;			//テクスチャのU
	float fStopTexU;		//テクスチャのUが止まる場所
	float fWidth;			//幅
	float fHeight;			//高さ
	bool bUse;				//使っているかどうか
	bool bSpin;				//回っているかどうか
	bool bStop;				//ストップさせているかどうか
} SLOT;

//========================================================
//プロトタイプ宣言
//========================================================
void InitSlot(void);
void UninitSlot(void);
void UpdateSlot(void);
void DrawSlot(void);
void SetSlot(D3DXVECTOR3 pos, float fWidth, float fHeight);
SLOT *GetSlot(void);

#endif // !_SLOT_H_
