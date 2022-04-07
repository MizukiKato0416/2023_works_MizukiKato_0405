//================================================
//ボスの処理
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "manager.h"
#include "enemy_boss.h"
#include "motion_enemy_boss.h"
#include "renderer.h"
#include "floor.h"
#include "model.h"
#include "model_single.h"
#include "x_load.h"
#include "player.h"
#include "mesh_trajectory.h"
#include "effect3D.h"
#include "play_data.h"
#include "gauge.h"
#include "meshfield.h"
#include "spark.h"
#include "magic_thunder.h"
#include "guard_effect.h"
#include "texture.h"
#include "exclamation_mark.h"
#include "bullet_enemy.h"
#include "shadow.h"
#include "score.h"
#include "sound.h"

//================================================
//マクロ定義
//================================================
#define ENEMY_BOSS_SIZE_ADJUSTMENT				(30.0f)									//サイズ調整値
#define ENEMY_BOSS_GRAVITY						(0.2f)									//重力の大きさ
#define ENEMY_BOSS_MOVE_SPEED					(4.0f)									//通常移動の移動量
#define ENEMY_BOSS_RUSH_MOVE_SPEED				(15.0f)									//突進攻撃の移動量
#define ENEMY_BOSS_DAMAGE_MOVE_SPEED			(1.0f)									//ダメージを受けたときの移動量
#define ENEMY_BOSS_ATTACK_COLLISION_RADIUS		(80.0f)									//攻撃時の当たり判定の半径
#define ENEMY_BOSS_ATTACK_COLLISION_OFFSET		(50.0f)									//攻撃時の当たり判定の位置(親とのオフセット)
#define ENEMY_BOSS_LIFE							(300)									//ライフ
#define ENEMY_BOSS_HIT_EFFECT_SIZE				(60.0f)									//ヒットエフェクトの大きさ
#define ENEMY_BOSS_HIT_EFFECT_POS_Y				(60.0f)									//ヒットエフェクトの位置調整Y
#define ENEMY_BOSS_HIT_EFFECT_POS_XZ			(60.0f)									//ヒットエフェクトの位置調整XZ
#define ENEMY_BOSS_HIT_ADD_SP					(6)										//ヒットした時のSP増加量
#define ENEMY_BOSS_GUARD_ADD_SP					(2)										//ガードした時のSP増加量
#define ENEMY_BOSS_HIT_ADD_MP					(14)									//ヒットした時のMP増加量
#define ENEMY_BOSS_HIT_DAMAGE					(7)										//ヒットした時のダメージ量
#define ENEMY_BOSS_ATTACK_RUSH_COUNTER			(4)										//突進攻撃をするときの攻撃回数
#define ENEMY_BOSS_ATTACK_RUSH_COUNT			(180)									//突進攻撃をするまでの時間
#define ENEMY_BOSS_ATTACK_RUSH_COUNT_MAX		(ENEMY_BOSS_ATTACK_RUSH_COUNT + 240)	//突進攻撃をする時間
#define ENEMY_BOSS_ATTACK_MAGIC_COUNT			(240)									//魔法攻撃をするまでの時間
#define ENEMY_BOSS_ATTACK_RUSH_COLL				(5)										//突進攻撃中に当たり判定が復活するまでのカウント
#define ENEMY_BOSS_ATTACK_MAGIC_INTERVAL		(40)									//魔法攻撃を出す間隔
#define ENEMY_BOSS_MOVE_TO_PLAYER_MAX_DIFFER	(10000.0f)								//プレイヤーを追う距離
#define ENEMY_BOSS_ATTACK_DIFFER				(120.0f)								//プレイヤーに攻撃する距離
#define ENEMY_BOSS_ATTACK_STOP_MAX_COUNT		(90.0f)									//敵が攻撃するまでの時間

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CEnemyBoss::CEnemyBoss(int nPriority) :CEnemy(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bAttackColl = false;
	m_pParent = nullptr;
	memset(&m_apModel, NULL, sizeof(m_apModel));
	m_pMotionEnemyBoss = nullptr;
	m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::NONE;
	m_nCntAttack = 0;
	m_bDamage = false;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CEnemyBoss::~CEnemyBoss()
{

}

//================================================
//初期化処理
//================================================
HRESULT CEnemyBoss::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_posOld = pos;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fObjectiveRot = 0.0f;
	m_fNumRot = 0.0f;
	m_bRotate = false;
	m_bAttackColl = true;
	m_bNotice = false;
	m_movePattern = ENEMY_MOVE_PATTERN::STOP;
	m_nStopCounter = 0;
	m_nAttackCounter = 0;
	m_nDamageCounter = 0;
	m_nLife = ENEMY_BOSS_LIFE;
	m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::NORMAL;
	m_nCntAttack = 0;
	m_bDamage = false;
	m_bDraw = true;

	//モデルの生成
	//textファイル読み込み
	FILE *pFile = fopen("data/MOTION/motion_enemy_boss.txt", "r");
	if (pFile != nullptr)
	{
		char cString[128];
		//一行ずつ保存
		while (fgets(cString, 128, pFile) != nullptr)
		{
			//文字列を保存
			fscanf(pFile, "%s", cString);
			//文字列の中にPARTSSETがあったら
			if (strncmp("PARTSSET", cString, 9) == 0)
			{
				fscanf(pFile, "%*s%*s");

				//インデックス読み込み
				int nIndex = 0;
				fscanf(pFile, "%*s%*s%d", &nIndex);

				//親読み込み
				int nParent = 0;
				fscanf(pFile, "%*s%*s%d", &nParent);
				fscanf(pFile, "%*s%*s");

				//位置読み込み
				D3DXVECTOR3 modelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &modelPos.x, &modelPos.y, &modelPos.z);

				//向き読み込み
				D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				fscanf(pFile, "%*s%*s%f%f%f", &rot.x, &rot.y, &rot.z);

				//モデル生成
				int nModelType = 0;
				nModelType = CXload::X_TYPE_ENEMY_BOSS_BODY;
				m_apModel[nIndex] = CModel::Create(modelPos, rot, CManager::GetInstance()->GetXload()->GetType(nModelType + nIndex));

				//親の設定
				if (nParent == -1)
				{
					m_apModel[nIndex]->SetParent(nullptr);
				}
				else
				{
					m_apModel[nIndex]->SetParent(m_apModel[nParent]);
				}

				if (nIndex == MAX_ENEMY_BOSS_MODEL - 1)
				{
					break;
				}
			}
		}
	}
	else
	{
		printf("ファイルが開けませんでした\n");
	}
	fclose(pFile);

	//位置の設定
	SetPos(m_pos);
	SetPosOld(m_posOld);

	//オブジェクトの種類の設定
	SetObjType(CObject::OBJTYPE::ENEMY_BOSS);

	//モーションの生成
	m_pMotionEnemyBoss = CMotionEnemyBoss::Create(this);
	m_pMotionEnemyBoss->SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL, this);
	
	//サイズを取得
	D3DXVECTOR3 modelSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	modelSize = m_apModel[0]->GetSize();

	//サイズのXとZを比べて大きいほうをXとZそれぞれに割り当てる
	if (modelSize.x >= modelSize.z)
	{
		m_size = D3DXVECTOR3(modelSize.x + ENEMY_BOSS_SIZE_ADJUSTMENT, modelSize.y, modelSize.x + ENEMY_BOSS_SIZE_ADJUSTMENT);
	}
	else
	{
		m_size = D3DXVECTOR3(modelSize.z + ENEMY_BOSS_SIZE_ADJUSTMENT, modelSize.y, modelSize.z + ENEMY_BOSS_SIZE_ADJUSTMENT);
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
void CEnemyBoss::Uninit(void)
{
	CEnemy::Uninit();
	Release();
}

//================================================
//更新処理
//================================================
void CEnemyBoss::Update(void)
{
	//位置取得
	D3DXVECTOR3 pos = GetPos();

	m_pos = pos;
	m_posOld = pos;

	//1フレーム前の位置設定
	SetPosOld(m_posOld);

	//重力
	m_move.y -= ENEMY_GRAVITY;

	//移動処理
	MoveType();

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

	//移動量反映
	m_pos += m_move;		

	//モーション
	m_pMotionEnemyBoss->Update(this);

	//回転の慣性
	Rotate();

	//位置反映
	SetPos(m_pos);

	//プレイヤーとの当たり判定
	CPlayer::Collision(this, m_size.x / 2.0f);

	//敵との当たり判定
	Collision(this, m_size.x / 2.0f);

	//プレイヤーへの攻撃の当たり判定			
	ToPlayerAttackCollision();

	//ダメージの処理
	Damage();

	//3Dポリゴンとの当たり判定
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
void CEnemyBoss::Draw(void)
{
	CEnemy::Draw();

	//モデルの描画
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}

	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			//計算用マトリックス

	//攻撃する際の当たり判定の位置設定
	for (int nCntMtx = 0; nCntMtx < ENEMY_BOSS_MAX_ATTACK_COLLISION; nCntMtx++)
	{
		D3DXMATRIX mtx;									//計算用マトリックス
		D3DXMatrixIdentity(&m_aAttackCollMtx[nCntMtx]);	//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtx);						//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxTrans);					//ワールドマトリックスの初期化

		//オフセット
		float fOffset = 0.0f;
		
		switch (nCntMtx)
		{
		case 0:
			fOffset = -ENEMY_BOSS_ATTACK_COLLISION_OFFSET;
			break;
		case 1:
			fOffset = ENEMY_BOSS_ATTACK_COLLISION_OFFSET;
			break;
		default:
			break;
		}
		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, fOffset, 0.0f, 0.0f);
		D3DXMatrixMultiply(&m_aAttackCollMtx[nCntMtx], &m_aAttackCollMtx[nCntMtx], &mtxTrans);

		//算出した各パーツのワールドマトリックスと親のワールドマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_aAttackCollMtx[nCntMtx], &m_aAttackCollMtx[nCntMtx], m_apModel[2 + nCntMtx]->GetMtxPoint());

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_aAttackCollMtx[nCntMtx]);
	}
}

//================================================
//生成処理
//================================================
CEnemyBoss *CEnemyBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//インスタンスの生成
	CEnemyBoss *pEnemyBoss = nullptr;
	if (pEnemyBoss == nullptr)
	{
		pEnemyBoss = new CEnemyBoss;
		if (pEnemyBoss != nullptr)
		{
			pEnemyBoss->m_rot = rot;
			pEnemyBoss->Init(pos, pEnemyBoss->m_size);
		}
	}
	return pEnemyBoss;
}

//================================================
//モデルの位置設定処理
//================================================
void CEnemyBoss::SetModelPos(int nCntModel, D3DXVECTOR3 pos)
{
	m_apModel[nCntModel]->SetPos(pos);
}

//================================================
//モデルの位置取得処理
//================================================
D3DXVECTOR3 CEnemyBoss::GetModelPos(int nCntModel)
{
	return m_apModel[nCntModel]->GetPos();
}

//================================================
//モデルの向き設定処理
//================================================
void CEnemyBoss::SetModelRot(int nCntModel, D3DXVECTOR3 rot)
{
	m_apModel[nCntModel]->SetRot(rot);
}

//================================================
//モデルの向き取得処理
//================================================
D3DXVECTOR3 CEnemyBoss::GetModelRot(int nCntModel)
{
	return m_apModel[nCntModel]->GetRot();
}

//================================================
//動きに関する処理
//================================================
void CEnemyBoss::MoveType(void)
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

			//プレイヤーと自身の距離が既定の距離の範囲内且つ、モーションが攻撃ではない、ダメージを受けている状態でないとき且つ通常攻撃の時
			if (fRadius <= ENEMY_BOSS_MOVE_TO_PLAYER_MAX_DIFFER && fRadius > ENEMY_BOSS_ATTACK_DIFFER &&
				m_pMotionEnemyBoss->GetMotion() != CMotionRoad::MOTION_ENEMY_BOSS_TYPE_ATTACK_01 &&
				m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE && m_attackPattern == ENEMY_BOSS_ATTACK_PATTERN::NORMAL)
			{
				//プレイヤーに向かって動くようにする
				m_movePattern = ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER;
			}
			else if (fRadius <= ENEMY_BOSS_ATTACK_DIFFER && m_movePattern != ENEMY_MOVE_PATTERN::DAMAGE)
			{//プレイヤーと自身の距離が既定の距離より短かったら且つ、ダメージを受けている状態でないとき
				//攻撃する
				m_movePattern = ENEMY_MOVE_PATTERN::ATTACK;
			}
			else if (fRadius > ENEMY_BOSS_MOVE_TO_PLAYER_MAX_DIFFER &&
					m_movePattern == ENEMY_MOVE_PATTERN::MOVE_TO_PLAYER)
			{//プレイヤーと自身の距離が既定の距離より長くなり行動パターンがプレイヤーに向かって動いている状態の時
				//停止させる
				m_movePattern = ENEMY_MOVE_PATTERN::STOP;
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
		m_move.z = -cosf(m_rot.y) * ENEMY_BOSS_MOVE_SPEED;
		m_move.x = -sinf(m_rot.y) * ENEMY_BOSS_MOVE_SPEED;

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
		m_move.z = -cosf(fRot) * ENEMY_BOSS_MOVE_SPEED;
		m_move.x = -sinf(fRot) * ENEMY_BOSS_MOVE_SPEED;

		//目的の方向を設定する
		m_fObjectiveRot = fRot;
		//回転をさせる
		m_bRotate = true;
		break;
	case ENEMY_MOVE_PATTERN::ATTACK:			//攻撃

		//攻撃の種類によって処理を分ける
		switch (m_attackPattern)
		{
		case CEnemyBoss::ENEMY_BOSS_ATTACK_PATTERN::NORMAL:
			//移動量を0にする
			m_move.x = 0.0f;
			m_move.z = 0.0f;

			//カウンターを加算
			m_nAttackCounter++;
			//規定値より大きくなったら
			if (m_nAttackCounter >= ENEMY_BOSS_ATTACK_STOP_MAX_COUNT)
			{
				//0に戻す
				m_nAttackCounter = 0;
				//攻撃する
				m_pMotionEnemyBoss->SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_ATTACK_01, this);
				//攻撃したカウンターを増やす
				m_nCntAttack++;
				//攻撃した回数によって次の攻撃を何にするか決める
				if (m_nCntAttack < ENEMY_BOSS_ATTACK_RUSH_COUNTER)
				{
					m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::NORMAL;
				}
				else if (m_nCntAttack == ENEMY_BOSS_ATTACK_RUSH_COUNTER)
				{
					m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::RUSH;
				}
			}
			else
			{
				//目的の方向を設定する
				m_fObjectiveRot = fRot;
				//回転をさせる
				m_bRotate = true;
			}
			break;
		case CEnemyBoss::ENEMY_BOSS_ATTACK_PATTERN::RUSH:
			//カウンターを加算
			m_nAttackCounter++;
			//規定値になったら
			if (m_nAttackCounter == ENEMY_BOSS_ATTACK_RUSH_COUNT)
			{
				//移動量を設定
				m_move.z = -cosf(fRot) * ENEMY_BOSS_RUSH_MOVE_SPEED;
				m_move.x = -sinf(fRot) * ENEMY_BOSS_RUSH_MOVE_SPEED;
				//突進攻撃する
				m_pMotionEnemyBoss->SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_RUSH, this);
				//攻撃したカウンターを増やす
				m_nCntAttack++;
			}
			else if (m_nAttackCounter > ENEMY_BOSS_ATTACK_RUSH_COUNT && m_nAttackCounter <= ENEMY_BOSS_ATTACK_RUSH_COUNT_MAX)
			{
				//5フレームに1回攻撃の当たり判定をつける
				if (m_nAttackCounter % ENEMY_BOSS_ATTACK_RUSH_COLL == 0)
				{
					//攻撃の当たり判定が無効なら
					if (m_bAttackColl == false)
					{
						//攻撃の当たり判定を有効にする
						m_bAttackColl = true;
					}
				}
			}
			else if (m_nAttackCounter > ENEMY_BOSS_ATTACK_RUSH_COUNT_MAX)
			{//規定値より大きくなったら

				//0に戻す
				m_nAttackCounter = 0;
				//次の攻撃を魔法攻撃にする
				m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::MAGIC;
				//モーションをニュートラルにする
				m_pMotionEnemyBoss->SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL, this);
				//攻撃の当たり判定が無効なら
				if (m_bAttackColl == false)
				{
					//攻撃の当たり判定を有効にする
					m_bAttackColl = true;
				}
			}
			else if (m_nAttackCounter < ENEMY_BOSS_ATTACK_RUSH_COUNT)
			{
				//目的の方向を設定する
				m_fObjectiveRot = fRot;
				//回転をさせる
				m_bRotate = true;
			}
			break;
		case CEnemyBoss::ENEMY_BOSS_ATTACK_PATTERN::MAGIC:
			//移動量を0にする
			m_move.x = 0.0f;
			m_move.z = 0.0f;

			//目的の方向を設定する
			m_fObjectiveRot = fRot;
			//回転をさせる
			m_bRotate = true;

			//カウンターを加算
			m_nAttackCounter++;
			//規定値になったら
			if (m_nAttackCounter == ENEMY_BOSS_ATTACK_MAGIC_COUNT)
			{
				//魔法攻撃する
				m_pMotionEnemyBoss->SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_MAGIC, this);
			}
			else if (m_nAttackCounter > ENEMY_BOSS_ATTACK_MAGIC_COUNT)
			{//規定値よりも大きくなったら
				//20フレームに1回魔法を出す
				if (m_nAttackCounter % ENEMY_BOSS_ATTACK_MAGIC_INTERVAL == 0)
				{
					//弾を出して攻撃する
					CBulletEnemy::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 200.0f, m_pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
				}

				//攻撃が終わったら
				if (m_pMotionEnemyBoss->GetMotion() == CMotionRoad::MOTION_ENEMY_BOSS_TYPE::MOTION_ENEMY_BOSS_TYPE_MAGIC &&
					m_pMotionEnemyBoss->GetKey() >= m_pMotionEnemyBoss->GetKeyMax() - 2 &&
					m_pMotionEnemyBoss->GetFrame() >= m_pMotionEnemyBoss->GetFrameMax() && m_pMotionEnemyBoss->GetConnect() == false)
				{
					//通常攻撃に戻す
					m_attackPattern = ENEMY_BOSS_ATTACK_PATTERN::NORMAL;
					//攻撃したカウンターを0にする
					m_nCntAttack = 0;
					//0に戻す
					m_nAttackCounter = 0;
					//停止状態にする
					m_movePattern = ENEMY_MOVE_PATTERN::STOP;
				}
			}
			break;
		default:
			break;
		}
		break;
	case ENEMY_MOVE_PATTERN::DAMAGE:			//被ダメージ
		
		break;
	default:
		break;
	}
}

//================================================
//プレイヤーへの攻撃の当たり判定			
//================================================
void CEnemyBoss::ToPlayerAttackCollision(void)
{
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
			//プレイヤーにキャスト
			CPlayer *pPlayer = nullptr;
			pPlayer = (CPlayer*)pObject;

			//モーションが攻撃且つキーが2個目以降の時または突進攻撃の時
			if ((m_pMotionEnemyBoss->GetMotion() == CMotionRoad::MOTION_ENEMY_BOSS_TYPE::MOTION_ENEMY_BOSS_TYPE_ATTACK_01 &&
				m_pMotionEnemyBoss->GetKey() >= 2) ||
				m_pMotionEnemyBoss->GetMotion() == CMotionRoad::MOTION_ENEMY_BOSS_TYPE::MOTION_ENEMY_BOSS_TYPE_RUSH)
			{
				//攻撃の当たり判定があるなら
				if (m_bAttackColl == true)
				{
					//オブジェクトの位置を取得
					D3DXVECTOR3 posObj = pPlayer->GetPos();
					posObj.y += pPlayer->GetSize().y;
					//オブジェクトのサイズを取得
					D3DXVECTOR3 size = pPlayer->GetSize();

					for (int nCntMtx = 0; nCntMtx < ENEMY_BOSS_MAX_ATTACK_COLLISION; nCntMtx++)
					{
						//自身の手から対象のオブジェクトまでの距離を求める
						float fRadius = sqrtf((posObj.x - m_aAttackCollMtx[nCntMtx]._41) * (posObj.x - m_aAttackCollMtx[nCntMtx]._41) +
							                  (posObj.y - m_aAttackCollMtx[nCntMtx]._42) * (posObj.y - m_aAttackCollMtx[nCntMtx]._42) +
							                  (posObj.z - m_aAttackCollMtx[nCntMtx]._43) * (posObj.z - m_aAttackCollMtx[nCntMtx]._43));


						//求めた距離がプレイヤーの半径と対象のオブジェクトの半径を足した数値以下だったら
						if (fRadius <= ENEMY_BOSS_ATTACK_COLLISION_RADIUS + size.x / 2.0f)
						{
							//太型敵の攻撃との当たり判定
							if (pPlayer->GetState() == CPlayer::PLAYER_STATE::NORMAL)
							{
								//ガードしていなかったら
								if (pPlayer->GetGuard() == false)
								{
									//状態を無敵にする
									pPlayer->SetState(CPlayer::PLAYER_STATE::DAMAGE);
									//ライフを減らす
									CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-ENEMY_BOSS_ATTACK_DAMAGE);
									//ライフが0になったら
									if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
									{
										//ゲームオーバーにする
										CManager::GetInstance()->GetPlayData()->SetGameOver(true);
									}
								}
								else
								{//ガードしていたら
									 //プレイヤーの位置と向き取得
									D3DXVECTOR3 posPlayer = pPlayer->GetPos();
									D3DXVECTOR3 rotPlayer = pPlayer->GetRot();
									float fRotPlayerY = rotPlayer.y;

									//プレイヤーとの角度を求める
									float fRot = atan2((posPlayer.x - m_pos.x), (posPlayer.z - m_pos.z));

									//プレイヤーの向きだけがマイナスの時D3DXPI*2を足す
									if (fRotPlayerY < 0.0f && fRot > 0.0f)
									{
										fRotPlayerY += D3DX_PI * 2.0f;
									}
									else if (rotPlayer.y > 0.0f && fRot < 0.0f)
									{//プレイヤーとの角度だけがマイナスの時D3DXPI*2を足す
										fRot += D3DX_PI * 2.0f;
									}

									float fDiffer = abs(fRotPlayerY - fRot);
									//向きの差が90度以上あったら
									if (fDiffer > D3DX_PI / 2.0f)
									{
										//状態を無敵にする
										pPlayer->SetState(CPlayer::PLAYER_STATE::DAMAGE);
										//ライフを減らす
										CManager::GetInstance()->GetPlayData()->GetHpGauge()->AddGauge(-ENEMY_BOSS_ATTACK_DAMAGE);
										//ライフが0になったら
										if (CManager::GetInstance()->GetPlayData()->GetHpGauge()->GetGauge() <= 0)
										{
											//ゲームオーバーにする
											CManager::GetInstance()->GetPlayData()->SetGameOver(true);
										}
									}
									else
									{
										//サウンド取得処理
										CSound *pSound;
										pSound = CManager::GetInstance()->GetSound();

										//SE再生
										pSound->Play(CSound::SOUND_LABEL_GUARD_SE);
										//サウンドの音量調整
										pSound->ControllVoice(CSound::SOUND_LABEL_GUARD_SE, 1.3f);

										//ガードエフェクトの生成
										CGuardEffect::Create(D3DXVECTOR3(posPlayer.x + sinf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS,
											posPlayer.y + GUARD_EFFECT_POS_Y,
											posPlayer.z + cosf(rotPlayer.y - D3DX_PI) * GUARD_EFFECT_POS),
											D3DXVECTOR3(GUARD_EFFECT_SIZE, GUARD_EFFECT_SIZE, 0.0f), rotPlayer);

										//SPゲージを増やす
										CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_BOSS_GUARD_ADD_SP);
									}
								}
							}
							//攻撃の当たり判定が有効なら
							if (m_bAttackColl == true)
							{
								//攻撃の当たり判定を消す
								m_bAttackColl = false;
							}
						}
					}
				}
			}

			//攻撃が終わったら
			if (m_pMotionEnemyBoss->GetMotion() == CMotionRoad::MOTION_ENEMY_BOSS_TYPE::MOTION_ENEMY_BOSS_TYPE_ATTACK_01 &&
			    m_pMotionEnemyBoss->GetKey() >= m_pMotionEnemyBoss->GetKeyMax() - 2 &&
			    m_pMotionEnemyBoss->GetFrame() >= m_pMotionEnemyBoss->GetFrameMax())
			{
				//攻撃の当たり判定が無効なら
				if (m_bAttackColl == false)
				{
					//攻撃の当たり判定を有効にする
					m_bAttackColl = true;
				}
			}
		}
		//次のオブジェクトに進める
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
}

//================================================
//斬撃の当たり判定
//================================================
bool CEnemyBoss::CollisionSlash(void)
{
	//剣の軌跡との当たり判定
	if (CMeshTrajectory::CollisionSphere(this, m_size.x / 3.0f) == true && m_bDamage == false)
	{//ダメージを受けていなかったら
		//ダメージ状態にする
		m_bDamage = true;

		//カメラのポインタ配列1番目のアドレス取得
		CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
		//cameraの取得
		CCamera* pCamera = &**pCameraAddress;
		//カメラの向き取得
		D3DXVECTOR3 rotCamera = pCamera->GetRotV();

		//ヒットエフェクトを出す
		CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BOSS_HIT_EFFECT_POS_Y,
			              m_pos.z + cosf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ),
			              D3DXVECTOR3(ENEMY_BOSS_HIT_EFFECT_SIZE, ENEMY_BOSS_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			              CEffect3D::EFFECT3D_TYPE::HIT);

		//火の粉エフェクトの生成
		CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BOSS_HIT_EFFECT_POS_Y,
			                       m_pos.z + cosf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ),
			           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
			           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
			           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

		//SPゲージを増やす
		CManager::GetInstance()->GetPlayData()->GetSpGauge()->AddGauge(ENEMY_BOSS_HIT_ADD_SP);
		//MPゲージを増やす
		CManager::GetInstance()->GetPlayData()->GetMpGauge()->AddGauge(ENEMY_BOSS_HIT_ADD_MP);

		//ライフを減らす
		m_nLife -= ENEMY_BOSS_HIT_DAMAGE;
		//ライフが0になったら
		if (m_nLife <= 0)
		{
			//スコアを増やす
			CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BOSS_UNINIT_SCORE);

			//ゲームクリアにする
			CManager::GetInstance()->GetPlayData()->SetGameClear(true);

			//消す
			Uninit();
			return true;
		}
	}
	return false;
}

//================================================
//雷魔法の当たり判定
//================================================
bool CEnemyBoss::CollisionMagicThunder(void)
{
	if (CMagicThunder::Collision(this) == true)
	{
		//ダメージ状態でないなら
		if (m_bDamage == false)
		{
			//ダメージ状態にする
			m_bDamage = true;

			//HPを減らす
			m_nLife -= MAGIC_THUNDER_EFFECT_ENEMY_BOSS_DAMAGE;

			//カメラのポインタ配列1番目のアドレス取得
			CCamera** pCameraAddress = CManager::GetInstance()->GetCamera();
			//cameraの取得
			CCamera* pCamera = &**pCameraAddress;
			//カメラの向き取得
			D3DXVECTOR3 rotCamera = pCamera->GetRotV();

			//ヒットエフェクトを出す
			CEffect3D::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BOSS_HIT_EFFECT_POS_Y,
				              m_pos.z + cosf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ),
				              D3DXVECTOR3(ENEMY_BOSS_HIT_EFFECT_SIZE, ENEMY_BOSS_HIT_EFFECT_SIZE, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
				              CEffect3D::EFFECT3D_TYPE::HIT);

			//火の粉エフェクトの生成
			CSpark::Create(D3DXVECTOR3(m_pos.x + sinf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ, m_pos.y + ENEMY_BOSS_HIT_EFFECT_POS_Y,
				                       m_pos.z + cosf(rotCamera.y) * ENEMY_BOSS_HIT_EFFECT_POS_XZ),
				           D3DXVECTOR3(ENEMY_SPARK_SIZE, ENEMY_SPARK_SIZE, 0.0f), ENEMY_SPARK_EFFECT_NUM,
				           ENEMY_SPARK_EFFECT_COLOR, ENEMY_SPARK_MOVE_MIN, ENEMY_SPARK_MOVE_MAX, ENEMY_SPARK_GRAVITY,
				           ENEMY_SPARK_COL_A_MIN, ENEMY_SPARK_COL_A_MAX, ENEMY_SPARK_SUBTRACTION_MOVE);

			//HPが0以下になったら
			if (m_nLife <= 0)
			{
				//スコアを増やす
				CManager::GetInstance()->GetPlayData()->GetScorePoint()->AddScore(ENEMY_BOSS_UNINIT_SCORE);

				//ゲームクリアにする
				CManager::GetInstance()->GetPlayData()->SetGameClear(true);

				//消す
				Uninit();
				return true;
			}
		}
	}
	return false;
}

//================================================
//ダメージを受けているときの処理
//================================================
void CEnemyBoss::Damage(void)
{
	//ダメージを受けているなら
	if (m_bDamage == true)
	{
		//カウンターを加算
		m_nDamageCounter++;

		//規定値よりもカウンターが大きくなったら
		if (m_nDamageCounter >= ENEMY_DAMAGE_MAX_COUNT)
		{
			//カウンターを戻す
			m_nDamageCounter = 0;
			//ダメージを受けていない状態にする
			m_bDamage = false;
		}
	}
}
