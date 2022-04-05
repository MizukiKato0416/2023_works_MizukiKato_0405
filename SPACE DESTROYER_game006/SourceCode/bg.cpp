//================================================
//背景処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "bg.h"
#include "texture.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_BG_POLYGON] = {};

//================================================
//デフォルトコンストラクタ
//================================================
CBg::CBg(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		m_apScene2D[nCntPolygon] = NULL;
		m_fPosTexV[nCntPolygon] = 0.0f;
	}
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CBg::~CBg()
{

}

//================================================
//初期化処理
//================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		//ポリゴンの生成
		m_apScene2D[nCntPolygon] = new CScene2D(PRIORITY_BG_0);
		m_apScene2D[nCntPolygon]->Init(pos, size);

		//テクスチャの割り当て
		m_apScene2D[nCntPolygon]->BindTexture(m_pTexture[nCntPolygon]);

		//テクスチャV座標
		m_fPosTexV[nCntPolygon] = 0.0f;
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CBg::Uninit(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		if (m_apScene2D[nCntPolygon] != NULL)
		{
			m_apScene2D[nCntPolygon]->Uninit();
			m_apScene2D[nCntPolygon] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CBg::Update(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		//背景によって動く速さを変える
		if (nCntPolygon == 0)
		{
			m_fPosTexV[nCntPolygon] -= 0.0005f;
		}
		else if (nCntPolygon == 1)
		{
			m_fPosTexV[nCntPolygon] -= 0.001f;
		}
		else if (nCntPolygon == 2)
		{
			m_fPosTexV[nCntPolygon] -= 0.002f;
		}

		if (m_fPosTexV[nCntPolygon] < -1.0f)
		{
			m_fPosTexV[nCntPolygon] += 0.0f;
		}

		m_apScene2D[nCntPolygon]->SetTex(0.0f, m_fPosTexV[nCntPolygon]);
	}
}

//================================================
//描画処理
//================================================
void CBg::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CBg *pBg = NULL;
	if (pBg == NULL)
	{
		pBg = new CBg;
		if (pBg != NULL)
		{
			//テクスチャ割り当て
			m_pTexture[0] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_00);
			m_pTexture[1] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_01);
			m_pTexture[2] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_02);
			pBg->Init(pos, size);
		}
	}
	return pBg;
}