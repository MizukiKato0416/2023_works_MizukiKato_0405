//===========================================
//スピードアップのアイテムを落とす敵の処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ENEMY_ITEM_SPEED_H_
#define _ENEMY_ITEM_SPEED_H_
#include "enemy.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_ITEM_SPEED_WIDTH		(70.0f)	//ポリゴンの幅
#define ENEMY_ITEM_SPEED_HEIGHT		(70.0f)	//ポリゴンの高さ
#define ENEMY_ITEM_SPEED_LIFE		(1)		//ライフ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyItemSpeed : public CEnemy
{
public:

	CEnemyItemSpeed();				//コンストラクタ
	~CEnemyItemSpeed();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyItemSpeed *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//メンバ関数
	void MoveType(void);								//敵の動き方
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ENEMY_ITEM_SPEED_H_