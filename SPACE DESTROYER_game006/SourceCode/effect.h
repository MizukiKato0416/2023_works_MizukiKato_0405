//===========================================
//弾処理
//Authore:加藤瑞葵
//===========================================
#ifndef _EFFECT_H_
#define _EFFECT_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================
#define EFFECT_WIDTH (50.0f)			//ポリゴンの幅
#define EFFECT_HEIGHT (50.0f)			//ポリゴンの高さ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEffect : public CScene2D
{
public:
	//エフェクトの種類
	typedef enum
	{
		EFFECT_TYPE_NONE = 0,
		EFFECT_TYPE_NORMAL,			//普通
		EFFECT_TYPE_BOSS_LASER,		//ボスのレーザー弾兆候
		EFFECT_TYPE_MAX
	} EFFECT_TYPE;

	CEffect(int nPriority = PRIORITY_EFFECT);				//コンストラクタ
	~CEffect();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size, D3DXVECTOR3 move, D3DCOLORVALUE col, EFFECT_TYPE type);

private:
	//メンバ関数
	void MoveType(void);								//タイプによる動き

	D3DXVECTOR3	m_size;									//サイズ
	D3DCOLORVALUE	m_col;								//カラー
	D3DXVECTOR3 m_move;									//移動量
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャのポインタ
	EFFECT_TYPE m_type;									//エフェクトの種類
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_EFFECT_H_