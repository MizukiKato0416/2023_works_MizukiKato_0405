#//=============================================================================
// メニュー星コントロール処理 [control_menu_star.h]
// Author : 寺下琉生
//=============================================================================
#ifndef _CONTROL_MENU_STAR_H_
#define  _CONTROL_MENU_STAR_H_

#include "control.h"

//================================================
//前方宣言
//================================================
class CScene;

//================================================
//マクロ定義
//================================================
#define STAR_COL				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//表示
#define STAR_HIDE				(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))		//非表示
#define STAR_LOWERLIMIT_POSY	(510.0f)								//posYの下限
//*****************************************************************************
// メニュー星コントロールクラス
//*****************************************************************************
class CControlMenuStar : public CControl
{
public:
	CControlMenuStar();					// コンストラクタ
	~CControlMenuStar();				// デストラクタ
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(CScene *pScene);		// 更新処理
	static CControlMenuStar *Create();	// 生成処理

private:
	D3DXCOLOR m_col;					//色
	float m_fMaxMoveX;					// 移動量の最大値X
	float m_fMaxMoveY;					// 移動量の最大値X
	int m_nFrame;						//フレーム数
};

#endif	//_CONTROL_TITLE_LOGO_H_