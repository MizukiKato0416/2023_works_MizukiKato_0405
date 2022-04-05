//============================================================================
// シャドウ処理 [shadow.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "scene3D.h"

//================================================
//クラスの定義
//================================================
//クラスの定義
class CShadow : public CScene3D
{
public:
	CShadow();						//コンストラクタ
	~CShadow();						//デストラクタ

									//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	void SetShadow(D3DXVECTOR3 pos, float fRange);	// 影の設定処理
	void SetUseShadow(bool bUse);					// 使用状態の設定処理

private:
	//メンバ関数
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャのポインタ
	D3DXVECTOR3 m_move;						// ポリゴンの移動量
	D3DXVECTOR3 m_Defaultsize;				// デフォルトの影のサイズ
	bool m_bUse;							// 使用しているかどうか
};

#endif // _SHADOW_H_