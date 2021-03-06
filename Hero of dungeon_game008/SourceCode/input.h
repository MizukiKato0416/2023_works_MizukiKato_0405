//===========================================
//入力処理
//Author:KatoMizuki
//===========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//構造体の定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CInput
{
public:
	//メンバ関数
	CInput();					//コンストラクタ
	virtual ~CInput();			//デストラクタ

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;


protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUTDEVICE8 m_pDeviceJoyStick;
	static LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_H_