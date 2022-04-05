//===========================================
//敵UFOの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ENEMY_UFO_H_
#define _ENEMY_UFO_H_
#include "enemy.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_UFO_WIDTH				(70.0f)		//ポリゴンの幅
#define ENEMY_UFO_HEIGHT			(70.0f)		//ポリゴンの高さ
#define ENEMY_UFO_SHOOT_COUNTER		(180)		//弾を撃つ間隔
#define ENEMY_UFO_LIFE				(2)			//ライフ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyUfo : public CEnemy
{
public:
	CEnemyUfo();				//コンストラクタ
	~CEnemyUfo();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyUfo *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CMover::MOVER_TYPE moverType);

private:
	//メンバ関数
	void MoveType(void);								//敵の動き方
	void ShootBullet(void);			//弾を打つ処理
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ENEMY_UFO_H_