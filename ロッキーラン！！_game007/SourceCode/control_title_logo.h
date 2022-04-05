#//=============================================================================
// タイトルロゴコントロール処理 [control_title_logo.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_LOGO_H_
#define _CONTROL_TITLE_LOGO_H_

#include "control.h"

//前方宣言
class CScene;

//*****************************************************************************
// タイトルロゴコントロールクラス
//*****************************************************************************
class CControlTitleLogo : public CControl
{
public:
	CControlTitleLogo();					// コンストラクタ
	~CControlTitleLogo();					// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlTitleLogo *Create();	// 生成処理

private:
	float m_fMaxMove;						// 移動量の最大値
};

#endif	//_CONTROL_TITLE_LOGO_H_