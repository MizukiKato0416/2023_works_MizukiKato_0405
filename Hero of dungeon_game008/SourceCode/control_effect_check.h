//=============================================================================
// チェックポイントのエフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_CHECK_H_
#define _CONTROL_EFFECT_CHECK_H_
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
class CControlEffectCheck : public CControl
{
public:
	//メンバ関数
	CControlEffectCheck();			//コンストラクタ	
	~CControlEffectCheck();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectCheck *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_CHECK_H_