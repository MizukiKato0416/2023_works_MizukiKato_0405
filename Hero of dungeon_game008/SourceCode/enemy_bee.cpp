//================================================
//敵(蜂)の処理
//Author:KatoMizuki
//================================================
#include "manager.h"
#include "enemy_bee.h"
#include "motion_enemy_bee.h"
#include "renderer.h"
#include "floor.h"
#include "model.h"
#include "model_single.h"
#include "x_load.h"
#include "player.h"
#include "bullet_enemy.h"
#include "mesh_trajectory.h"
#include "play_data.h"
#include "gauge.h"
#include "effect3D.h"
#include "spark.h"
#include "magic_thunder.h"
#include "exclamation_mark.h"
#include "shadow.h"
#include "score.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_BEE_GRAVITY							(0.2f)		//重力の大きさ
#define ENEMY_BEE_SIZE_ADJUSTMENT					(90.0f)		//サイズ調整値
#define ENEMY_BEE_FLY_COUNTER						(90)		//飛行時の上下移動カウンター
#define ENEMY_BEE_FLY_ADD_SPEED						(0.02f)		//飛行時の上下移動量加速値
#define ENEMY_BEE_FLY_MAX_SPEED						(0.4f)		//飛行時の上下移動量上限値
#define ENEMY_BEE_MOVE_SPEED						(4.0f)		//通常移動の移動量
#define ENEMY_BEE_DAMAGE_MOVE_SPEED					(1.0f)		//ダメージ状態の移動量
#define ENEMY_BEE_ATTACK_DIFFER						(400.0f)	//攻撃をしてくる範囲
#define ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER			(600.0f)	//追いかけてくる範囲
#define ENEMY_BEE_LIFE								(30)		//ライフ
#define ENEMY_BEE_HIT_EFFECT_SIZE					(40.0f)		//ヒットエフェクトの大きさ
#define ENEMY_BEE_HIT_EFFECT_POS_Y					(10.0f)		//ヒットエフェクトの位置調整Y
#define ENEMY_BEE_HIT_EFFECT_POS_XZ					(20.0f)		//ヒットエフェクトの位置調整XZ
#define ENEMY_BEE_HIT_ADD_SP						(3)			//ヒットした時のSP増加量
#define ENEMY_BEE_HIT_ADD_MP						(14)		//ヒットした時のMP増加量
#define ENEMY_BEE_HIT_DAMAGE						(3)			//ヒットした時ダメージ
#define ENEMY_BEE_EXCLAMATION_MARK_POS				(180.0f)	//ビックリマークの位置調整値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEnemyBee::CEnemyBee(int nPriority):CEnemy(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_pModel = nullptr;
	m_nFlyMoveCounter = 0;
	m_pMotionEnemyBee = nullptr;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CEnemyBee::~CEnemyBee()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemyBee::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bNotice = false;
	m_nFlyMoveCounter = 0;
	m_movePattern = ENEMY_MOVE_PATTERN::STOP;
	m_nLife = ENEMY_BEE_LIFE;

	//位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクトの種類の設定
	SetObjType(CEnemy::OBJTYPE::ENEMY_BEE);

	//モデルの生成
	m_pModel = CModel::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_rot, CManager::GetInstance()->GetXload()->GetType(CXload::X_TYPE_BEE));

	//モーションの生成
	m_pMotionEnemyBee = CMotionEnemyBee::Create(this);
	m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL, this);

	//サイズを取得
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_pModel->GetSize();

	//サイズのXとZを比べて大きいほうをXとZそれぞれに割り当てる
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x - ENEMY_BEE_SIZE_ADJUSTMENT, modelSize.y, modelSize.x - ENEMY_BEE_SIZE_ADJUSTMENT);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z - ENEMY_BEE_SIZE_ADJUSTMENT, modelSize.y, modelSize.z - ENEMY_BEE_SIZE_ADJUSTMENT);
	}

	//サイズの設定
	SetSize(m_size);

	//影の設定
	m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z), D3DXVECTOR3(m_size.x, 0.0f, m_size.z), this);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CEnemyBee::Uninit(void)
{
	CEnemy::Uninit();
}

//================================================
//更新処理
//================================================
void CEnemyBee::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1フレーム前の位置設定
	SetPosOld(m_posOld);

	//移動処理
	Move();

	//移動パターン処理
	MoveType();

	m_pos += m_move;		//移動量反映

	//モーション
	m_pMotionEnemyBee->Update(this);

	//回転の慣性
	Rotate();

	//位置反映
	SetPos(m_pos);

	//プレイヤーとの当たり判定
	CPlayer::Collision(this, m_size.x / 2.0f);

	//敵との当たり判定
	Collision(this, m_size.x / 2.0f);

	//斬撃の当たり判定
	if (CollisionSlash() == true)
	{
		return;
	}

	//雷魔法の当たり判定
	if (CollisionMagicThunder() == true)
	{
		return;
	}

	//3Dポリゴンの床との当たり判定
	if (CFloor::Collision(this) == true)
	{
		m_move.y = 0.0f;
		m_move.y -= 40.0f;
	}

	//モデルとの当たり判定
	if (CModelSingle::Collision(this) == true)
	{
		m_move.y = 0.0f;
		m_move.y -= 40.0f;
	}

	//位置取得
	pos = GetPos();
	m_pos = pos;
}

//================================================
//描画処理
//================================================
void CEnemyBee::Draw(void)
{
	CEnemy::Draw();

	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;

	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);

	while (pObject != nullptr)
	{
		//現在のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pObject->GetPos();

			//自身から対象のオブジェクトまでの距離を求める
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) +
				                  (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//求めた距離が既定の数値以下だったら
			if (fRadius <= ENEMY_DRAW_DIFFER)
			{
				//描画されている状態にする
				m_bDraw = true;
				//モデルの描画
				m_pModel->Draw();
			}
			else
			{
				//描画されていない状態にする
				m_bDraw = false;
				
				//影を描画しないようにする
				m_pShadow->SetDraw(false);

				//プレイヤーにキャスト
				CPlayer *pPlayerObj = nullptr;
				pPlayerObj = (CPlayer*)pObject;

				//ロックオンしているなら
				if (pPlayerObj->GetEnemyNear() == this)
				{
					//nullにする
					pPlayerObj->SetEnemyNear(nullptr);
				}
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//生成処理
//================================================
CEnemyBee *CEnemyBee::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CEnemyBee *pEnemyBee = nullptr;
	if (pEnemyBee == nullptr)
	{
		pEnemyBee = new CEnemyBee;
		if (pEnemyBee != nullptr)
		{
			pEnemyBee->m_rot = rot;
			pEnemyBee->Init(pos, pEnemyBee->m_size);
		}
	}
	return pEnemyBee;
}

//================================================
//モデルの動き処理
//================================================
void CEnemyBee::Move(void)
{
	//飛行時の上下移動の加速量保存用変数
	float fFlySpeed = 0.0f;

	//カウンターが規定値より少ないとき
	if (m_nFlyMoveCounter < ENEMY_BEE_FLY_COUNTER)
	{
		fFlySpeed = ENEMY_BEE_FLY_ADD_SPEED;
	}
	else
	{
		fFlySpeed = -ENEMY_BEE_FLY_ADD_SPEED;
	}

	//移動量を加算
	m_move.y += fFlySpeed;

	//移動量が規定値より大きくなったら
	if (m_move.y >= ENEMY_BEE_FLY_MAX_SPEED)
	{
		//規定値にする
		m_move.y = ENEMY_BEE_FLY_MAX_SPEED;
	}
	else if (m_move.y <= -ENEMY_BEE_FLY_MAX_SPEED)
	{
		//規定値にする
		m_move.y = -ENEMY_BEE_FLY_MAX_SPEED;
	}

	//カウンターを加算
	m_nFlyMoveCounter++;

	//カウンターが規定値よりおおきくなったら
	if (m_nFlyMoveCounter >= ENEMY_BEE_FLY_COUNTER * 2)
	{
		//0にする
		m_nFlyMoveCounter = 0;
	}
}

//================================================
//モデルの位置設定処理
//================================================
void CEnemyBee::SetModelPos(D3DXVECTOR3 pos)
{
	m_pModel->SetPos(pos);
}

//================================================
//モデルの位置取得処理
//================================================
D3DXVECTOR3 CEnemyBee::GetModelPos(void)
{
	return m_pModel->GetPos();
}

//================================================
//モデルの向き設定処理
//================================================
void CEnemyBee::SetModelRot(D3DXVECTOR3 rot)
{
	m_pModel->SetRot(rot);
}

//================================================
//モデルの向き取得処理
//================================================
D3DXVECTOR3 CEnemyBee::GetModelRot(void)
{
	return m_pModel->GetRot();
}

//================================================
//動きに関する処理
//================================================
void CEnemyBee::MoveType(void)
{
	//オブジェクト情報を入れるポインタ
	CObject *pObject = nullptr;
	//オブジェクト情報を保存するポインタ変数
	CObject *pSaveObject = nullptr;
	//先頭のポインタを代入
	pObject = pObject->GetTopObj(CObject::PRIORITY_PLAYER);
	//プレイヤーとの角度保存用変数
	float fRot = 0.0f;

	while (pObject != nullptr)
	{
		//現在の次のオブジェクトのポインタを保存
		pSaveObject = pObject;

		//オブジェクトの種類がプレイヤーだったら
		if (pObject->GetObjType() == CObject::OBJTYPE::PLAYER)
		{
			//オブジェクトの位置を取得
			D3DXVECTOR3 posObj = pObject->GetPos();

			//プレイヤーから自身までのの距離を求める
			float fRadius = sqrtf((posObj.x - m_pos.x) * (posObj.x - m_pos.x) + (posObj.z - m_pos.z) * (posObj.z - m_pos.z));

			//プレイヤーと自身の距離が既定の距離の範囲内且つ、ダメージを受けている状態でないとき
			if (fRadius <= ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER && fRadius > ENEMY_BEE_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{
				//プレイヤーに向かって動くようにする
				m_movePattern = ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER;

				//プレイヤーに気づいていないなら
				if (m_bNotice == false)
				{
					//気づかせる
					m_bNotice = true;
					//ビックリマークを出す
					CExclamationMark::Create(D3DXVECTOR3(m_pos.x, m_pos.y + ENEMY_BEE_EXCLAMATION_MARK_POS, m_pos.z),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, ENEMY_EXCLAMATION_MARK_SIZE, 0.0f),
						                     D3DXVECTOR3(ENEMY_EXCLAMATION_MARK_SIZE, 0.1f, 0.0f),
						                     D3DXVECTOR3(0.0f, ENEMY_EXCLAMATION_MARK_ADD_SIZE, 0.0f),
						                     this, ENEMY_EXCLAMATION_MARK_LIFE);

				}
			}
			else if (fRadius <= ENEMY_BEE_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{//プレイヤーと自身の距離が既定の距離より短かったら且つ、ダメージを受けている状態でないとき
				//攻撃する
				m_movePattern = ENEMY_MOVE_PATTERN::ATTACK;
			}
			else if (fRadius > ENEMY_BEE_MOVE_TO_PLAYER_MAX_DIFFER &&
					m_movePattern == ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER)
			{//プレイヤーと自身の距離が既定の距離より長くなり行動パターンがプレイヤーに向かって動いている状態のとき
				//停止させる
				m_movePattern = ENEMY_MOVE_PATTERN::STOP;

				//プレイヤーに気づいてたなら
				if (m_bNotice == true)
				{
					//気づいていない状態にする
					m_bNotice = false;
				}
			}

			//プレイヤーと対象のオブジェクトの角度を求める
			fRot = atan2((posObj.x - m_pos.x), (posObj.z - m_pos.z)) - D3DX_PI;
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}


	//動きの種類によって処理を変える
	switch (m_movePattern)
	{
	case ENEMY_MOVE_PATTERN::MOVE:				//移動
		//移動量を設定
		m_move.z = -cosf(m_rot.y) * ENEMY_BEE_MOVE_SPEED;
		m_move.x = -sinf(m_rot.y) * ENEMY_BEE_MOVE_SPEED;

		//カウンターを加算
		m_nMoveCounter++;
		//規定値より大きくなったら
		if (m_nMoveCounter >= ENEMY_MOVE_MAX_COUNT)
		{
			//0に戻す
			m_nMoveCounter = 0;
			//停止状態にする
			m_movePattern = ENEMY_MOVE_PATTERN::STOP;
		}
		break;
	case ENEMY_MOVE_PATTERN::STOP:				//停止
		//移動量を0にする
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//カウンターを加算
		m_nStopCounter++;
		//規定値より大きくなったら
		if (m_nStopCounter >= ENEMY_STOP_MAX_COUNT)
		{
			//0に戻す
			m_nStopCounter = 0;
			//回転状態にする
			m_movePattern = ENEMY_MOVE_PATTERN::TURN;
			//目的の方向を設定する
			m_fObjectiveRot = ENEMY_TURN_RAND;
			//回転をさせる
			m_bRotate = true;
		}
		break;
	case ENEMY_MOVE_PATTERN::TURN:				//回転
		//回転し終わったら
		if (m_bRotate == false)
		{
			//移動状態にする
			m_movePattern = ENEMY_MOVE_PATTERN::MOVE;
		}
		break;
	case ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER:	//プレイヤーのほうに向かって移動
		//移動量を設定
		m_move.z = -cosf(fRot) * ENEMY_BEE_MOVE_SPEED;
		m_move.x = -sinf(fRot) * ENEMY_BEE_MOVE_SPEED;

		//目的の方向を設定する
		m_fObjectiveRot = fRot;
		//回転をさせる
		m_bRotate = true;
		break;
	case ENEMY_MOVE_PATTERN::ATTACK:			//攻撃
		//移動量を0にする
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		//カウンターを加算
		m_nAttackCounter++;
		//規定値より大きくなったら
		if (m_nAttackCounter >= ENEMY_ATTACK_STOP_MAX_COUNT)
		{
			//0に戻す
			m_nAttackCounter = 0;
			//弾を出して攻撃する
			CBulletEnemy::Create(m_pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));
		}
		else
		{
			//目的の方向を設定する
			m_fObjectiveRot = fRot;
			//回転をさせる
			m_bRotate = true;
		}
		break;
	case ENEMY_MOVE_PATTERN::DAMAGE:			//被ダメージ
		//カウンターを加算
		m_nDamageCounter++;

		//規定値よりもカウンターが大きくなったら
		if (m_nDamageCounter >= ENEMY_DAMAGE_MAX_COUNT)
		{
			//カウンターを戻す
			m_nDamageCounter = 0;
			//停止させる
			m_movePattern = ENEMY_MOVE_PATTERN::STOP;
			//ニュートラルモーションにする
			m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL, this);
		}
		else
		{
			//プレイヤーと反対の方にノックバックさせる
			m_move.z = cosf(fRot) * ENEMY_BEE_DAMAGE_MOVE_SPEED;
			m_move.x = sinf(fRot) * ENEMY_BEE_DAMAGE_MOVE_SPEED;

			//被ダメージモーションじゃなかったら
			if (m_pMotionEnemyBee->GetMotion() != CMotionRoad::MOTION_ENEMY_BEE_TYPE_DAMAGE)
			{
				//ダメージモーションにする
				m_pMotionEnemyBee->SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_DAMAGE, this);
			}
		}
		break;
	default:
		break;
	}
}

//================================================
//斬撃の当たり判定
//================================================
bool CEnemyBee::CollisionSlash(void)
{
	//剣の軌跡との当たり判定
	if (CMeshTrajectory::CollisionSphere(this, m_size.x / 3.0f) == true && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
	{//ダメージを受けていなくて攻撃モーションではなかったら

		//カメラのポインタ配列1番目のアドレス取得
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//cameraの取得
		CCamera* pCamera = &**pCameraAddress;
		//カメラの向き取得
		D3DXVECTOR3 rotCamera = pCamera->GetRotV();

		//ヒットエフェクトを出す
		CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
			              m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
			              D3DXVECTOR3(ENEMY_BEE_HIT_EFFECT_SIZE, ENEMY_BEE_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			              CEffect3D::EFFECT3D_TYPE::HIT);

		//火の粉エフェクトの生成
		CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
			                       m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
			           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
			           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
			           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

		//SPゲージを増やす
		CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_BEE_HIT_ADD_SP);
		//MPゲージを増やす
		CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(ENEMY_BEE_HIT_ADD_MP);

		//ライフを減らす
		m_nLife -= ENEMY_BEE_HIT_DAMAGE;
		//ライフが0になったら
		if (m_nLife <= 0)
		{
			//スコアを増やす
			CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);

			//消す
			Uninit();
			return true;
		}
		//ダメージを受けたときのパターンにする
		m_movePattern = ENEMY_MOVE_PATTERN::DAMAGE;
	}
	return false;
}

//================================================
//雷魔法の当たり判定
//================================================
bool CEnemyBee::CollisionMagicThunder(void)
{
	if (CMagicThunder::Collision(this) == true)
	{
		//ダメージ状態でないなら
		if (m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
		{
			//ダメージ状態にする
			m_movePattern = ENEMY_MOVE_PATTERN::DAMAGE;

			//HPを減らす
			m_nLife -= MAGIC_THUNDER_EFFECT_ENEMY_BEE_DAMAGE;

			//カメラのポインタ配列1番目のアドレス取得
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//cameraの取得
			CCamera* pCamera = &**pCameraAddress;
			//カメラの向き取得
			D3DXVECTOR3 rotCamera = pCamera->GetRotV();

			//ヒットエフェクトを出す
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
				              m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
				              D3DXVECTOR3(ENEMY_BEE_HIT_EFFECT_SIZE, ENEMY_BEE_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				              CEffect3D::EFFECT3D_TYPE::HIT);

			//火の粉エフェクトの生成
			CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BEE_HIT_EFFECT_POS_Y,
				                       m_pos.z + cosf(rotCamera.y) * ENEMY_BEE_HIT_EFFECT_POS_XZ),
				           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
				           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
				           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

			//HPが0以下になったら
			if (m_nLife <= 0)
			{
				//スコアを増やす
				CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BEE_UNINIT_SCORE);

				//消す
				Uninit();
				return true;
			}
		}
	}
	return false;
}
