//===========================================
//影処理
//Author:KatoMizuki
//===========================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "object3D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CShadow : public CObject3D
{
public:
	CShadow(int nPriority = PRIORITY_SHADOW);		//コンストラクタ
	~CShadow();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CObject *pObject);

	bool GetDraw(void) { return m_bDraw; }				//描画取得処理
	void SetDraw(bool bDraw) { m_bDraw = bDraw; }		//描画設定処理

private:
	CObject *m_pObject;		//対象のオブジェクトのポインタ
	bool m_bDraw;			//描画するかどうか
	D3DXVECTOR3 m_size;		//サイズ
};

#endif // !_SHADOW_H_