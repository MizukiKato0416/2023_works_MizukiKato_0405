//===========================================
//プレイデータ管理処理
//Authore:加藤瑞葵
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

	static void SetPlayerLife(int nLife);	//プレイヤーのライフの設定
	static int GetPlayerLife(void);			//プレイヤーのライフの取得
	static void SetScore(int nScore);		//スコアの設定
	static int GetScore(void);				//スコアの取得

private:
	static int m_nPlayerLife;				//プレイヤーのライフ
	static int m_nScore;					//スコア

};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PLAY_DATA_H_