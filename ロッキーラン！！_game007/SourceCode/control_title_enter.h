#//=============================================================================
// タイトルエンター文字コントロール処理 [control_title_enter.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_ENTER_H_
#define _CONTROL_TITLE_ENTER_H_

#include "control.h"

//前方宣言
class CScene;

//*****************************************************************************
// タイトルエンターコントロールクラス
//*****************************************************************************
class CControlTitleEnter : public CControl
{
public:
	CControlTitleEnter();					// コンストラクタ
	~CControlTitleEnter();					// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlTitleEnter *Create();	// 生成処理

private:
	int m_nCount;							// カウント
	D3DXCOLOR m_col;						//ポリゴンの色
	bool m_bAlphaUp;						// アルファ度を上げるかどうか
};

#endif	//_CONTROL_TITLE_LOGO_H_