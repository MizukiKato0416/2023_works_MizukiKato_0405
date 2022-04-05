//===========================================
//3Dポリゴン処理
//Author:加藤瑞葵
//===========================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
#include "scene.h"
#include "main.h"

//================================================
//マクロ定義
//================================================
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)		//頂点フォーマット3D
#define VERTEX_3D_NUM (4)														//頂点数

//========================================================
//構造体の定義3D
//========================================================
typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
} VERTEX_3D;

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = PRIORITY_MODEL);	//コンストラクタ
	~CScene3D();								//デストラクタ

												//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);
	D3DXVECTOR3 GetPos(void);
	void SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void SetTex(int nPattern, int nMaxPattern);
	void SetTex(float fMoveTexU, float fMoveTexV);
	void SetCol(D3DCOLORVALUE col);
	void SetCol(D3DXCOLOR col);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:

protected:
	D3DXVECTOR3 m_pos;						//ポリゴンの位置
	D3DXVECTOR3	m_size;						//サイズ
	D3DXVECTOR3 m_rot;						//向き
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス
};

#endif // !_SCENE3D_H_