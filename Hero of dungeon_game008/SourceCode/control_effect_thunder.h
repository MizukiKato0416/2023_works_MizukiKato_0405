//=============================================================================
// 雷エフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_THUNDER_H_
#define _CONTROL_EFFECT_THUNDER_H_
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
class CControlEffectThunder : public CControl
{
public:
	//メンバ関数
	CControlEffectThunder();			//コンストラクタ	
	~CControlEffectThunder();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectThunder *Create(CObject *pObject);

private:
	int m_nDestroyCounter;				//消えるまでの時間
};

#endif	//_CONTROL_EFFECT_THUNDER_H_