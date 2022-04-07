//===========================================
//ビックリマーク処理
//Author:KatoMizuki
//===========================================
#ifndef _EXCLAMATION_MARK_H_
#define _EXCLAMATION_MARK_H_
#include "billboard.h"

//前方宣言
class CControl;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CExclamationMark : public CBillboard
{
public:
	CExclamationMark(int nPriority = PRIORITY_EXCLAMATION_MARK);	//コンストラクタ
	~CExclamationMark();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExclamationMark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 initSize, D3DXVECTOR3 addSize, CObject *pObject, int nLife);

private:
	D3DXVECTOR3 m_size;		//サイズ
	D3DXVECTOR3 m_addSize;	//サイズ加算値
	CObject *m_pObject;		//対象のポインタ
	int m_nLife;			//寿命
};

#endif // !_EXCLAMATION_MARK_H_