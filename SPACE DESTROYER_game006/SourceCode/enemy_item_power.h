//===========================================
//パワーアップのアイテムを落とす敵の処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ENEMY_ITEM_POWER_H_
#define _ENEMY_ITEM_POWER_H_
#include "enemy.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_ITEM_POWER_WIDTH		(70.0f)	//ポリゴンの幅
#define ENEMY_ITEM_POWER_HEIGHT		(70.0f)	//ポリゴンの高さ
#define ENEMY_ITEM_POWER_LIFE		(1)		//ライフ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyItemPower : public CEnemy
{
public:

	CEnemyItemPower();				//コンストラクタ
	~CEnemyItemPower();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyItemPower *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//メンバ関数
	void MoveType(void);								//敵の動き方
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ENEMY_ITEM_POWER_H_