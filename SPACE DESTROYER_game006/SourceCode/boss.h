//===========================================
//ボスの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "scene.h"

//前方宣言
class CScene2D;
//================================================
//マクロ定義
//================================================
#define MAX_BOSS_POLYGON						(4)								//ポリゴンの最大数
#define BOSS_WING_WIDTH							(1249.0f)						//羽のポリゴンの幅
#define BOSS_WING_HEIGHT						(225.0f)						//羽のポリゴンの高さ
#define BOSS_BODY_WIDTH							(316.0f)						//体のポリゴンの幅
#define BOSS_BODY_HEIGHT						(327.0f)						//体のポリゴンの高さ
#define BOSS_CANNON_WIDTH						(91.0f)							//大砲のポリゴンの幅
#define BOSS_CANNON_HEIGHT						(128.0f)						//大砲のポリゴンの高さ
#define BOSS_CANNON_POS							(400.0f)						//ボスの中心位置からの大砲の相対的な位置
#define BOSS_BODY_COLLISION_ADJUST				(-100.0f)						//ボスの体の当たり判定調節の値
#define BOSS_BODY_COLLISION_PLAYER_ADJUST		(-50.0f)						//プレイヤーとボスの体の当たり判定調節の値
#define BOSS_WING_COLLISION_ADJUST				(-200.0f)						//ボスの羽の当たり判定調節の値
#define BOSS_WING_COLLISION_PLAYER_ADJUST		(-80.0f)						//プレイヤーとボスの羽の当たり判定調節の値
#define BOSS_CANNON_COLLISION_ADJUST			(-50.0f)						//ボスの大砲の当たり判定調節の値
#define BOSS_CANNON_COLLISION_PLAYER_ADJUST		(-10.0f)						//プレイヤーとボスの大砲の当たり判定調節の値
#define BOSS_DAMAGE_COUNT						(10)							//ダメージを受けている状態の時間
#define BOSS_BODY_LIFE							(300)							//体のライフ
#define BOSS_WING_LIFE							(200)							//羽のライフ
#define BOSS_CANNON_LIFE						(150)							//大砲のライフ
#define BOSS_CANNON_SHOOT_COUNTER				(180)							//大砲が弾を撃つ間隔
#define BOSS_CANNON_SHOOT_ADJUST_X				(20.0f)							//大砲が弾を出すX座標調整
#define BOSS_CANNON_SHOOT_ADJUST_Y				(50.0f)							//大砲が弾を出すY座標調整
#define BOSS_BODY_SHOOT_LASER_TIME				(200)							//体がレーザーを出す時間
#define BOSS_BODY_SHOOT_LASER_COUNT				(100)							//体がレーザーを出すタイミング
#define BOSS_BODY_SHOOT_STRAIGHT_COUNT_0		(90)							//体の直進する弾を出すタイミングその1
#define BOSS_BODY_SHOOT_STRAIGHT_COUNT_1		(180)							//体の直進する弾を出すタイミングその2
#define BOSS_BODY_SHOOT_STRAIGHT_ADJUST			(40.0f)							//体の直進する弾を出す位置調整の値
#define BOSS_BODY_SHOOT_ADJUST_Y				(60.0f)							//体の弾を出すy座標調整の値
#define BOSS_BODY_SHOOT_DIFFUSION_00_NUM		(5)								//体の拡散弾を出す個数00
#define BOSS_BODY_SHOOT_DIFFUSION_01_NUM		(6)								//体の拡散弾を出す個数01
#define BOSS_BODY_SHOOT_DIFFUSION_00_COUNT		(120)							//体の拡散弾00を出すタイミング
#define BOSS_BODY_SHOOT_DIFFUSION_01_COUNT		(240)							//体の拡散弾01を出すタイミング
#define BOSS_BODY_SHOOT_HOMING_COUNT			(15)							//ホーミング弾を出すタイミング
#define BOSS_BODY_SHOOT_STRAIGHT_PHASE_COUNT	(800)							//体の直進する弾を出すフェーズの時間
#define BOSS_BODY_SHOOT_DIFFUSION_PHASE_COUNT	(1000)							//体の拡散する弾を出すフェーズの時間
#define BOSS_BODY_SHOOT_LASER_PHASE_COUNT		(600)							//体のレーザー弾を出すフェーズの時間
#define BOSS_BODY_SHOOT_HOMING_PHASE_COUNT		(280)							//体のホーミング弾を出すフェーズの時間
#define BOSS_BODY_SHOOT_LASER_EFFECT_NUM		(6)								//体のレーザー弾を出す兆候のエフェクトの数
#define BOSS_BODY_SHOOT_LASER_EFFECT_TIME		(40)							//体のレーザー弾を出す兆候のエフェクトを出す時間
#define BOSS_BODY_SHOOT_LASER_EFFECT_COUNT		(3)								//体のレーザー弾を出す兆候のエフェクトを出す間隔
#define BOSS_BODY_SHOOT_LASER_EFFECT_ADJUST		(300.0f)						//体のレーザー弾を出す兆候のエフェクトを出す位置調整値
#define BOSS_CLEAR_UNINIT_COUNT					(500)							//ボスを破棄するまでの時間
#define BOSS_CLEAR_EXPLOSION_COUNT				(10)							//ボス倒したときに出るエフェクトの生成間隔
#define BOSS_CLEAR_EXPLOSION_POS_X				((float)(rand() % 1250 + 15))	//ボス倒したときに出るエフェクトのX座標
#define BOSS_CLEAR_EXPLOSION_POS_Y				((float)(rand() % 201))			//ボス倒したときに出るエフェクトのY座標

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CBoss : public CScene
{
public:
	CBoss(int nPriority = PRIORITY_BOSS);					//コンストラクタ
	~CBoss();												//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move);

	D3DXVECTOR3 GetBodyPos(void);			//体の位置取得処理

private:
	//ボスの状態
	typedef enum
	{
		BOSS_STATE_NONE = 0,
		BOSS_STATE_NORMAL,
		BOSS_STATE_DAMAGE,
		BOSS_STATE_MAX
	} BOSS_STATE;

	//ボスの本体の射撃フェーズ
	typedef enum
	{
		BOSS_BODY_SHOOT_PHASE_NONE = 0,
		BOSS_BODY_SHOOT_PHASE_STRAIGHT,			//直進
		BOSS_BODY_SHOOT_PHASE_DIFFUSION_00,		//拡散00
		BOSS_BODY_SHOOT_PHASE_LASER,			//レーザー
		BOSS_BODY_SHOOT_PHASE_HOMING,			//追尾
		BOSS_BODY_SHOOT_PHASE_MAX
	} BOSS_BODY_SHOOT_PHASE;

	//メンバ関数
	void StateColor(int nCntPolygon);								//状態に応じた色に変化させる処理
	bool CollisionPlayerBullet(void);								//プレイヤーの弾との当たり判定
	void Shoot(int nCntPolygon);									//射撃処理
	void BodyShoot(int nCntPolygon);								//体部分の射撃処理
	bool GameClear(void);											//ゲームクリア時の処理

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BOSS_POLYGON];			//テクスチャへのポインタ
	CScene2D *m_apScene2D[MAX_BOSS_POLYGON];						//Scene2Dのインスタンス
	D3DXVECTOR3	m_size[MAX_BOSS_POLYGON];							//サイズ
	D3DXVECTOR3	m_pos[MAX_BOSS_POLYGON];							//位置
	D3DXVECTOR3	m_move;												//移動量
	int m_nBulletCounter[MAX_BOSS_POLYGON];							//弾発射用カウンタ
	BOSS_STATE m_state[MAX_BOSS_POLYGON];							//ボスの状態
	int m_nDamageCounter[MAX_BOSS_POLYGON];							//ダメージを受けている状態のカウンター
	int m_nLife[MAX_BOSS_POLYGON];									//ライフ
	BOSS_BODY_SHOOT_PHASE m_shootPhase;								//本体の射撃フェーズ
	int m_nNextPhase;												//次のフェーズに行くまでの時間
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_BOSS_H_