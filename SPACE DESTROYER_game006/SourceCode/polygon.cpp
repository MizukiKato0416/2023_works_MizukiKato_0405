//================================================
//ナンバー処理
//Authore:加藤瑞葵
//================================================
#include "renderer.h"
#include "polygon.h"
#include "manager.h"
#include "scene.h"

//================================================
//静的メンバ変数宣言
//================================================
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;

//================================================
//デフォルトコンストラクタ
//================================================
CPolygon::CPolygon()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//オーバーロードされたコンストラクタ
//================================================


//================================================
//デストラクタ
//================================================
CPolygon::~CPolygon()
{

}

//================================================
//初期化処理
//================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//変数初期化
	m_pos = pos;
	m_size = size;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D_POLYGON) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D_POLYGON,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D_POLYGON *pVtx;
	//頂点バッファをロックし、頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//終了処理
//================================================
void CPolygon::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//================================================
//更新処理
//================================================
void CPolygon::Update(void)
{
	
}

//================================================
//描画処理
//================================================
void CPolygon::Draw(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D_POLYGON));
	pDevice->SetFVF(FVF_VERTEX_2D_POLYGON);			//頂点フォーマットの設定

	pDevice->SetTexture(0, m_pTexture);	//テクスチャの設定

												//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,					//描画を開始する頂点のインデックス
		2);					//描画するプリミティブ数
}

//================================================
//生成処理
//================================================
CPolygon* CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//インスタンスの生成
	CPolygon *pPolygon = NULL;
	if (pPolygon == NULL)
	{
		pPolygon = new CPolygon;
		if (pPolygon != NULL)
		{
			pPolygon->Init(pos, size);
		}
	}
	return pPolygon;
}

//================================================
//テクスチャ割り当て処理
//================================================
void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}