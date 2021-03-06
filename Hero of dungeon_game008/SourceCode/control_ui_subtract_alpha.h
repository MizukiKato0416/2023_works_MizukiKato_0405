//=============================================================================
// ヒットエフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_UI_SUBTRACT_ALPHA_H_
#define _CONTROL_UI_SUBTRACT_ALPHA_H_
#include "control.h"

//前方宣言
class CObject;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CControlUiSubtractAlpha : public CControl
{
public:
	//メンバ関数
	CControlUiSubtractAlpha();			//コンストラクタ	
	~CControlUiSubtractAlpha();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlUiSubtractAlpha *Create(CObject *pObject, float fSubtractAlpha, int nDelay);

private:
	float m_fSubtractAlpha;		//α値減算値
	int m_nDelay;				//ディレイ
	int m_nDelayCounter;		//ディレイのカウンター
};

#endif	//_CONTROL_UI_SUBTRACT_ALPHA_H_