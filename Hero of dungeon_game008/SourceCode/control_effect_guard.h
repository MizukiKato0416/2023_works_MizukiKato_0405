//=============================================================================
// ガードエフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_GUARD_H_
#define _CONTROL_EFFECT_GUARD_H_
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
class CControlEffectGuard : public CControl
{
public:
	//メンバ関数
	CControlEffectGuard();			//コンストラクタ	
	~CControlEffectGuard();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectGuard *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_GUARD_H_