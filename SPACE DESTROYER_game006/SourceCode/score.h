//===========================================
//スコア処理
//Authore:加藤瑞葵
//===========================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"
#include "number.h"

//================================================
//マクロ定義
//================================================
#define MAX_SCORE_POLYGON (8)				//ポリゴンの最大数
#define SCORE_POLYGON_WIDTH (30.0f)			//ポリゴンの幅
#define SCORE_POLYGON_HEIGHT (60.0f)		//ポリゴンの高さ

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
	CScore(int nPriority = PRIORITY_UI);				//コンストラクタ
	~CScore();								//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetScore(int nScore);
	void AddScore(int nValue);
	int GetScore(void);
	CNumber *GetNumber(int nNumber);


	static CScore *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_SCORE_POLYGON];			//numberのインスタンス
	int m_nScore;									//スコア

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCORE_H_