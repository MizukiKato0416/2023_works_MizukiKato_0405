//================================================
//シーン処理
//Author:加藤瑞葵
//================================================
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "pause.h"

//================================================
//静的メンバ変数宣言
//================================================
CScene *CScene::m_pTop[PRIORITY_MAX] = {};
CScene *CScene::m_pCur[PRIORITY_MAX] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CScene::CScene(int nPriority)
{
	if (m_pTop[nPriority] == NULL && m_pCur[nPriority] == NULL)
	{
		//前のオブジェクト情報がなければTOPにする
		m_pTop[nPriority] = this;
		//つぎのオブジェクト情報がなければCURにする
		m_pCur[nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else
	{
		//前のオブジェクト情報があったら前のオブジェクト情報を入れてあげる
		m_pPrev = m_pCur[nPriority];
		//前のオブジェクトの次のオブジェクト情報をこのオブジェクトにする
		m_pCur[nPriority]->m_pNext = this;
		//一番最後にする
		m_pCur[nPriority] = this;
		m_pNext = NULL;
	}
	m_objType = OBJTYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_bDeath = false;
}

//================================================
//デストラクタ
//================================================
CScene::~CScene()
{
	int nPriority = m_nPriority;

	//次のオブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	pObject = this;


	//トップでもカレントでもない場合
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//自分の前のオブジェクトが持っている次のオブジェクト情報を自分の次のオブジェクト情報にする
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報を自分の前のオブジェクト情報にする
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//トップだったらトップを次のオブジェクトにずらす
		m_pTop[m_nPriority] = pObject->m_pNext;
		//自分の次のオブジェクトが持っている前のオブジェクト情報をNULLにする
		if (pObject->m_pNext != NULL)
		{
			pObject->m_pNext->m_pPrev = NULL;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//カレントだったらカレントを前のオブジェクトにずらす
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//自分の前のオブジェクトが持っている次のオブジェクト情報をNULLにする
		if (pObject->m_pPrev != NULL)
		{
			pObject->m_pPrev->m_pNext = NULL;
		}
	}
}

//================================================
//終了処理
//================================================
void CScene::ReleaseAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			//先頭のポインタを代入
			pObject = m_pTop[nCntPriority];
			while (pObject != NULL)
			{
				//現在のオブジェクトのポインタを保存
				pSaveObject = pObject;
				pObject->Uninit();
				if (pObject->m_bDeath == true)
				{
					//破棄
					delete pObject;
					pObject = NULL;
				}
				//次のオブジェクトのポインタにする
				pObject = pSaveObject->m_pNext;
			}
		}
	}
}

//================================================
//更新処理
//================================================
void CScene::UpdateAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			if (CPause::GetPause() == false)
			{
				pObject->Update();
			}
			else
			{
				if (nCntPriority == PRIORITY_FADE || nCntPriority == PRIORITY_PAUSE)
				{
					pObject->Update();
				}
			}
			pObject = pObject->m_pNext;
		}
	}


	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject;
			//死亡フラグチェック
			if (pObject->m_bDeath == true)
			{
				//破棄
				delete pObject;
				pObject = NULL;
			}
			//次のオブジェクトのポインタにする
			pObject = pSaveObject->m_pNext;
		}
	}
}

//================================================
//描画処理
//================================================
void CScene::DrawAll(void)
{
	//次のオブジェクト情報を入れるポインタ
	CScene *pObject = NULL;
	//オブジェクト情報を保存するポインタ変数
	CScene *pSaveObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//先頭のポインタを代入
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			//現在のオブジェクトのポインタを保存
			pSaveObject = pObject;
			pObject->Draw();
			pObject = pSaveObject->m_pNext;
		}
	}
}

//================================================
//単体を破棄する処理
//================================================
void CScene::Release(void)
{
	m_bDeath = true;	
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
//引数のオブジェクトの次のオブジェクト情報取得処理
//================================================
CScene *CScene::GetObjNext(CScene *pObject)
{
	return pObject->m_pNext;
}

//================================================
//オブジェクト取得処理
//================================================
CScene *CScene::GetTopObj(int nPriority)
{
	return m_pTop[nPriority];
}

//================================================
//位置取得処理
//================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

//================================================
//1フレーム前の位置設定処理
//================================================
void CScene::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//================================================
//1フレーム前の位置取得処理
//================================================
D3DXVECTOR3 CScene::GetPosOld(void)
{
	return m_posOld;
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