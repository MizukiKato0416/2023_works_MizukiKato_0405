//===========================================
//弾処理
//Authore:加藤瑞葵
//===========================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "scene2D.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBullet : public CScene2D
{
public:
	CBullet(int nPriority = PRIORITY_BULLET_ENEMY);				//コンストラクタ
	~CBullet();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_move;									//ポリゴンの移動量
	D3DXVECTOR3	m_size;									//サイズ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_BULLET_H_