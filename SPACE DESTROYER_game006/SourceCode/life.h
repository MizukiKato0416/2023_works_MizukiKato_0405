//===========================================
//ライフ処理
//Authore:加藤瑞葵
//===========================================
#ifndef _LIFE_H_
#define _LIFE_H_
#include "scene.h"
#include "polygon.h"

//================================================
//マクロ定義
//================================================
#define MAX_LIFE_POLYGON (8)				//ポリゴンの最大数
#define START_LIFE_POLYGON (5)				//ポリゴンの最大数
#define LIFE_POLYGON_WIDTH (60.0f)			//ポリゴンの幅
#define LIFE_POLYGON_HEIGHT (60.0f)			//ポリゴンの高さ

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CLife : public CScene
{
public:
	CLife(int nPriority = PRIORITY_UI);		//コンストラクタ
	~CLife();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife);			//設定
	void AddLife(int nValue);			//加算
	void SubtractLife(int nValue);		//減算
	int GetLife(void);

	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CPolygon *m_apPolygon[MAX_LIFE_POLYGON];		//polygonのインスタンス
	int m_nLife;									//ライフ
	D3DXVECTOR3 m_pos;								//位置
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_LIFE_H_