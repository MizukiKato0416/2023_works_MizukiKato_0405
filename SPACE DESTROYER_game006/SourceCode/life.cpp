//================================================
//ライフ処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "polygon.h"
#include "manager.h"
#include "life.h"
#include "texture.h"
#include "game01.h"
#include "player.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CLife::CLife(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_LIFE_POLYGON; nCntPolygon++)
	{
		m_apPolygon[nCntPolygon] = NULL;
	}

	m_nLife = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CLife::~CLife()
{

}

//================================================
//初期化処理
//================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nLife = MAX_PLAYER_INIT_LIFE;
	m_pos = pos;

	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		m_apPolygon[nCntPolygon] = CPolygon::Create(D3DXVECTOR3(pos.x - (LIFE_POLYGON_WIDTH * m_nLife / 2) + (LIFE_POLYGON_WIDTH * nCntPolygon) + (LIFE_POLYGON_WIDTH / 2.0f), pos.y, 0.0f),
												D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CLife::Uninit(void)
{
	//ナンバーの破棄
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Uninit();
			delete m_apPolygon[nCntPolygon];
			m_apPolygon[nCntPolygon] = NULL;
		}
	}

	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CLife::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CLife::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
}

//================================================
//生成処理
//================================================
CLife* CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CLife *pLife = NULL;
	if (pLife == NULL)
	{
		pLife = new CLife;
		if (pLife != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PLAYER_LIFE);
			pLife->Init(pos, size);
			CGame01::GetPolygon()->BindTexture(m_pTexture);
		}
	}
	return pLife;
}

//================================================
//ライフ取得処理
//================================================
int CLife::GetLife(void)
{
	return m_nLife;
}

//================================================
//ライフ設定処理
//================================================
void CLife::SetLife(int nLife)
{
	m_nLife = nLife;
}

//================================================
//ライフ加算処理
//================================================
void CLife::AddLife(int nValue)
{
	//ライフの加算
	m_nLife += nValue;

	//加算した分のライフポリゴン生成
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] == NULL)
		{
			m_apPolygon[nCntPolygon] = CPolygon::Create(D3DXVECTOR3(m_pos.x - (LIFE_POLYGON_WIDTH * START_LIFE_POLYGON / 2) + (LIFE_POLYGON_WIDTH * nCntPolygon) + (LIFE_POLYGON_WIDTH / 2.0f), m_pos.y, 0.0f),
														D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));
		}
	}
}

//================================================
//ライフ減算処理
//================================================
void CLife::SubtractLife(int nValue)
{
	//減算した分のライフポリゴン破棄
	if (m_nLife > 0)
	{
		for (int nCntPolygon = m_nLife - 1; nCntPolygon > m_nLife - 1 - nValue; nCntPolygon--)
		{
			m_apPolygon[nCntPolygon]->Uninit();
			delete m_apPolygon[nCntPolygon];
			m_apPolygon[nCntPolygon] = NULL;
		}
	}
	else
	{
		m_nLife = 0;
	}

	//ライフの減算
	m_nLife -= nValue;
}