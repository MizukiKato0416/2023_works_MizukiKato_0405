//===========================================
//敵処理
//Authore:加藤瑞葵
//===========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "scene2D.h"
#include "mover.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_DAMAGE_COUNT				(20)		//ダメージを受けている状態の時間
#define ENEMY_DELETE_EFFECT_IN_MAX		(6)			//敵の体力がゼロになった時に出る内側のエフェクトの最大数
#define ENEMY_DELETE_EFFECT_IN_SIZE		(50.0f)		//敵の体力がゼロになった時に出る内側のエフェクトのサイズ
#define ENEMY_DELETE_EFFECT_IN_MOVE		(3.0f)		//敵の体力がゼロになった時に出る内側のエフェクトの移動量
#define ENEMY_DELETE_EFFECT_OUT_MAX		(8)			//敵の体力がゼロになった時に出る外側のエフェクトの最大数
#define ENEMY_DELETE_EFFECT_OUT_SIZE	(30.0f)		//敵の体力がゼロになった時に出る外側のエフェクトのサイズ
#define ENEMY_DELETE_EFFECT_OUT_MOVE	(6.0f)		//敵の体力がゼロになった時に出る外側のエフェクトの移動量

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemy : public CScene2D
{
public:
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,
		ENEMY_TYPE_FIGHTER,
		ENEMY_TYPE_UFO,
		ENEMY_TYPE_SPHERE,
		ENEMY_TYPE_ITEM_POWER,
		ENEMY_TYPE_ITEM_SPEED,
		ENEMY_TYPE_MAX
	} ENEMY_TYPE;

	CEnemy(int nPriority = PRIORITY_ENEMY);				//コンストラクタ
	~CEnemy();			//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);		

protected:
	//敵の状態
	typedef enum
	{
		ENEMY_STATE_NONE = 0,
		ENEMY_STATE_NORMAL,
		ENEMY_STATE_DAMAGE,
		ENEMY_STATE_MAX
	} ENEMY_STATE;

	static LPDIRECT3DTEXTURE9 m_pTexture;			//共有テクスチャのポインタ
	D3DXVECTOR3	m_size;								//サイズ
	D3DXVECTOR3	m_pos;								//位置
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	int m_nCntFrame;								//フレームをカウントする変数
	CMover *m_pMover;								//CMoverのポインタ
	CMover::MOVER_TYPE m_moverType;					//動きの種類
	int m_nLife;									//ライフ
	int m_nBulletCounter;							//弾の生成間隔カウント用
	ENEMY_TYPE m_type;								//敵の種類

private:
	//メンバ関数
	void StateColor(void);							//状態に応じた色に変化させる処理
	bool Collision(void);							//当たり判定

	ENEMY_STATE m_state;							//敵の状態
	int m_nDamageCounter;							//ダメージを受けている状態のカウンター
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_ENEMY_H_