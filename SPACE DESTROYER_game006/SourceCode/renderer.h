//===========================================
//描画処理
//Authore:加藤瑞葵
//===========================================
#ifndef _RENDERER_H_
#define _RENDERER_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CRenderer
{
public:
	CRenderer();			//コンストラクタ
	~CRenderer();			//デストラクタ

	//メンバ関数
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

private:
#ifdef _DEBUG
	void DrawFPS(void);
	void DrawFrame(void);
#endif

	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	
#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
#endif
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_RENDERER_H_