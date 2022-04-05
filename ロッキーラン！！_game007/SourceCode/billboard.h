//============================================================================
// ビルボード処理 [billboard.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "scene.h"
#include "scene3D.h"

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBillboard : public CScene
{
public:
	CBillboard(int nPriority = PRIORITY_PLAYER);	//コンストラクタ
	~CBillboard();								//デストラクタ

												//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetTex(int nPattern, int nMaxPattern);
	void SetTex(float fMoveTexU, float fMoveTexV);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

protected:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3	m_size;						//サイズ
	D3DXVECTOR3 m_rot;						//向き
	D3DXVECTOR3 m_move;						//移動量
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
};

#endif // !_BILLBOARD_H_