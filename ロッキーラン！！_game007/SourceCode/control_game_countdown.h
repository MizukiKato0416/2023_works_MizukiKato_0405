//=============================================================================
// ゲームカウントダウン文字コントロール処理 [control_game_countdown.h]
// Author :寺下琉生
//=============================================================================
#ifndef _CONTROL_GAME_COUNTDOWN_H_
#define _CONTROL_GAME_COUNTDOWN_H_

#include "control.h"

//前方宣言
class CScene;

//*****************************************************************************
// ゲームカウントダウンコントロールクラス
//*****************************************************************************
class CControlGameCountdown : public CControl
{
public:
	CControlGameCountdown();					// コンストラクタ
	~CControlGameCountdown();					// デストラクタ
	HRESULT Init(void);						// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(CScene *pScene);			// 更新処理
	static CControlGameCountdown *Create();	// 生成処理

private:
	typedef enum
	{
		COUNTDOWN_03=0,
		COUNTDOWN_02,
		COUNTDOWN_01,
		COUNTDOUN_MAX
	} COUNTDOWN;

	float m_fMaxMove;						// 移動量の最大値
	int m_nCount;							// カウント
	D3DXCOLOR m_col;						//ポリゴンの色
};

#endif	//_CONTROL_TITLE_LOGO_H_