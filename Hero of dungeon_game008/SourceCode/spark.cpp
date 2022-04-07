//================================================
//火の粉の処理
//Author:KatoMizuki
//================================================
#include "spark.h"
#include "effect3D.h"

//================================================
//マクロ定義
//================================================
#define SPARK_MOVE_ROTATE			(float((rand() % 629 + -314)) / 100.0f)		//移動する方向
#define SPARK_SIZE_SUBTRACTION		(0.99f)										//サイズ減算値

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CSpark::CSpark(int nPriority) :CObject(nPriority)
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
CSpark::~CSpark()
{

}

//================================================
//初期化処理
//================================================
HRESULT CSpark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		//動的に確保
		m_pEffect3D.push_back(CEffect3D::Create(pos, size, m_col, CEffect3D::EFFECT3D_TYPE::NONE));

		//移動する方向を決める
		float fRotX = SPARK_MOVE_ROTATE;
		float fRotY = SPARK_MOVE_ROTATE;
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
void CSpark::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//================================================
//更新処理
//================================================
void CSpark::Update(void)
{
	for (int nCntEffect = 0; nCntEffect < static_cast<int>(m_pEffect3D.size()); nCntEffect++)
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
void CSpark::Draw(void)
{
	
}

//================================================
//生成処理
//================================================
CSpark* CSpark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
	                           float fGravity, float fColAMin, float fColAMax, float SubtractionMove)
{
	//インスタンスの生成
	CSpark *pSpark = nullptr;
	if (pSpark == nullptr)
	{
		pSpark = new CSpark();
		if (pSpark != nullptr)
		{
			pSpark->m_nNumEffect = nNumEffect;
			pSpark->m_col = col;
			pSpark->m_fGravity = fGravity;
			pSpark->m_fSubtractionMove = SubtractionMove;
			//ランダム値は整数でしか入れられないので整数にする
			pSpark->m_nColAMin = int(fColAMin * 100000.0f);
			pSpark->m_nColAMax = int(fColAMax * 100000.0f);
			//ランダムの数値生成時に引数で指定した数を最大値にするために計算
			pSpark->m_nColAMax -= pSpark->m_nColAMin;
			//ランダム値は整数でしか入れられないので整数にする
			int nMoveMin = int(fMoveMin * 100.0f);
			int nMoveMax = int(fMoveMax * 100.0f);
			//ランダムの数値生成時に引数で指定した数を最大値にするために計算
			nMoveMax -= nMoveMin;
			for (int nCnt = 0; nCnt < pSpark->m_nNumEffect; nCnt++)
			{
				//動的確保
				pSpark->m_fInitMove.push_back(float(rand() % nMoveMax + nMoveMin) / 100.0f);
			}
			pSpark->Init(pos, size);
		}
	}
	return pSpark;
}
