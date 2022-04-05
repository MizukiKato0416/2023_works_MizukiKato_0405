//===========================================
//爆発処理
//Authore:加藤瑞葵
//===========================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================
#define EXPLOSION_WIDTH					(50.0f)		//ポリゴンの幅
#define EXPLOSION_HEIGHT				(50.0f)		//ポリゴンの高さ
#define EXPLOSION_BOSS_UNINIT_WIDTH		(100.0f)	//ボスを倒したときのポリゴンの幅
#define EXPLOSION_BOSS_UNINIT_HEIGHT	(100.0f)	//ボスを倒したときのポリゴンの高さ
#define PATTERN_FRAME					(4)			//パターンが切り替わるまでのフレーム
#define MAX_PATTERN						(8)			//パターンの最大値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CExplosion : public CScene2D
{
public:
	CExplosion(int nPriority = PRIORITY_EXPLOSION);				//コンストラクタ
	~CExplosion();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//共有テクスチャのポインタ
	int m_nCounterAnim;						//カウンター
	int m_nPatternAnim;						//パターンNo
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_EXPLOSION_H_