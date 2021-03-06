//===========================================
//入力処理
//Author:加藤瑞葵
//===========================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CInput
{
public:
	CInput();				//コンストラクタ
	virtual ~CInput();			//デストラクタ

	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;


protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;
	static LPDIRECTINPUT8 m_pInput;
};

#endif // !_INPUT_H_