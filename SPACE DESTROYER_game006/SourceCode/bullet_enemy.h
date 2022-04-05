//===========================================
//敵の弾処理
//Authore:加藤瑞葵
//===========================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_
#include "bullet.h"
#include "texture.h"

//================================================
//マクロ定義
//================================================
#define BULLET_ENEMY_WIDTH							(15.0f)		//ポリゴンの幅
#define BULLET_ENEMY_HEIGHT							(15.0f)		//ポリゴンの高さ
#define BULLET_ENEMY_BOSS_CANNON_HOMING_WIDTH		(30.0f)		//ボスの大砲が出すホーミング弾のポリゴンの幅
#define BULLET_ENEMY_BOSS_CANNON_HOMING_HEIGHT		(30.0f)		//ボスの大砲が出すホーミング弾のポリゴンの高さ
#define BULLET_ENEMY_BOSS_BODY_HOMING_WIDTH			(80.0f)		//ボスの体が出すホーミング弾のポリゴンの幅
#define BULLET_ENEMY_BOSS_BODY_HOMING_HEIGHT		(80.0f)		//ボスの体が出すホーミング弾のポリゴンの高さ
#define BULLET_ENEMY_BOSS_STRAIGHT_WIDTH			(60.0f)		//ボスが出す直進弾のポリゴンの幅
#define BULLET_ENEMY_BOSS_STRAIGHT_HEIGHT			(200.0f)	//ボスが出す直進弾のポリゴンの高さ
#define BULLET_ENEMY_BOSS_DIFFUSION_WIDTH			(80.0f)		//ボスが出す拡散弾のポリゴンの幅
#define BULLET_ENEMY_BOSS_DIFFUSION_HEIGHT			(80.0f)		//ボスが出す拡散弾のポリゴンの高さ
#define BULLET_ENEMY_BOSS_LASER_WIDTH				(300.0f)	//ボスが出すレーザー弾のポリゴンの幅
#define BULLET_ENEMY_BOSS_LASER_HEIGHT				(700.0f)	//ボスが出すレーザー弾のポリゴンの高さ
#define BULLET_ENEMY_SPEED							(7.0f)		//弾のスピード
#define BULLET_ENEMY_HOMING_SPEED					(5.0f)		//ホーミング弾のスピード
#define BULLET_ENEMY_FINISH_HOMING					(250.0f)	//ホーミングが終わる距離

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBulletEnemy : public CBullet
{
public:
	//弾の種類
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_STRAIGHT,				//真っすぐ
		BULLET_TYPE_HOMING,					//追尾
		BULLET_TYPE_LASER,					//レーザー
		BULLET_TYPE_MAX
	} BULLET_TYPE;

	CBulletEnemy(int nPriority = PRIORITY_BULLET_ENEMY);	//コンストラクタ
	~CBulletEnemy();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletEnemy::BULLET_TYPE, CTexture::TYPE textureType);

private:
	//メンバ関数
	bool Collision(D3DXVECTOR3 pos, CSound *pSound);	//当たり判定
	void MoveType(void);								//弾の動き方

	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3 m_move;									//ポリゴンの移動量
	D3DXVECTOR3	m_size;									//サイズ
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャのポインタ
	BULLET_TYPE m_nType;								//弾の種類
	float m_fRot;										//弾を円形に動かすための角度
	float m_fDistance;									//弾を円形に動かすための距離
	bool m_bHoming;										//ホーミング状態かどうか
	int m_nLaserCounter;								//レーザーを出し続ける時間
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_BULLET_ENEMY_H_