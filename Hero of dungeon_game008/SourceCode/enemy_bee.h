//===========================================
//敵(蜂)の処理
//Author:KatoMizuki
//===========================================
#ifndef _ENEMY_BEE_H_
#define _ENEMY_BEE_H_
#include "enemy.h"

//前方宣言
class CModel;
class CMotionEnemyBee;

//================================================
//マクロ定義
//================================================
#define MAX_ENEMY_BEE_MODEL							(1)			//蜂型敵1体に使うモデルの数

//================================================
//クラスの定義
//================================================
//クラスの定義
class CEnemyBee : public CEnemy
{
public:
	//メンバ関数
	CEnemyBee(int nPriority = PRIORITY_ENEMY);				//コンストラクタ
	~CEnemyBee();											//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	static CEnemyBee *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);			//生成処理
	void SetModelPos(D3DXVECTOR3 pos);									//モデルの位置設定処理
	D3DXVECTOR3 GetModelPos(void);										//モデルの位置取得処理
	void SetModelRot(D3DXVECTOR3 rot);									//モデルの向き設定処理
	D3DXVECTOR3 GetModelRot(void);										//モデルの向き取得処理
private:
	void Move(void);							//移動処理
	void MoveType(void);						//動きに関する処理
	bool CollisionSlash(void);					//斬撃の当たり判定
	bool CollisionMagicThunder(void);			//雷魔法の当たり判定

	CModel *m_pModel;						//ModelSingleのポインタ
	int m_nFlyMoveCounter;					//飛行時の上下移動のカウンター
	CMotionEnemyBee *m_pMotionEnemyBee;		//モーションのポインタ

};

#endif // !_ENEMY_BEE_H_