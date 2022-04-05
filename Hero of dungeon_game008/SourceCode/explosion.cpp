//================================================
//爆発の処理
//Author:KatoMizuki
//================================================
#include "explosion.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define EXPLOSION_MOVE_ROTATE			(float((rand() % 629 + -314)) / 100.0f)		//移動する方向
#define EXPLOSION_SIZE_SUBTRACTION		(0.99f)										//サイズ減算値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CExplosion::CExplosion(int nPriority) :CObject(nPriority)
{
	m_pEffect3D.clear();
	m_fRotX.clear();
	m_fRotY.clear();
	m_fInitMove.clear();
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nNumEffect = 0;
	m_fGravity = 0.0f;
	m_nColAMin = 0;
	m_nColAMax = 0;
	m_fSubtractionMove = 0.0f;
}

//================================================
//オーバーロードされたコンストラクタ
//================================================

//================================================
//デストラクタ
//================================================
CExplosion::~CExplosion()
{

}

//================================================
//初期化処理
//================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		//動的に確保
		m_pEffect3D.push_back(CEffect3D::Create(pos, size, m_col, CEffect3D::EFFECT3D_TYPE::FIRE));

		//移動する方向を決める
		float fRotX = EXPLOSION_MOVE_ROTATE;
		float fRotY = EXPLOSION_MOVE_ROTATE;
		//動的確保
		m_fRotX.push_back(fRotX);
		m_fRotY.push_back(fRotY);
	}

	//オブジェクトの種類を設定
	SetObjType(CObject::OBJTYPE::FIRE_BALL);

	//位置とサイズを設定
	SetPos(pos);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CExplosion::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CExplosion::Update(void)
{
	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		if (m_pEffect3D[nCntEffect] != nullptr)
		{
			//位置とサイズを取得
			D3DXVECTOR3 pos = m_pEffect3D[nCntEffect]->GetPos();
			D3DXVECTOR3 size = m_pEffect3D[nCntEffect]->GetSize();

			//移動量を設定
			D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fRotX[nCntEffect]) * sinf(m_fRotY[nCntEffect]) * m_fInitMove[nCntEffect],
				                           sinf(m_fRotX[nCntEffect]) * cosf(m_fRotY[nCntEffect]) * m_fInitMove[nCntEffect],
				                           cosf(m_fRotX[nCntEffect]) * m_fInitMove[nCntEffect]);
			//重力
			move.y -= m_fGravity;

			//移動量反映
			pos += move;

			//サイズを小さくする
			size.x *= EXPLOSION_SIZE_SUBTRACTION;
			size.y *= EXPLOSION_SIZE_SUBTRACTION;

			//カラーを取得
			D3DXCOLOR col = m_pEffect3D[nCntEffect]->GetCol();
			//薄くする
			float fCola = float((rand() % m_nColAMax + m_nColAMin)) / 100000.0f;
			col.a -= fCola;
			//見えなくなったら
			if (col.a <= 0.0f)
			{
				//消す
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
			else
			{
				//カラーを設定
				m_pEffect3D[nCntEffect]->SetCol(col);

				//位置を設定
				m_pEffect3D[nCntEffect]->SetPos(pos, size);

				//移動量を減らしていく
				m_fInitMove[nCntEffect] *= m_fSubtractionMove;
			}
		}
	}
}

//================================================
//描画処理
//================================================
void CExplosion::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
	                           float fGravity, float fColAMin, float fColAMax, float SubtractionMove)
{
	//インスタンスの生成
	CExplosion *pExplosion = nullptr;
	if (pExplosion == nullptr)
	{
		pExplosion = new CExplosion();
		if (pExplosion != nullptr)
		{
			pExplosion->m_nNumEffect = nNumEffect;
			pExplosion->m_col = col;
			pExplosion->m_fGravity = fGravity;
			pExplosion->m_fSubtractionMove = SubtractionMove;
			//ランダム値は整数でしか入れられないので整数にする
			pExplosion->m_nColAMin = int(fColAMin * 100000.0f);
			pExplosion->m_nColAMax = int(fColAMax * 100000.0f);
			//ランダムの数値生成時に引数で指定した数を最大値にするために計算
			pExplosion->m_nColAMax -= pExplosion->m_nColAMin;
			//ランダム値は整数でしか入れられないので整数にする
			int nMoveMin = int(fMoveMin * 100.0f);
			int nMoveMax = int(fMoveMax * 100.0f);
			//ランダムの数値生成時に引数で指定した数を最大値にするために計算
			nMoveMax -= nMoveMin;
			for (int nCnt = 0; nCnt < pExplosion->m_nNumEffect; nCnt++)
			{
				//動的確保
				pExplosion->m_fInitMove.push_back(float(rand() % nMoveMax + nMoveMin) / 100.0f);
			}
			pExplosion->Init(pos, size);
		}
	}
	return pExplosion;
}
