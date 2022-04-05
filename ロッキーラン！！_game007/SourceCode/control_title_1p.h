//=============================================================================
// タイトル1P画像コントロール処理 [control_title_1p.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_1P_H_
#define _CONTROL_TITLE_1P_H_

#include "control.h"

//================================================
//マクロ定義
//================================================
#define TITLE_1P_GRAVITY	(0.1f)		//重力
#define TITLE_1P_RISE		(9.0f)		//上昇量

//================================================
//前方宣言
//================================================
class CScene;

//*****************************************************************************
// タイトル1P画像コントロールクラス
//*****************************************************************************
class CControlTitle1P : public CControl
{
public:
	CControlTitle1P();					// コンストラクタ
	~CControlTitle1P();					// デストラクタ
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(CScene *pScene);		// 更新処理
	static CControlTitle1P *Create();	// 生成処理
};

#endif	//_CONTROL_TITLE_1P_H_