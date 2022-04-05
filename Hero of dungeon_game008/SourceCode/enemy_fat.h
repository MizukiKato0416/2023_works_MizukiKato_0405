//===========================================
//太型敵の処理
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_FAT_H_
#define _ENEMY_FAT_H_
#include "enemy.h"

//前方宣言
class CModel;
class CMotionEnemyFat;

//================================================
//マクロ定義
//================================================
#define MAX_ENEMY_FAT_MODEL						(5)			//モデルの数
#define ENEMY_FAT_MAX_ATTACK_COLLISION			(2)			//攻撃時の当たり判定の数
#define ENEMY_FAT_ATTACK_DAMAGE					(50)		//攻撃時のダメージ

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyFat : public CEnemy
{
public:
	//メンバ関数
	CEnemyFat(int nPriority = PRIORITY_ENEMY);				//コンストラクタ
	~CEnemyFat();											//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemyFat *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetModelPos(int nCntModel, D3DXVECTOR3 pos);					//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(int nCntModel);								//モデルの位置取得処理
	void SetModelRot(int nCntModel, D3DXVECTOR3 rot);					//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(int nCntModel);								//モデルの向き取得処理

private:
	//メンバ関数
	void MoveType(void);							//動きに関する処理
	void ToPlayerAttackCollision(void);				//プレイヤーへの攻撃の当たり判定				
	bool CollisionSlash(void);						//斬撃の当たり判定
	bool CollisionMagicThunder(void);				//雷魔法の当たり判定

	//メンバ変数
	CModel *m_apModel[MAX_ENEMY_FAT_MODEL];							//モデルのポインタ
	CModel *m_pParent;												//親モデルへのポインタ
	CMotionEnemyFat *m_pMotionEnemyFat;								//モーションのポインタ
	D3DXMATRIX m_aAttackCollMtx[ENEMY_FAT_MAX_ATTACK_COLLISION];	//攻撃する際の当たり判定を行う場所
	bool m_bAttackColl;												//攻撃の当たり判定があるかどうか
};

#endif // !_ENEMY_FAT_H_