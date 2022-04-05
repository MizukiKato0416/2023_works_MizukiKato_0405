//===========================================
//背景処理
//Authore:加藤瑞葵
//===========================================
#ifndef _BG_H_
#define _BG_H_
#include "scene.h"

//前方宣言
class CScene2D;
//================================================
//マクロ定義
//================================================
#define MAX_BG_POLYGON (3)		//ポリゴンの最大数

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBg : public CScene
{
public:
	CBg(int nPriority = PRIORITY_BG_0);					//コンストラクタ
	~CBg();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG_POLYGON];			//テクスチャへのポインタ
	CScene2D *m_apScene2D[MAX_BG_POLYGON];							//Scene2Dのインスタンス
	D3DXVECTOR3	m_size;												//サイズ
	float m_fPosTexV[MAX_BG_POLYGON];								//テクスチャV座標
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_BG_H_