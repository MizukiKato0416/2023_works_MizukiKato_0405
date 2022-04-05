//===========================================
//タイム処理
//Author:寺下琉生
//===========================================
#ifndef _TIME_H_
#define _TIME_H_
#include "scene.h"
#include "number.h"

//================================================
//マクロ定義
//================================================
#define MAX_TIME_POLYGON		(6)				//ポリゴンの最大数
#define TIME_POLIGON_POSY		(30.0f)			//タイムのポリゴンのposY
#define TIME_POLYGON_WIDTH		(50.0f)			//ポリゴンの幅
#define TIME_POLYGON_HEIGHT		(80.0f)			//ポリゴンの高さ
#define START_TIME				(0)				//最初のタイム

//================================================
//前方宣言
//================================================
class CUi;

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CTimer : public CScene
{
public:
	CTimer(int nPriority = PRIORITY_UI);	//コンストラクタ
	~CTimer();								//デストラクタ

											//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddTime(int nValue);
	void SetTime(int nTime);
	int GetTime(void);
	CNumber *GetNumber(int nNumber);

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	CNumber *m_apNumber[MAX_TIME_POLYGON];	//numberのインスタンス
	int m_nTime;							//タイム
	CUi *m_pUi;								//UIのポインタ

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SCORE_H_#pragma once
