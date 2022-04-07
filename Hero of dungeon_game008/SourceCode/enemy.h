//===========================================
//敵の処理
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "object.h"

//前方宣言
class CBillboard;
class CShadow;

//================================================
//マクロ定義
//================================================
#define ENEMY_GRAVITY						(0.2f)								//重力の大きさ
#define ENEMY_STOP_MAX_COUNT				(120)								//止まっている時間
#define ENEMY_ATTACK_STOP_MAX_COUNT			(150)								//攻撃を繰り出すまでの時間
#define ENEMY_DAMAGE_MAX_COUNT				(15)								//ノックバックしている時間
#define ENEMY_MOVE_MAX_COUNT				(rand() % 840 + 240)				//進んでいる時間
#define ENEMY_TURN_RAND						(float (rand() % 629 + -314) / 100)	//回転する際の方向を決めるためのランダム値
#define ENEMY_MOVE_TO_PLAYER_MAX_DIFFER		(500.0f)							//プレイヤーを追いかける範囲
#define ENEMY_ATTACK_DIFFER					(80.0f)								//プレイヤーを攻撃する範囲
#define ENEMY_DRAW_DIFFER					(1500.0f)							//描画する範囲
#define ENEMY_SPARK_SIZE					(2.0f)								//火の粉エフェクトのサイズ
#define ENEMY_SPARK_EFFECT_NUM				(50)								//火の粉エフェクトの数
#define ENEMY_SPARK_EFFECT_COLOR			(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//火の粉エフェクトの色
#define ENEMY_SPARK_MOVE_MIN				(2.0f)								//火の粉エフェクトの初速ランダム最小値
#define ENEMY_SPARK_MOVE_MAX				(5.0f)								//火の粉エフェクトの初速ランダム最大値
#define ENEMY_SPARK_GRAVITY					(0.3f)								//火の粉エフェクトの重力
#define ENEMY_SPARK_COL_A_MIN				(0.02f)								//火の粉エフェクトのα値減算ランダム最小値
#define ENEMY_SPARK_COL_A_MAX				(0.04f)								//火の粉エフェクトのα値減算ランダム最大値
#define ENEMY_SPARK_SUBTRACTION_MOVE		(0.94f)								//火の粉エフェクトの移動量減算割合
#define ENEMY_EXCLAMATION_MARK_SIZE			(70.0f)								//ビックリマークの大きさ
#define ENEMY_EXCLAMATION_MARK_ADD_SIZE		(20.0f)								//ビックリマークの大きさ加算量
#define ENEMY_EXCLAMATION_MARK_LIFE			(60)								//ビックリマークの寿命
#define ENEMY_BOSS_UNINIT_SCORE				(10000000)							//ボスを倒した時に得られるスコア
#define ENEMY_FAT_UNINIT_SCORE				(150000)							//太型敵倒した時に得られるスコア
#define ENEMY_BEE_UNINIT_SCORE				(200000)							//蜂型敵倒した時に得られるスコア


//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemy : public CObject
{
public:
	//行動パターン
	enum class ENEMY_MOVE_PATTERN
	{
		NONE = 0,
		MOVE,				//移動
		STOP,				//停止
		TURN,				//回転
		MOVE_TO_PLAYER,		//プレイヤーのほうに向かって移動
		ATTACK,				//攻撃
		DAMAGE,				//被ダメージ
		MAX
	};

	//メンバ関数
	CEnemy(int nPriority = PRIORITY_ENEMY);				//コンストラクタ
	~CEnemy();											//デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	void Uninit(void);
	virtual void Update(void) = 0;
	void Draw(void);
	static int GetNum(void) { return m_nNum; }												//総数取得処理
	static void Collision(CObject *pSubjectObject, float fObjRadius);						//当たり判定
	bool CEnemy::CollisionOnly(CObject * pSubjectObject, float fObjRadius);					//衝突判定のみの処理
	ENEMY_MOVE_PATTERN GetMovePattern(void) { return m_movePattern; }						//行動パターン取得処理
	void SetMovePattern(ENEMY_MOVE_PATTERN movePattern) { m_movePattern = movePattern; }	//行動パターン設定処理
	int GetLife(void) { return m_nLife; }													//ライフ取得処理
	void AddLife(int nLife) { m_nLife += nLife; }											//ライフ加減処理
	bool GetDraw(void) { return m_bDraw; }													//描画されているか取得処理

protected:
	//メンバ関数
	void Rotate(void);							//回転処理

	//メンバ変数
	static int m_nNum;							//敵の総数
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_posOld;						//1フレーム前の位置
	D3DXVECTOR3 m_move;							//ポリゴンの移動量
	D3DXVECTOR3	m_size;							//サイズ
	D3DXVECTOR3 m_rot;							//向き
	D3DXMATRIX m_mtxWorld;						//ワールドマトリックス
	float m_fObjectiveRot;						//目的の向き
	float m_fNumRot;							//向きを変える量
	bool m_bRotate;								//回転しているかどうか
	bool m_bDraw;								//描画しているかどうか
	bool m_bNotice;								//プレイヤーに気づいているかどうか
	ENEMY_MOVE_PATTERN m_movePattern;			//動きの種類
	int m_nStopCounter;							//停止している時間
	int m_nMoveCounter;							//移動している時間
	int m_nAttackCounter;						//攻撃を出すまでの時間
	int m_nDamageCounter;						//ノックバックしている時間
	int m_nLife;								//体力
	CShadow *m_pShadow;							//影のポインタ
};

#endif // !_ENEMY_H_