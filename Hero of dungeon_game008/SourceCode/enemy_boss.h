//===========================================
//ボスの処理
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_BOSS_H_
#define _ENEMY_BOSS_H_
#include "enemy.h"

//前方宣言
class CModel;
class CMotionEnemyBoss;

//================================================
//マクロ定義
//================================================
#define MAX_ENEMY_BOSS_MODEL						(5)			//モデルの数
#define ENEMY_BOSS_MAX_ATTACK_COLLISION				(2)			//攻撃時の当たり判定の数
#define ENEMY_BOSS_ATTACK_DAMAGE					(80)		//攻撃時のダメージ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyBoss : public CEnemy
{
public:
	//攻撃の種類
	enum class ENEMY_BOSS_ATTACK_PATTERN
	{
		NONE = 0,
		NORMAL,			//通常
		RUSH,			//突進
		MAGIC,			//魔法
		MAX
	};

	//メンバ関数
	CEnemyBoss(int nPriority = PRIORITY_ENEMY);				//コンストラクタ
	~CEnemyBoss();											//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyBoss *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);					//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);								//モデルの位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);					//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);								//モデルの向き取得処理
	bool GetDamage(void) { return m_bDamage; }							//ダメージを受けているかどうか取得処理
	void SetDamage(bool bDamage) { m_bDamage = bDamage; }				//ダメージを受けているかどうか設定処理

private:
	//メンバ関数
	void MoveType(void);							//動きに関する処理
	void ToPlayerAttackCollision(void);				//プレイヤーへの攻撃の当たり判定				
	bool CollisionSlash(void);						//斬撃の当たり判定
	bool CollisionMagicThunder(void);				//雷魔法の当たり判定
	void Damage(void);								//ダメージを受けているときの処理

	//メンバ変数
	CModel *m_apModel[MAX_ENEMY_BOSS_MODEL];						//モデルのポインタ
	CModel *m_pParent;												//親モデルへのポインタ
	CMotionEnemyBoss *m_pMotionEnemyBoss;							//モーションのポインタ
	D3DXMATRIX m_aAttackCollMtx[ENEMY_BOSS_MAX_ATTACK_COLLISION];	//攻撃する際の当たり判定を行う場所
	bool m_bAttackColl;												//攻撃の当たり判定があるかどうか
	ENEMY_BOSS_ATTACK_PATTERN m_attackPattern;						//攻撃の種類
	int m_nCntAttack;												//攻撃した回数
	bool m_bDamage;													//ダメージを受けているかどうか
};

#endif // !_ENEMY_BOSS_H_