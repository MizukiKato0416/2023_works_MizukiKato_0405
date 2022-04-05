//=======================================================================
//入力に関する処理
//Aouthor: 加藤　瑞葵
//=======================================================================

#ifndef _PAD_H_
#define _PAD_H_
#include "main.h"

typedef enum
{
	TRIGGERTYPE_RIGHT = 0,
	TRIGGERTYPE_LEFT,
	TRIGGERTYPE_MAX
} TRIGGERTYPE;
typedef enum
{
	STICKTYPE_UP = 0,
	STICKTYPE_RIGHT,
	STICKTYPE_LEFT,
	STICKTYPE_DOWN,
	STICKTYPE_MAX
} STICKTYPE;

//========================================================
//プロトタイプ宣言
//========================================================
HRESULT InitPad(void);
void UninitPad(void);
void UpdatePad(void);
bool GetButtonPress(int nButton);
bool GetButtonTrigger(int nButton);
bool GetTriggerPress(int nTrigger);
bool GetTriggerTrigger(int nTrigger);
bool GetLeftStick(int nLstick);
bool GetRightStick(int nRstick);
void SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd);

#endif // !_PAD_H_
