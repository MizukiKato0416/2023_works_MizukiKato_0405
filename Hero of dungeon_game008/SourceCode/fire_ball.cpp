//================================================
//炎の弾の処理
//Author:KatoMizuki
//================================================
#include "fire_ball.h"
#include "effect3D.h"
#include "floor.h"
#include "model_single.h"
#include "enemy.h"
#include "explosion.h"
#include "spark.h"
#include "play_data.h"
#include "manager.h"
#include "gauge.h"
#include "player.h"
#include "magic_fire.h"
#include "enemy_boss.h"
#include "score.h"

//================================================
//マクロ定義
//================================================
#define FIRE_BALL_EXPLOSION_SIZE_X				(50.0f)									//爆発エフェクトのサイズX
#define FIRE_BALL_EXPLOSION_SIZE_Y				(70.0f)									//爆発エフェクトのサイズY
#define FIRE_BALL_EXPLOSION_EFFECT_NUM			(70)									//爆発エフェクトの数
#define FIRE_BALL_EXPLOSION_EFFECT_COLOR		(D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f))		//爆発エフェクトの色
#define FIRE_BALL_EXPLOSION_MOVE_MIN			(1.0f)									//爆発エフェクトの初速ランダム最小値
#define FIRE_BALL_EXPLOSION_MOVE_MAX			(4.0f)									//爆発エフェクトの初速ランダム最大値
#define FIRE_BALL_EXPLOSION_GRAVITY				(-0.7f)									//爆発エフェクトの重力
#define FIRE_BALL_EXPLOSION_COL_A_MIN			(0.01f)									//爆発エフェクトのα値減算ランダム最小値
#define FIRE_BALL_EXPLOSION_COL_A_MAX			(0.016f)								//爆発エフェクトのα値減算ランダム最大値
#define FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE	(0.9f)									//爆発エフェクトの移動量減算割合
#define FIRE_BALL_SPARK_SIZE					(1.0f)									//火の粉エフェクトのサイズ
#define FIRE_BALL_SPARK_EFFECT_NUM				(100)									//火の粉エフェクトの数
#define FIRE_BALL_SPARK_EFFECT_COLOR			(D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f))		//火の粉エフェクトの色
#define FIRE_BALL_SPARK_MOVE_MIN				(2.0f)									//火の粉エフェクトの初速ランダム最小値
#define FIRE_BALL_SPARK_MOVE_MAX				(5.0f)									//火の粉エフェクトの初速ランダム最大値
#define FIRE_BALL_SPARK_GRAVITY					(-0.5f)									//火の粉エフェクトの重力
#define FIRE_BALL_SPARK_COL_A_MIN				(0.007f)								//火の粉エフェクトのα値減算ランダム最小値
#define FIRE_BALL_SPARK_COL_A_MAX				(0.009f)								//火の粉エフェクトのα値減算ランダム最大値
#define FIRE_BALL_SPARK_SUBTRACTION_MOVE		(0.9f)									//火の粉エフェクトの移動量減算割合
#define FIRE_BALL_ENEMY_FAT_DAMAGE				(6)										//太型敵に与えるダメージ
#define FIRE_BALL_ENEMY_FAT_ADD_SP				(3)										//太型敵に当てたときのSP増加量
#define FIRE_BALL_ENEMY_BEE_DAMAGE				(8)										//蜂型敵に与えるダメージ
#define FIRE_BALL_ENEMY_BEE_ADD_SP				(6)										//蜂型敵に当てたときのSP増加量
#define FIRE_BALL_ENEMY_BOSS_DAMAGE				(7)										//ボスに与えるダメージ
#define FIRE_BALL_ENEMY_BOSS_ADD_SP				(5)										//ボスに当てたときのSP増加量

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CFireBall::CFireBall(int nPriority) :CObject(nPriority)
{
	m_nRotPartitionNum = 0;
	m_nLayer = 0;
	m_nLife = 0;
	m_fPower = 0.0f;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pEffect3D.clear();
	m_bHoming = false;
	m_pTargetEnemy = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CFireBall::~CFireBall()
{

}

//================================================
//初期化処理
//================================================
HRESULT CFireBall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::FIRE_BALL);
	
	for (int nCnt = 0; nCnt < m_nLayer; nCnt++)
	{
		for (int nCnt1 = 0; nCnt1 < m_nRotPartitionNum; nCnt1++)
		{
			m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(pos.x + cosf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.y + sinf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.z),
													D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE));

			m_pEffect3D.push_back(CEffect3D::Create(D3DXVECTOR3(pos.x,
																pos.y + sinf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt),
																pos.z + cosf(D3DX_PI * 2.0f / m_nRotPartitionNum * nCnt1) * pow(m_fPower, nCnt)),
													D3DXVECTOR3(60.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CEffect3D::EFFECT3D_TYPE::FIRE));
		}
	}

	//変数初期化
	m_pos = pos;
	m_size = size;

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//現在の次のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//ロックオンしている敵を取得
			m_pTargetEnemy = pPlayerObj->GetEnemyNear();
			//ロックオンしているなら
			if (m_pTargetEnemy != nullptr)
			{
				//追尾させる
				m_bHoming = true;
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//位置とサイズを設定
	SetPos(m_pos);
	SetSize(m_size);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CFireBall::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CFireBall::Update(void)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//現在の次のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//プレイヤーにキャスト
			CPlayer *pPlayerObj = nullptr;
			pPlayerObj = (CPlayer*)pObject;

			//ロックオンしているなら
			if (m_pTargetEnemy != pPlayerObj->GetEnemyNear())
			{
				//追尾をやめる
				m_bHoming = false;
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//寿命を減らす
	m_nLife--;
	//0以下になったら
	if (m_nLife <= 0)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//エフェクトを消す
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//移動量
	for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
	{
		//位置とサイズを取得
		D3DXVECTOR3 posEffect = m_pEffect3D[nCntEffect]->GetPos();
		D3DXVECTOR3 sizeEffect = m_pEffect3D[nCntEffect]->GetSize();


		//追尾するなら
		if (m_bHoming == true)
		{
			//敵の位置を取得
			D3DXVECTOR3 enemyPos = m_pTargetEnemy->GetPos();

			//移動量を決めるためのベクトル
			D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//敵の位置から自身の位置のベクトルを求める
			moveVec = D3DXVECTOR3(enemyPos.x - posEffect.x, 0.0f, enemyPos.z - posEffect.z);

			//算出したベクトルを正規化
			D3DXVec3Normalize(&moveVec, &moveVec);

			//移動量設定
			m_move = moveVec * MAGIC_FIRE_BALL_MOVE;
		}

		//移動量を加算
		posEffect += m_move;

		//位置を設定
		m_pEffect3D[nCntEffect]->SetPos(posEffect, sizeEffect);
	}
	
	//位置を取得
	m_pos = GetPos();

	//移動量を加算
	m_pos += m_move;

	//位置を設定
	SetPos(m_pos);

	//3Dポリゴンとの当たり判定
	if (CFloor::Collision(this) == true)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//エフェクトを消す
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//モデルとの当たり判定
	if (CModelSingle::CollisionAny(this) == true)
	{
		for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
		{
			if (m_pEffect3D[nCntEffect] != nullptr)
			{
				//エフェクトを消す
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
		}
		Uninit();
		return;
	}

	//オブジェクト情報を入れるポインタ
	pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類が敵だったら
		if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT ||
			pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE)
		{
			//敵にキャスト
			CEnemy *pEnemyObj = nullptr;
			pEnemyObj = (CEnemy*)pObject;

			//敵との当たり判定
			if (pEnemyObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//ダメージ状態でないなら
				if (pEnemyObj->GetMovePattern() != CEnemy::ENEMY_MOVE_PATTERN::DAMAGE)
				{
					//爆発エフェクトの生成
					CExplosion::Create(m_pos, D3DXVECTOR3(FIRE_BALL_EXPLOSION_SIZE_X, FIRE_BALL_EXPLOSION_SIZE_Y, 0.0f), FIRE_BALL_EXPLOSION_EFFECT_NUM,
						               FIRE_BALL_EXPLOSION_EFFECT_COLOR, FIRE_BALL_EXPLOSION_MOVE_MIN, FIRE_BALL_EXPLOSION_MOVE_MAX,
						               FIRE_BALL_EXPLOSION_GRAVITY, FIRE_BALL_EXPLOSION_COL_A_MIN, FIRE_BALL_EXPLOSION_COL_A_MAX,
						               FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE);

					//火の粉エフェクトの生成
					CSpark::Create(m_pos, D3DXVECTOR3(FIRE_BALL_SPARK_SIZE, FIRE_BALL_SPARK_SIZE, 0.0f), FIRE_BALL_SPARK_EFFECT_NUM,
						           FIRE_BALL_SPARK_EFFECT_COLOR, FIRE_BALL_SPARK_MOVE_MIN, FIRE_BALL_SPARK_MOVE_MAX, FIRE_BALL_SPARK_GRAVITY,
						           FIRE_BALL_SPARK_COL_A_MIN, FIRE_BALL_SPARK_COL_A_MAX, FIRE_BALL_SPARK_SUBTRACTION_MOVE);

					//ダメージ状態にする
					pEnemyObj->SetMovePattern(CEnemy::ENEMY_MOVE_PATTERN::DAMAGE);
					//敵の種類によってダメージを変える
					int nDamage = 0;
					switch (pObject->GetObjType())
					{
					case CObject::OBJTYPE::ENEMY_BEE:
						nDamage = FIRE_BALL_ENEMY_BEE_DAMAGE;
						CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_BEE_ADD_SP);
						break;
					case CObject::OBJTYPE::ENEMY_FAT:
						nDamage = FIRE_BALL_ENEMY_FAT_DAMAGE;
						CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_FAT_ADD_SP);
						break;
					default:
						break;
					}
					//HPを減らす
					pEnemyObj->AddLife(-nDamage);
					//HPが0以下になったら
					if (pEnemyObj->GetLife() <= 0)
					{
						switch (pObject->GetObjType())
						{
						case CObject::OBJTYPE::ENEMY_BEE:
							//スコアを増やす
							CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);
							break;
						case CObject::OBJTYPE::ENEMY_FAT:
							//スコアを増やす
							CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_FAT_UNINIT_SCORE);
							break;
						default:
							break;
						}
						//消す
						pEnemyObj->Uninit();
					}

					//消す
					for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
					{
						if (m_pEffect3D[nCntEffect] != nullptr)
						{
							//エフェクトを消す
							m_pEffect3D[nCntEffect]->Uninit();
							m_pEffect3D[nCntEffect] = nullptr;
						}
					}
					Uninit();
					return;
				}
			}
		}
		else if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BOSS)
		{
			//ボスにキャスト
			CEnemyBoss *pEnemyBossObj = nullptr;
			pEnemyBossObj = (CEnemyBoss*)pObject;

			//敵との当たり判定
			if (pEnemyBossObj->CollisionOnly(this, m_size.x / 2.0f) == true)
			{
				//ダメージ状態でないなら
				if (pEnemyBossObj->GetDamage() == false)
				{
					//爆発エフェクトの生成
					CExplosion::Create(m_pos, D3DXVECTOR3(FIRE_BALL_EXPLOSION_SIZE_X, FIRE_BALL_EXPLOSION_SIZE_Y, 0.0f), FIRE_BALL_EXPLOSION_EFFECT_NUM,
									   FIRE_BALL_EXPLOSION_EFFECT_COLOR, FIRE_BALL_EXPLOSION_MOVE_MIN, FIRE_BALL_EXPLOSION_MOVE_MAX,
									   FIRE_BALL_EXPLOSION_GRAVITY, FIRE_BALL_EXPLOSION_COL_A_MIN, FIRE_BALL_EXPLOSION_COL_A_MAX,
									   FIRE_BALL_EXPLOSION_SUBTRACTION_MOVE);

					//火の粉エフェクトの生成
					CSpark::Create(m_pos, D3DXVECTOR3(FIRE_BALL_SPARK_SIZE, FIRE_BALL_SPARK_SIZE, 0.0f), FIRE_BALL_SPARK_EFFECT_NUM,
								   FIRE_BALL_SPARK_EFFECT_COLOR, FIRE_BALL_SPARK_MOVE_MIN, FIRE_BALL_SPARK_MOVE_MAX, FIRE_BALL_SPARK_GRAVITY,
								   FIRE_BALL_SPARK_COL_A_MIN, FIRE_BALL_SPARK_COL_A_MAX, FIRE_BALL_SPARK_SUBTRACTION_MOVE);

					//ダメージ状態にする
					pEnemyBossObj->SetDamage(true);
					CManager::GetPlayData()->GetSpGauge()->AddGauge(FIRE_BALL_ENEMY_BOSS_ADD_SP);
					//HPを減らす
					pEnemyBossObj->AddLife(-FIRE_BALL_ENEMY_BOSS_DAMAGE);
					//HPが0以下になったら
					if (pEnemyBossObj->GetLife() <= 0)
					{
						//スコアを増やす
						CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BOSS_UNINIT_SCORE);

						//ゲームクリアにする
						CManager::GetInstance()->GetPlayData()->SetGameClear(true);

						//消す
						pEnemyBossObj->Uninit();
					}

					//消す
					for (int nCntEffect = 0; nCntEffect < (int)m_pEffect3D.size(); nCntEffect++)
					{
						if (m_pEffect3D[nCntEffect] != nullptr)
						{
							//エフェクトを消す
							m_pEffect3D[nCntEffect]->Uninit();
							m_pEffect3D[nCntEffect] = nullptr;
						}
					}
					Uninit();
					return;
				}
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//描画処理
//================================================
void CFireBall::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CFireBall* CFireBall::Create(D3DXVECTOR3 pos, int nRotPartitionNum, int nLayer, int nLife, float fPower, D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CFireBall *pFireBall = nullptr;
	if (pFireBall == nullptr)
	{
		pFireBall = new CFireBall();
		if (pFireBall != nullptr)
		{
			pFireBall->m_nRotPartitionNum = nRotPartitionNum;
			pFireBall->m_nLayer = nLayer;
			pFireBall->m_nLife = nLife;
			pFireBall->m_fPower = fPower;
			pFireBall->m_move = move;
			pFireBall->Init(pos, size);
		}
	}
	return pFireBall;
}
