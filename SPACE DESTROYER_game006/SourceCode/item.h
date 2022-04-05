//===========================================
//アイテム処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================
#define ITEM_WIDTH				(30.0f)				//ポリゴンの幅
#define ITEM_HEIGHT				(30.0f)				//ポリゴンの高さ
#define ITEM_SCORE_WIDTH		(20.0f * 1.9f)		//スコアアイテムのポリゴンの幅
#define ITEM_SCORE_HEIGHT		(30.0f * 1.9f)		//スコアアイテムのポリゴンの高さ
#define ITEM_SCROLL_SPEED		(1.0f)				//スクロールのスピード
#define ITEM_COLECT_SPEED		(10.0f)				//アイテムがプレイヤーに集まるスピード
#define ITEM_EFFECT_INTERVAL	(2)					//エフェクトが生成される間隔

//================================================
//クラスの定義
//================================================
//クラスの定義
class CItem : public CScene2D
{
public:
	typedef enum
	{
		ITEM_TYPE_NONE = 0,
		ITEM_TYPE_SPEED,
		ITEM_TYPE_POWER,
		ITEM_TYPE_SCORE,
		ITEM_TYPE_MAX
	} ITEM_TYPE;

	CItem(int nPriority = PRIORITY_ITEM);				//コンストラクタ
	~CItem();											//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, ITEM_TYPE type);


private:
	//メンバ関数
	bool Collision(void);					//当たり判定
	void Move(void);						//動きの処理

	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャのポインタ
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3	m_size;						//サイズ
	D3DXVECTOR3 m_scrollSpeed;				//スクロールのスピード
	ITEM_TYPE m_type;						//アイテムのタイプ
	int m_nEfectCounter;					//エフェクト生成間隔カウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ITEM_H_