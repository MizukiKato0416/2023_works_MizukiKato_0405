//=============================================================================
// 爆発エフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_EXPLOSION_H_
#define _CONTROL_EFFECT_EXPLOSION_H_
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
class CControlEffectExplosion : public CControl
{
public:
	//メンバ関数
	CControlEffectExplosion();			//コンストラクタ	
	~CControlEffectExplosion();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectExplosion *Create(CObject *pObject);

private:
	
};

#endif	//_CONTROL_EFFECT_EXPLOSION_H_