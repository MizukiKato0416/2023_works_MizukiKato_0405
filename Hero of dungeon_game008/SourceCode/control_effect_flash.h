//=============================================================================
// 閃光エフェクトの動きの処理
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_FLASH_H_
#define _CONTROL_EFFECT_FLASH_H_
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
class CControlEffectFlash : public CControl
{
public:
	//メンバ関数
	CControlEffectFlash();			//コンストラクタ	
	~CControlEffectFlash();			//デストラクタ	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectFlash *Create(CObject *pObject);

private:
	//状態
	enum class CONTROL_EFFECT_FLASH_STATE
	{
		NONE = 0,
		ADD_SIZE_SMALL,		//サイズを大きくする(変化値小)
		SUBTRACTION_SIZE,	//サイズを小さくする
		ADD_SIZE_BIG,		//サイズを大きくする(変化値大)
		MAX
	};

	CONTROL_EFFECT_FLASH_STATE m_state;		//状態
	int m_nCounter;							//状態を切り替えるまでの時間
};

#endif	//_CONTROL_EFFECT_FLASH_H_