//===========================================
//ランキング処理
//Author:加藤瑞葵
//===========================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "scene.h"
#include "scene2D.h"
#include "number.h"
#include "score.h"

//================================================
//前方宣言
//================================================
class CScene2D;
class CUi;

//================================================
//マクロ定義
//================================================
#define MAX_RANKING					(5)									//ランキングの最大数
#define MAX_SCORE_DATA				(MAX_RANKING + 1)					//スコアデータの最大数
#define RANKING_POLYGON_WIDTH		(30.0f * 1.4f)						//ポリゴンの幅
#define RANKING_POLYGON_HEIGHT		(60.0f * 1.4f)						//ポリゴンの高さ
#define RANKING_RANK_POLYGON_SIZE	(D3DXVECTOR3(225.0f,90.0f,0.0f))	//ランクのサイズ
#define RANKING_RANK_POLYGON_POS_X	(420.0f)							//ランクのX座標
#define RANKING_MOVE_X				(-30.0f)							//ランキングに出すUIの移動量

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CRanking : public CScene
{
public:
	CRanking();					//コンストラクタ
	~CRanking();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRanking *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	static CScore *m_apScore[MAX_RANKING];

	int m_nScore[MAX_SCORE_DATA];			//スコア
	int m_nNowScore;						//今回のスコア
	D3DCOLORVALUE	m_col;					//カラー
	CScene2D *m_apScene2D[MAX_RANKING];		//Scene2Dのポインタ
	CUi *m_apUi[MAX_RANKING];				//UIのポインタ
};

#endif // !_RANKING_H_