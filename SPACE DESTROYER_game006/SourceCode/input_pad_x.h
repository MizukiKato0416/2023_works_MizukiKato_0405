//===========================================
//パッド入力処理
//Authore:加藤瑞葵
//===========================================
#ifndef _INPUT_PAD_X_H_
#define _INPUT_PAD_X_H_
#include "input.h"

//================================================
//マクロ定義
//================================================
#define NUM_KEY_MAX (256)		//キーの最大数


//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CInputPadX : public CInput
{
public:
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

	CInputPadX();			//コンストラクタ
	~CInputPadX();			//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetButtonPress(int nButton);
	bool GetButtonTrigger(int nButton);
	bool GetTriggerPress(int nTrigger);
	bool GetTriggerTrigger(int nTrigger);
	bool GetLeftStick(int nLstick);
	bool GetLeftStickTrigger(int nLstick);
	bool GetLeftStickRelease(int nLstick);
	bool GetRightStick(int nRstick);
	void SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd);

private:
	XINPUT_STATE m_state;
	XINPUT_STATE m_stateLast;
	XINPUT_VIBRATION m_vibration;
	bool m_bConnect;
	int m_nCntVibration;
	bool m_bVibration;
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_INPUT_PAD_X_H_