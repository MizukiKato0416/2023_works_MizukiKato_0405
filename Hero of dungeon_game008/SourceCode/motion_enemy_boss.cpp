//================================================
//ボスのモーション処理
//Author:KatoMizuki
//================================================
#include "motion_enemy_boss.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMotionEnemyBoss::CMotionEnemyBoss()
{
	//モーションの数分回す
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BOSS_TYPE_MAX; nCntMotion++)
	{
		//モーション情報の変数を動的に確保
		m_aInfo.push_back({});
		//初期化
		m_aInfo[nCntMotion].bLoop = false;
		m_aInfo[nCntMotion].nNumKey = 0;
		//キー最大数分回す
		for (int nCntKey = 0; nCntKey < MOTION_MAX_KEY_INFO; nCntKey++)
		{
			//初期化
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = 0;
			//モデルの数分回す
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
			{
				//モデルのキー要素の変数を動的に確保
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey.push_back({});
				//初期化
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//動的確保して初期化
				m_posOld.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_rotOld.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
	}

	//初期化
	m_type = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_typeNext = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_typeOld = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 0.0f;
	m_nKey = 0;
	m_bConnect = false;
}

//================================================
//デストラクタ
//================================================
CMotionEnemyBoss::~CMotionEnemyBoss()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMotionEnemyBoss::Init(CEnemyBoss *pEnemyBoss)
{
	//モーションの数分回す
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BOSS_TYPE_MAX; nCntMotion++)
	{
		//キー数取得
		m_aInfo[nCntMotion].nNumKey = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BOSS, nCntMotion).nNumKey;
		//ループ情報取得
		m_aInfo[nCntMotion].bLoop = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BOSS, nCntMotion).bLoop;
		
		//キーの数分回す
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			//フレーム数の取得
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BOSS, nCntMotion).aKeyInfo[nCntKey].nFrame;
			
			//モデルの数分回す
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
			{
				//位置と回転の取得
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BOSS, nCntMotion).aKeyInfo[nCntKey].aKey[nCntModel].pos;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BOSS, nCntMotion).aKeyInfo[nCntKey].aKey[nCntModel].rot;
			}
		}
	}

	//親子関係による位置ずれの修正
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BOSS_TYPE_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
			{
				//モデルの位置と向き取得
				D3DXVECTOR3 pos = pEnemyBoss->GetModelPos(nCntModel);
				D3DXVECTOR3 rot = pEnemyBoss->GetModelRot(nCntModel);

				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x = pos.x + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y = pos.y + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z = pos.z + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x = rot.x + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y = rot.y + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z = rot.z + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z;
			}
		}
	}

	//変数初期化
	m_type = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_typeNext = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_typeOld = CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 0.0f;
	m_nKey = 0;
	m_bConnect = false;

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
	{
		//モデルの位置と向きに反映
		pEnemyBoss->SetModelPos(nCntModel, m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos);
		pEnemyBoss->SetModelRot(nCntModel, m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot);
		m_posOld[nCntModel] = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos;
		m_rotOld[nCntModel] = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot;
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMotionEnemyBoss::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMotionEnemyBoss::Update(CEnemyBoss *pEnemyBoss)
{
	D3DXVECTOR3 posAsk[MAX_ENEMY_BOSS_MODEL];		//求めたい値
	D3DXVECTOR3 rotAsk[MAX_ENEMY_BOSS_MODEL];		//求めたい値
	D3DXVECTOR3 posDiffer[MAX_ENEMY_BOSS_MODEL];	//差分
	D3DXVECTOR3 rotDiffer[MAX_ENEMY_BOSS_MODEL];	//差分

	//次のキー
	int nKeyNext = 0;

	if (m_nKey >= m_aInfo[m_type].nNumKey - 1)	//現在のキーが最大値以上だったら
	{
		nKeyNext = 0;
	}
	else			//現在のキーが最大値より小さかったら
	{
		nKeyNext = m_nKey + 1;
	}

	//モーションをつなげるとき
	if (m_bConnect == true)	
	{
		//次のキーを0にする
		nKeyNext = 0;
	}
	else
	{
		m_fConnectMaxFrame = (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFrame;
	}
	

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
	{
		if (m_bConnect == true)		//つなげるとき
		{
			//現在のキーと次のキーの位置の差分を求める
			posDiffer[nCntModel].x = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.x - m_posOld[nCntModel].x;
			posDiffer[nCntModel].y = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.y - m_posOld[nCntModel].y;
			posDiffer[nCntModel].z = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.z - m_posOld[nCntModel].z;

			//現在のキーと次のキーの回転の差分を求める
			rotDiffer[nCntModel].x = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.x - m_rotOld[nCntModel].x;
			rotDiffer[nCntModel].y = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.y - m_rotOld[nCntModel].y;
			rotDiffer[nCntModel].z = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.z - m_rotOld[nCntModel].z;

			if (rotDiffer[nCntModel].x <= -D3DX_PI)
			{
				rotDiffer[nCntModel].x += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].x > D3DX_PI)
			{
				rotDiffer[nCntModel].x -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].z <= -D3DX_PI)
			{
				rotDiffer[nCntModel].z += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].z > D3DX_PI)
			{
				rotDiffer[nCntModel].z -= D3DX_PI * 2.0f;
			}

			//現在のキーから次のキーに動かした先の位置を求める
			posAsk[nCntModel].x = m_posOld[nCntModel].x + posDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].y = m_posOld[nCntModel].y + posDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].z = m_posOld[nCntModel].z + posDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);

			//現在のキーから次のキーに動かした先の向きを求める
			rotAsk[nCntModel].x = m_rotOld[nCntModel].x + rotDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].y = m_rotOld[nCntModel].y + rotDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].z = m_rotOld[nCntModel].z + rotDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);
		}
		else	//つなげないとき
		{
			//現在のキーと次のキーの位置の差分を求める
			posDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.x
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x;
			posDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.y
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y;
			posDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.z
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z;

			//現在のキーと次のキーの回転の差分を求める
			rotDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.x
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x;
			rotDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.y
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y;
			rotDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.z
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z;

			if (rotDiffer[nCntModel].x <= -D3DX_PI)
			{
				rotDiffer[nCntModel].x += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].x > D3DX_PI)
			{
				rotDiffer[nCntModel].x -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].z <= -D3DX_PI)
			{
				rotDiffer[nCntModel].z += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].z > D3DX_PI)
			{
				rotDiffer[nCntModel].z -= D3DX_PI * 2.0f;
			}

			//現在のキーから次のキーに動かした先の位置を求める
			posAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x
				+ posDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y
				+ posDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z
				+ posDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);

			//現在のキーから次のキーに動かした先の向きを求める
			rotAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x
				+ rotDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y
				+ rotDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z
				+ rotDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);
		}

		//モデルの位置と向きに反映
		pEnemyBoss->SetModelPos(nCntModel, posAsk[nCntModel]);
		pEnemyBoss->SetModelRot(nCntModel, rotAsk[nCntModel]);
	}

	//カウンターを加算
	m_fCounter += 1.0f;

	if (m_bConnect == false)
	{
		//フレーム数最大値を超えたら
		if (m_fCounter > m_aInfo[m_type].aKeyInfo[m_nKey].nFrame)
		{
			m_nKey++;
			if (m_nKey < m_aInfo[m_type].nNumKey - 1)//キーの最大数-1
			{
				m_fCounter = 0.0f;
			}
			else if (m_nKey >= m_aInfo[m_type].nNumKey - 1)
			{
				if (m_aInfo[m_type].bLoop == 0)	//ループしないとき
				{
					//次のモーションをニュートラルモーションにする
					SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE_NEUTRAL, pEnemyBoss);
				}
				else	//ループするとき
				{
					//次のモーションを同じモーションにする
					if (m_nKey > m_aInfo[m_type].nNumKey - 1)
					{
						m_nKey = 0;
					}
				}
				
				m_fCounter = 0.0f;
			}
		}
	}
	else
	{
		//フレーム数最大値を超えたら
		if (m_fCounter > m_fConnectMaxFrame)
		{
			m_bConnect = false;
			m_fCounter = 0.0f;
			m_nKey = 0;
			//現在のモーションの種類を次のモーションの種類にする
			m_typeOld = m_type;
		}
	}
}

//================================================
//生成処理
//================================================
CMotionEnemyBoss *CMotionEnemyBoss::Create(CEnemyBoss *pEnemyBoss)
{
	//インスタンスの生成
	CMotionEnemyBoss *pMotionEnemyBoss = nullptr;
	if (pMotionEnemyBoss == nullptr)
	{
		pMotionEnemyBoss = new CMotionEnemyBoss;
		if (pMotionEnemyBoss != nullptr)
		{
			pMotionEnemyBoss->Init(pEnemyBoss);
		}
	}
	return pMotionEnemyBoss;
}

//================================================
//モーション設定処理
//================================================
void CMotionEnemyBoss::SetMotion(CMotionRoad::MOTION_ENEMY_BOSS_TYPE type, CEnemyBoss *pEnemyBoss)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
	{
		//モデルの位置と向きを取得
		D3DXVECTOR3 pos = pEnemyBoss->GetModelPos(nCntModel);
		D3DXVECTOR3 rot = pEnemyBoss->GetModelRot(nCntModel);

		//現在のモデルの位置と向きを保存
		m_posOld[nCntModel] = pos;
		m_rotOld[nCntModel] = rot;
	}
	m_typeOld = m_type;
	m_type = type;
	m_typeNext = type;
	m_bConnect = true;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 10;
}

//================================================
//モーション設定処理
//================================================
void CMotionEnemyBoss::SetMotion(int nType, CEnemyBoss *pEnemyBoss)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BOSS_MODEL; nCntModel++)
	{
		//モデルの位置と向きを取得
		D3DXVECTOR3 pos = pEnemyBoss->GetModelPos(nCntModel);
		D3DXVECTOR3 rot = pEnemyBoss->GetModelRot(nCntModel);

		//現在のモデルの位置と向きを保存
		m_posOld[nCntModel] = pos;
		m_rotOld[nCntModel] = rot;
	}

	m_typeOld = m_type;
	m_type = (CMotionRoad::MOTION_ENEMY_BOSS_TYPE)nType;
	m_typeNext = (CMotionRoad::MOTION_ENEMY_BOSS_TYPE)nType;
	m_bConnect = true;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 10;
}

//================================================
//モーション取得処理
//================================================
CMotionRoad::MOTION_ENEMY_BOSS_TYPE CMotionEnemyBoss::GetMotion(void)
{
	return m_type;
}

//================================================
//モーションをつなげている最中かどうか取得処理
//================================================
bool CMotionEnemyBoss::GetConnect(void)
{
	return m_bConnect;
}