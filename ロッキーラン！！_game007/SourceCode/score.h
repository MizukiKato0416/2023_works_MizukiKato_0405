//===========================================
//スコア処理
//Author:加藤瑞葵
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"
#include "number.h"

//================================================
//マクロ定義
//================================================
#define MAX_SCORE_POLYGON		(6)				//ポリゴンの最大数
#define SCORE_POLYGON_WIDTH		(40.0f)			//ポリゴンの幅
#define SCORE_POLYGON_HEIGHT	(70.0f)			//ポリゴンの高さ
#define MAX_SCORE				(999999)		//最大スコア

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CScore : public CScene
{
public:
	CScore(int nPriority = PRIORITY_UI);	//コンストラクタ
	~CScore();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);			//スコア設定処理
	void AddScore(int nValue);			//スコア加算処理
	int GetScore(void);					//スコア取得処理
	void SetScorePos(D3DXVECTOR3 pos);	//スコア位置設定処理
	CNumber *GetNumber(int nNumber);

	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//numberのインスタンス
	int m_nScore;									//スコア
	D3DXVECTOR3 m_size;								//サイズ
	D3DXVECTOR3 m_pos;								//位置
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCORE_H_