//===========================================
//ガードエフェクト処理
//Author:KatoMizuki
//===========================================
#ifndef _GUARD_EFFECT_H_
#define _GUARD_EFFECT_H_
#include "object.h"

//前方宣言
class CObject3D;

//================================================
//マクロ定義
//================================================
#define GUARD_EFFECT_POS			(10.0f)		//ガードエフェクトの生成位置調整値
#define GUARD_EFFECT_POS_Y			(30.0f)		//ガードエフェクトの生成位置調整値Y
#define GUARD_EFFECT_SIZE			(1.0f)		//ガードエフェクトの生成初期サイズ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CGuardEffect : public CObject
{
public:
	//メンバ関数
	CGuardEffect(int nPriority = PRIORITY_EFFECT3D);		//コンストラクタ
	~CGuardEffect();										//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGuardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	CObject3D *m_pObject3D;			//Object3Dのポインタ
	D3DXVECTOR3 m_rot;				//向き
};

#endif // !_GUARD_EFFECT_H_