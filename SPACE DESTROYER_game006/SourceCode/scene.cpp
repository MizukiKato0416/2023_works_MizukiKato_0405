//================================================
//シーン処理
//Authore:加藤瑞葵
//================================================
#include "scene.h"
#include "scene2D.h"
#include "game01.h"
#include "tutorial.h"
#include "manager.h"

//================================================
//静的メンバ変数宣言
//================================================
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//================================================
//デフォルトコンストラクタ
//================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nPriority = nPriority;
			m_objType = OBJTYPE_NONE;
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_nID = nCntScene;
			m_nNumAll++;
			break;
		}
	}
}

//================================================
//デストラクタ
//================================================
CScene::~CScene()
{

}

//================================================
//終了処理
//================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (nCntPriority != PRIORITY_FADE)
				{
					m_apScene[nCntPriority][nCntScene]->Uninit();
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}

//================================================
//更新処理
//================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (CManager::GetMode() == CManager::MODE_GAME01)
				{
					//ポーズを取得
					if (CGame01::GetPause() == false)
					{//ポーズ中ではないとき
						m_apScene[nCntPriority][nCntScene]->Update();
					}
					else
					{//ポーズ中の時
						if (nCntPriority == PRIORITY_NONE || nCntPriority == PRIORITY_UI || nCntPriority == PRIORITY_FADE)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
					}
				}
				else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
				{
					//ポーズを取得
					if (CManager::GetTutorial()->GetPause() == false)
					{//ポーズ中ではないとき
						if (CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_CONTROL ||
							CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_SHOOT ||
							CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
						else
						{
							if (nCntPriority != PRIORITY_PLAYER)
							{
								m_apScene[nCntPriority][nCntScene]->Update();
							}
						}
					}
					else
					{//ポーズ中の時
						if (nCntPriority == PRIORITY_NONE || nCntPriority == PRIORITY_UI || nCntPriority == PRIORITY_FADE)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
					}
				}
				else
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//================================================
//終了処理
//================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//インスタンスの破棄
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//================================================
//オブジェクトの種類の設定処理
//================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//================================================
//オブジェクトの種類の設定処理
//================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//================================================
//オブジェクト取得処理
//================================================
CScene *CScene::GetScene(int nScene, int nPriority)
{
	return m_apScene[nPriority][nScene];
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

//================================================
//位置設定処理
//================================================
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//================================================
//サイズ取得処理
//================================================
D3DXVECTOR3 CScene::GetSize(void)
{
	return m_size;
}

//================================================
//サイズ設定処理
//================================================
void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}