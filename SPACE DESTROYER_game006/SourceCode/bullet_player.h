//===========================================
//プレイヤーの弾処理
//Authore:加藤瑞葵
//===========================================
#ifndef _BULLET_PLAYER_H_
#define _BULLET_PLAYER_H_
#include "bullet.h"

//================================================
//マクロ定義
//================================================
#define BULLET_PLAYER_WIDTH				(15.0f)			//ポリゴンの幅
#define BULLET_PLAYER_HEIGHT			(100.0f)		//ポリゴンの高さ
#define BULLET_PLAYER_SPEED				(-15.0f)		//弾のスピード
#define BULLET_PLAYER_EFFECT_INTERVAL	(1)				//弾のエフェクトの間隔
#define BULLET_PLAYER_FINISH_HOMING		(0.0f)			//ホーミングが終わる距離


//================================================
//クラスの定義
//================================================
//クラスの定義
class CBulletPlayer : public CBullet
{
public:
	//弾の種類
	typedef enum
	{
		BULLET_TYPE_NONE = 0,
		BULLET_TYPE_STRAIGHT,			//真っすぐ
		BULLET_TYPE_DIFFUSION,		//拡散
		BULLET_TYPE_HOMING,			//追尾
		BULLET_TYPE_MAX
	} BULLET_TYPE;

	CBulletPlayer(int nPriority = PRIORITY_BULLET_PLAYER);	//コンストラクタ
	~CBulletPlayer();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fRot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBulletPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size, D3DXVECTOR3 move, CBulletPlayer::BULLET_TYPE, float fRot);
	float GetRot(void);			//弾の向き取得処理

private:
	//メンバ関数
	void MoveType(void);								//弾の動き方

	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3 m_move;									//ポリゴンの移動量
	D3DXVECTOR3	m_size;									//サイズ
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャのポインタ
	BULLET_TYPE m_nType;								//弾の種類
	int m_nEfectCounter;								//エフェクトを生成するカウンタ
	bool m_bHoming;										//ホーミング状態かどうか
	float m_fRot;										//弾の向き
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_BULLET_PLAYER_H_