//===========================================
//プレイデータ管理処理
//Author:加藤瑞葵
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPlayData
{
public:
	CPlayData();			//コンストラクタ
	~CPlayData();			//デストラクタ

	//メンバ関数
	HRESULT Init(void);
	void Uninit(void);

	static void SetScore(int nScore);		//スコアの設定
	static int GetScore(void);				//スコアの取得
	static void SetWinNum(int nWinNum);		//勝った個体識別番号の設定
	static int GetWinNum(void);				//勝った個体識別番号の取得

private:
	static int m_nScore;					//スコア
	static int m_nWinNum;					//勝った個体識別番号
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PLAY_DATA_H_