//=============================================================================
// ヒットエフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_HIT_H_
#define _CONTROL_EFFECT_HIT_H_
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
class CControlEffectHit : public CControl
{
public:
	//メンバ関数
	CControlEffectHit();			//コンストラクタ	
	~CControlEffectHit();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectHit *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_HIT_H_