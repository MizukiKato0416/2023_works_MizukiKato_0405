//===========================================
//2Dポリゴン処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
#include "scene.h"
#include "main.h"

//================================================
//マクロ定義
//================================================
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//頂点フォーマット
#define VERTEX_NUM (4)												//頂点数

//========================================================
//構造体の定義
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	float rhw;				//1.0fで固定
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_2D;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3);				//コンストラクタ
	~CScene2D();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRot);
	void SetTex(int nPattern, int nMaxPattern);
	void SetTex(float fMoveTexU, float fMoveTexV);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
	void SetVtx(D3DXVECTOR3 pos, D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3	m_size;						//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCENE2D_H_