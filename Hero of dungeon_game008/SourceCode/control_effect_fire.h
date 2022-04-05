//=============================================================================
// 炎エフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_FIRE_H_
#define _CONTROL_EFFECT_FIRE_H_
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
class CControlEffectFire : public CControl
{
public:
	//メンバ関数
	CControlEffectFire();			//コンストラクタ	
	~CControlEffectFire();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectFire *Create(CObject *pObject);

private:
	int m_nTexAnimCounter;		//テクスチャアニメーションのカウンター
	int m_nTexAnimNum;			//テクスチャアニメーションの番号
};

#endif	//_CONTROL_EFFECT_FIRE_H_