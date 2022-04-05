//===========================================
//プレイヤー処理
//Author:KatoMizuki
//===========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "object.h"

//前方宣言
class CModel;
class CMotionPlayer;
class CMeshTrajectory;
class CBillboard;
class CEnemy;

//================================================
//マクロ定義
//================================================
#define MAX_PLAYER_MODEL					(16)		//モデルの数
#define PLAYER_MAX_HP						(1000)		//最大HP
#define PLAYER_MAX_MP						(1000)		//最大MP
#define PLAYER_MAX_SP						(100)		//最大SP
#define PLAYER_MAGIC_01_POS					(50.0f)		//魔法1の位置XZ調整値
#define PLAYER_MAGIC_01_POS_Y				(40.0f)		//魔法1の位置Y調整値

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayer : public CObject
{
public:
	//プレイヤーの状態
	enum class PLAYER_STATE
	{
		NONE = 0,
		NORMAL,		//通常
		DAMAGE,		//ダメージ
		INVINCIBLE,	//無敵
		MAX
	};


	//メンバ関数
	CPlayer(int nPriority = PRIORITY_PLAYER);				//コンストラクタ
	~CPlayer();												//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);								//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);											//モデルの位置取得処理
	D3DXVECTOR3 GetRot(void) { return m_rot; }										//プレイヤーの向き取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);								//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);											//モデルの向き取得処理
	void SetMove(D3DXVECTOR3 move) { m_move = move; }								//移動量設定処理
	PLAYER_STATE GetState(void) { return m_state; }									//状態取得処理
	void SetState(PLAYER_STATE state) { m_state = state; }							//状態設定処理
	CEnemy *GetEnemyNear(void) { return m_pEnemyNear; }								//一番近くの敵取得処理
	void SetEnemyNear(CEnemy *pEnemy) { m_pEnemyNear = pEnemy; }					//一番近くの敵設定処理
	bool GetGuard(void) { return m_bGuard; }										//ガード取得処理
	static void CPlayer::Collision(CObject *pSubjectObject, float fObjRadius);		//当たり判定処理
	bool CPlayer::CollisionOnly(CObject *pSubjectObject, float fObjRadius);			//衝突判定のみの処理

private:
	//メンバ関数
	void Move(void);								//移動処理
	void Rotate(void);								//回転処理
	void Jump(void);								//ジャンプ処理
	void Slash(void);								//剣攻撃処理
	void Special(void);								//必殺技処理
	void Magic(void);								//魔法攻撃処理
	void Guard(void);								//ガード処理
	void State(void);								//状態による処理分け
	void LockOn(void);								//ロックオン処理

	//メンバ変数
	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_posOld;							//1フレーム前の位置
	D3DXVECTOR3 m_move;								//ポリゴンの移動量
	D3DXVECTOR3	m_size;								//サイズ
	D3DXVECTOR3 m_rot;								//向き
	CModel *m_apModel[MAX_PLAYER_MODEL];			//モデルのポインタ
	D3DXMATRIX m_mtxWorld;							//ワールドマトリックス
	CModel *m_pParent;								//親モデルへのポインタ
	CMotionPlayer *m_pMotionPlayer;					//モーションプレイヤーのポインタ
	CMeshTrajectory *m_pMeshTrajectory[2];			//剣の軌跡
	CBillboard *m_pLockOn;							//ロックオンUI
	CEnemy *m_pEnemyNear;							//プレイヤーに一番近い敵
	float m_fObjectiveRot;							//目的の向き
	float m_fLockOnObjectiveRot;					//lock-on時の目的の向き
	float m_fNumRot;								//向きを変える量
	bool m_bRotate;									//回転しているかどうか
	bool m_bJump;									//ジャンプしてるかどうか
	bool m_bBurst;									//連撃しているかどうか
	bool m_bSpecial;								//必殺技をしているかどうか
	bool m_bLockOn;									//ロックオンをしているかどうか
	bool m_bGuard;									//ガードをしているかどうか
	int m_nCntBurst;								//連撃数
	int m_nInvincibleCounter;						//無敵状態のカウンター
	PLAYER_STATE m_state;							//状態
	
};

#endif // !_PLAYER_H_