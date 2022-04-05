//================================================
//プレイヤーのモーション処理
//Author:加藤瑞葵
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "motion_player.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CMotionPlayer::CMotionPlayer()
{
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		m_aInfo[nCntMotion].bLoop = false;
		m_aInfo[nCntMotion].nNumKey = 0;
		for (int nCntKey = 0; nCntKey < MOTION_PLAYER_MAX_KEY_INFO; nCntKey++)
		{
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = 0;
			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	m_type = MOTION_PLAYER_TYPE_NEUTRAL;
	m_typeNext = MOTION_PLAYER_TYPE_NEUTRAL;
	m_nNumKey = 0;
	m_nKeyOld = 0;
	m_fCounter = 0.0f;
	m_nKey = 0;
	m_bConnect = false;
}

//================================================
//デストラクタ
//================================================
CMotionPlayer::~CMotionPlayer()
{

}

//================================================
//初期化処理
//================================================
HRESULT CMotionPlayer::Init(CPlayer *pPlayer)
{
	//textファイル読み込み
	FILE *pfile = fopen("data/MOTION/motion_player.txt", "r");

	char cString[MOTION_PLAYER_MAX_STRING];

	//モーションの読み込み
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		//一行ずつ保存
		while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
		{
			//文字列を保存
			fscanf(pfile, "%s", cString);
			//文字列の中にMOTIONSETがあったら
			if (strncmp("MOTIONSET", cString, 10) == 0)
			{
				//ループ情報の取得
				//キー数の取得
				fscanf(pfile, "%s%*s%d%*s%*s%*s%*s", cString, &m_aInfo[nCntMotion].bLoop);
				fscanf(pfile, "%s%*s%d", cString, &m_aInfo[nCntMotion].nNumKey);
				break;
			}
		}

		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
			{
				//文字列を保存
				fscanf(pfile, "%s", cString);
				//文字列の中にFRAMEがあったら
				if (strncmp("FRAME", cString, 6) == 0)
				{
					//フレーム数の取得
					fscanf(pfile, "%s%d", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					break;
				}
			}

			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
				{
					//文字列を保存
					fscanf(pfile, "%s", cString);
					//文字列の中にPOSがあったら
					if (strncmp("POS", cString, 4) == 0)
					{
						//位置、回転情報の取得
						fscanf(pfile, "%s%f%f%f", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x, 
																&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y,
																&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z);
						fscanf(pfile, "%s%*s%f%f%f%*s", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x,
																	&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y,
																	&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z);
						break;
					}
				}
			}

			while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
			{
				//文字列を保存
				fscanf(pfile, "%s", cString);
				//文字列の中にEND_KEYSETがあったら
				if (strncmp("END_KEYSET", cString, 11) == 0)
				{
					break;
				}
			}
		}

		while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
		{
			//文字列を保存
			fscanf(pfile, "%s", cString);
			//文字列の中にEND_MOTIONSETがあったら
			if (strncmp("END_MOTIONSET", cString, 14) == 0)
			{
				break;
			}
		}
	}
	fclose(pfile);

	//親子関係による位置ずれの修正
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				//モデルの位置と向き取得
				D3DXVECTOR3 pos = pPlayer->GetModelPos(nCntModel);
				D3DXVECTOR3 rot = pPlayer->GetModelRot(nCntModel);

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
	m_type = MOTION_PLAYER_TYPE_NEUTRAL;
	m_typeNext = MOTION_PLAYER_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_nKey = 0;
	m_bConnect = false;

	return S_OK;
}

//================================================
//終了処理
//================================================
void CMotionPlayer::Uninit(void)
{
	
}

//================================================
//更新処理
//================================================
void CMotionPlayer::Update(CPlayer *pPlayer)
{
	D3DXVECTOR3 posAsk[MAX_PLAYER_MODEL];		//求めたい値
	D3DXVECTOR3 rotAsk[MAX_PLAYER_MODEL];		//求めたい値
	D3DXVECTOR3 posDiffer[MAX_PLAYER_MODEL];	//差分
	D3DXVECTOR3 rotDiffer[MAX_PLAYER_MODEL];	//差分

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

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		//フレーム数
		int nFrame = 0;
		if (m_bConnect == true)
		{
			nFrame = 10;
			if (m_aInfo[m_type].bLoop == 1)	//ループする時
			{
				nFrame = m_aInfo[m_type].aKeyInfo[0].nFrame;
			}
		}
		else
		{
			nFrame = m_aInfo[m_type].aKeyInfo[m_nKey].nFrame;
		}

		if (m_bConnect == true)		//つなげるとき
		{
			//モデルの位置と向きを取得
			D3DXVECTOR3 pos = pPlayer->GetModelPos(nCntModel);
			D3DXVECTOR3 rot = pPlayer->GetModelRot(nCntModel);

			//現在のキーと次のキーの位置の差分を求める
			posDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.x - pos.x;
			posDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.y - pos.y;
			posDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.z - pos.z;

			//現在のキーと次のキーの回転の差分を求める
			rotDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.x - rot.x;
			rotDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.y - rot.y;
			rotDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.z - rot.z;

			//現在のキーから次のキーに動かした先の位置を求める
			posAsk[nCntModel].x = pos.x + posDiffer[nCntModel].x * (m_fCounter / nFrame);
			posAsk[nCntModel].y = pos.y + posDiffer[nCntModel].y * (m_fCounter / nFrame);
			posAsk[nCntModel].z = pos.z + posDiffer[nCntModel].z * (m_fCounter / nFrame);

			//現在のキーから次のキーに動かした先の位置を求める
			rotAsk[nCntModel].x = rot.x + rotDiffer[nCntModel].x * (m_fCounter / nFrame);
			rotAsk[nCntModel].y = rot.y + rotDiffer[nCntModel].y * (m_fCounter / nFrame);
			rotAsk[nCntModel].z = rot.z + rotDiffer[nCntModel].z * (m_fCounter / nFrame);
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

			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}

			//現在のキーから次のキーに動かした先の位置を求める
			posAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x
				+ posDiffer[nCntModel].x * (m_fCounter / nFrame);
			posAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y
				+ posDiffer[nCntModel].y * (m_fCounter / nFrame);
			posAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z
				+ posDiffer[nCntModel].z * (m_fCounter / nFrame);

			//現在のキーから次のキーに動かした先の位置を求める
			rotAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x
				+ rotDiffer[nCntModel].x * (m_fCounter / nFrame);
			rotAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y
				+ rotDiffer[nCntModel].y * (m_fCounter / nFrame);
			rotAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z
				+ rotDiffer[nCntModel].z * (m_fCounter / nFrame);
		}

		//モデルの位置と向きに反映
		pPlayer->SetModelPos(nCntModel, posAsk[nCntModel]);
		pPlayer->SetModelRot(nCntModel, rotAsk[nCntModel]);
	}

	//カウンターを加算
	m_fCounter += 1.0f;

	if (m_bConnect == false)
	{
		//フレーム数最大値を超えたら
		if (m_fCounter >= m_aInfo[m_type].aKeyInfo[m_nKey].nFrame)
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
					if (m_type == MOTION_PLAYER_TYPE_DIVE)
					{
						//次のモーションをダイブ着地モーションにする
						SetMotion(MOTION_PLAYER_TYPE_DIVE_LAND);
					}
					else if (m_type == MOTION_PLAYER_TYPE_LAND)
					{
						D3DXVECTOR3 movePlayer = pPlayer->GetMove();
						if (movePlayer.x == 0.0f && movePlayer.z == 0.0f)
						{
							//次のモーションをニュートラルモーションにする
							SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
						}
						else
						{
							//次のモーションを移動モーションにする
							SetMotion(MOTION_PLAYER_TYPE_MOVE);
						}
					}
					else if (m_type == MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						D3DXVECTOR3 movePlayer = pPlayer->GetMove();
						if (movePlayer.x == 0.0f && movePlayer.z == 0.0f)
						{
							//次のモーションをニュートラルモーションにする
							SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
						}
						else
						{
							//次のモーションを移動モーションにする
							SetMotion(MOTION_PLAYER_TYPE_MOVE);
						}
					}
					else
					{
						//次のモーションをニュートラルモーションにする
						SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
					}
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
		float nMaxFrame = 10.0f;
		
		if (m_fCounter >= nMaxFrame)
		{
			m_bConnect = false;
			m_fCounter = 0.0f;
			m_nKey = 0;
			//現在のモーションの種類を次のモーションの種類にする
			m_type = m_typeNext;
		}
	}
}

//================================================
//生成処理
//================================================
CMotionPlayer *CMotionPlayer::Create(CPlayer *pPlayer)
{
	//インスタンスの生成
	CMotionPlayer *pMotionPlayer = NULL;
	if (pMotionPlayer == NULL)
	{
		pMotionPlayer = new CMotionPlayer;
		if (pMotionPlayer != NULL)
		{
			pMotionPlayer->Init(pPlayer);
		}
	}
	return pMotionPlayer;
}


//================================================
//モーション設定処理
//================================================
void CMotionPlayer::SetMotion(MOTION_PLAYER_TYPE type)
{
	m_typeNext = type;
	m_bConnect = true;
	m_fCounter = 0.0f;
}

//================================================
//モーション取得処理
//================================================
CMotionPlayer::MOTION_PLAYER_TYPE CMotionPlayer::GetMotion(void)
{
	return m_type;
}


//================================================
//モーションをつなげている最中かどうか取得処理
//================================================
bool CMotionPlayer::GetConnect(void)
{
	return m_bConnect;
}