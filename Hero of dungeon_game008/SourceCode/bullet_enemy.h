//===========================================
//敵の弾処理
//Author:KatoMizuki
//===========================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_
#include "billboard.h"

//前方宣言

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBulletEnemy : public CBillboard
{
public:
	CBulletEnemy(int nPriority = PRIORITY_ENEMY_BULLET);		//コンストラクタ
	~CBulletEnemy();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);


private:
	//メンバ関数
	void CollisionPlayer(void);		//プレイヤーとの当たり判定

	D3DXVECTOR3 m_move;				//移動量
	int m_nLife;					//寿命
};

#endif // !_BULLET_ENEMY_H_