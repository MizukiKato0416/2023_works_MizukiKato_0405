//=============================================================================
// タイトル2P画像コントロール処理 [control_title_2p.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_2P_H_
#define _CONTROL_TITLE_2P_H_

#include "control.h"

//================================================
//マクロ定義
//================================================
#define TITLE_2P_GRAVITY	(0.1f)	//重力
#define TITLE_2P_RISE		(9.5f)	//上昇量
#define TITLE_2P_STOP_TIME	(90)	//ストップさせる時間

//================================================
//前方宣言
//================================================
class CScene;

//*****************************************************************************
// タイトル2P画像コントロールクラス
//*****************************************************************************
class CControlTitle2P : public CControl
{
public:
	CControlTitle2P();					// コンストラクタ
	~CControlTitle2P();					// デストラクタ
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(CScene *pScene);		// 更新処理
	static CControlTitle2P *Create();	// 生成処理

private:
	int m_nStop;						// 最初にストップさせる時間
};

#endif	//_CONTROL_TITLE_2P_H_