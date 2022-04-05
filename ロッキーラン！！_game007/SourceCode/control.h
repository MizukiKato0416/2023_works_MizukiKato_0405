//=============================================================================
// コントロール処理 [control.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "main.h"

//前方宣言
class CScene;

//*****************************************************************************
// コントロールクラス
//*****************************************************************************
class CControl
{
public:
	CControl();									// コンストラクタ
	virtual ~CControl();						// デストラクタ
	virtual HRESULT Init(void) = 0;				// 初期化処理
	virtual void Uninit(void) = 0;				// 終了処理
	virtual void Update(CScene *pScene) = 0;	// 更新処理
	D3DXVECTOR3 GetMove(void);					// 移動量の取得処理

protected:
	D3DXVECTOR3 m_move;				// 移動量
};

#endif	//_CONTROL_H_