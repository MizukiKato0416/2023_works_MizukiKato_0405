//===========================================
//マウス入力処理
//Author:KatoMizuki
//===========================================
#ifndef _INPUT_MOUSE_H_
#define _INPUT_MOUSE_H_
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
class CInputMouse : public CInput
{
public:
	typedef enum
	{
		MOUSE_TYPE_LEFT = 0,
		MOUSE_TYPE_RIGHT,
		MOUSE_TYPE_WHEEL,
		MOUSE_TYPE_MAX
	} MOUSE_TYPE;

	CInputMouse();			//コンストラクタ
	~CInputMouse();			//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nMouse);
	bool GetTrigger(int nMouse);
	bool GetRelease(int nMouse);
	DIMOUSESTATE2 GetMouseState(void);	//マウスの入力情報取得処理

	D3DXVECTOR2 GetMouseVelocity(void);	//マウスの移動量取得処理

private:
	DIMOUSESTATE2 m_mouseState;
	DIMOUSESTATE2 m_mouseStateTrigger;			//マウスの入力情報
	DIMOUSESTATE2 m_mouseStateRelease;			//マウスの入力情報
};

#endif // !_INPUT_MOUSE_H_