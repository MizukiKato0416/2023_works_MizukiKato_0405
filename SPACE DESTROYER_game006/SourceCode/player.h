//===========================================
//プレイヤー処理
//Authore:加藤瑞葵
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "scene2D.h"

//前方宣言
class CUi;

//================================================
//マクロ定義
//================================================
#define PLAYER_WIDTH							(70.0f)		//ポリゴンの幅
#define PLAYER_HEIGHT							(70.0f)		//ポリゴンの高さ
#define MAX_PLAYER_LIFE							(8)			//プレイヤーのライフの最大値
#define MAX_PLAYER_INIT_LIFE					(5)			//プレイヤーのライフの初期値
#define PLAYER_MOVE								(7.0f)		//プレイヤーの移動速度
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_1		(20)		//次の弾を打つまでの間隔レベル1
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_2		(15)		//次の弾を打つまでの間隔レベル2
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_3		(10)		//次の弾を打つまでの間隔レベル3
#define PLAYER_BULLET_NEXT_SHOOT_LEVEL_4		(5)			//次の弾を打つまでの間隔レベル4
#define PLAYER_COLLISION_ADJUST					(25.0f)		//プレイヤーの当たり判定調整用
#define PLAYER_COLLISION_ENEMY_BULLET_ADJUST	(20.0f)		//敵の弾との当たり判定調整用
#define PLAYER_BULLET_POWER_LEVEL_2_POS_X		(20.0f)		//弾のレベル2が生成される時のプレイヤーのX座標からどれだけ離れているか相対値
#define PLAYER_DAMAGE_COUNT						(300)		//ダメージを受けている状態の時間
#define PLAYER_BLINK_COUNT						(5)			//点滅するまでのカウント
#define PLAYER_OVER_UNINIT_COUNT				(300)		//プレイヤーを破棄するまでの時間
#define PLAYER_OVER_EXPLOSION_COUNT				(30)		//プレイヤー倒したときに出るエフェクトの生成間隔


//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayer : public CScene2D
{
public:
	//プレイヤーの弾の状態
	typedef enum
	{
		PLAYER_BULLET_POWER_LEVEL_NONE = 0,
		PLAYER_BULLET_POWER_LEVEL_1,
		PLAYER_BULLET_POWER_LEVEL_2,
		PLAYER_BULLET_POWER_LEVEL_3,
		PLAYER_BULLET_POWER_LEVEL_4,
		PLAYER_BULLET_POWER_LEVEL_MAX
	} PLAYER_BULLET_POWER_LEVEL;

	//プレイヤーの弾の速さの状態
	typedef enum
	{
		PLAYER_BULLET_SPEED_LEVEL_NONE = 0,
		PLAYER_BULLET_SPEED_LEVEL_1,
		PLAYER_BULLET_SPEED_LEVEL_2,
		PLAYER_BULLET_SPEED_LEVEL_3,
		PLAYER_BULLET_SPEED_LEVEL_4,
		PLAYER_BULLET_SPEED_LEVEL_MAX
	} PLAYER_BULLET_SPEED_LEVEL;

	//プレイヤーの状態
	typedef enum
	{
		PLAYER_STATE_NONE = 0,
		PLAYER_STATE_NORMAL,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_MAX
	} PLAYER_STATE;

	CPlayer(int nPriority = PRIORITY_PLAYER);				//コンストラクタ
	~CPlayer();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3	size);

	void SetBulletPowerLevel(PLAYER_BULLET_POWER_LEVEL bulletPowerLevel);	//弾のレベル設定処理
	PLAYER_BULLET_POWER_LEVEL GetBulletPowerLevel(void);					//弾のレベル取得処理
	void SetBulletSpeedLevel(PLAYER_BULLET_SPEED_LEVEL bulletSpeedLevel);	//次の弾を撃つまでの速さのレベル設定処理
	PLAYER_BULLET_SPEED_LEVEL GetBulletSpeedLevel(void);					//次の弾を撃つまでの速さのレベル取得処理
	PLAYER_STATE GetPlayerState(void);										//プレイヤーの状態取得処理
	void SetPlayerState(PLAYER_STATE state);								//プレイヤーの状態設定処理
	int GetLife(void);														//プレイヤーのライフ取得処理
	void SetLife(int nLife);												//プレイヤーのライフ設定処理

private:
	//テクスチャアニメーションの種類
	typedef enum
	{
		TEXPATTERN_LEFT = 0,	//テクスチャパターン左
		TEXPATTERN_SENTER,		//テクスチャパターン中央
		TEXPATTERN_RIGHT,		//テクスチャパターン右
		TEXPATTERN_MAX			//テクスチャパターン最大値
	} TEXPATTERN;

	//メンバ関数
	D3DXVECTOR3 MoveLimit(D3DXVECTOR3 pos);									//移動制限
	bool Collision(D3DXVECTOR3 pos, CSound *pSound);						//当たり判定
	void Move(CInputKeyboard *pInputKeyboard, CInputPadX *pInputPadX);		//移動
	void Shoot(void);														//射撃処理
	void StateColor(void);													//状態に応じた色に変化させる処理
	bool GameOver(void);													//ゲームオーバー時の処理

	static LPDIRECT3DTEXTURE9 m_pTexture;			//共有テクスチャのポインタ
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	D3DXVECTOR3	m_size;								//サイズ
	float m_fAngle;									//回転の向き
	int m_nLife;									//ライフ
	int m_nCounterShoot;							//次の弾を打つまでのカウンター
	int m_nCounterNotShoot;							//弾を打っていない時間のカウンター
	PLAYER_BULLET_POWER_LEVEL m_bulletPowerLevel;	//弾のレベル
	PLAYER_BULLET_SPEED_LEVEL m_bulletSpeedLevel;	//次の弾を撃つまでの速さのレベル
	int m_nNextShoot;								//次の弾を撃つまでの間隔
	PLAYER_STATE m_state;							//プレイヤーの状態
	int m_nDamageCounter;							//ダメージを受けている状態のカウンター
	int m_nBlinkCounter;							//点滅させるためのカウンター
	bool m_bBlink;									//点滅するときの薄い状態か普通の状態かのフラグ
	CUi *m_pUi;										//マスクを出すためのUIのポインタ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PLAYER_H_