//===========================================
//プレイデータ管理処理
//Author:KatoMizuki
//===========================================
#ifndef _PLAY_DATA_H_
#define _PLAY_DATA_H_
#include "main.h"

//前方宣言
class CGauge;
class CScore;

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

	void SetHitPoint(int nHitPoint) { m_nHitPoint = nHitPoint; }					//HP設定処理
	int GetHitPoint(void) { return m_nHitPoint; }									//HP取得処理
	void SetHpGauge(CGauge *pHpGauge) { m_pHpGauge = pHpGauge; }					//HPゲージのポインタ設定処理
	CGauge *GetHpGauge(void) { return m_pHpGauge; }									//HPゲージのポインタ取得処理
	void SetMagicPoint(int nMagicPoint) { m_nMagicPoint = nMagicPoint; }			//MP設定処理
	int GetMagicPoint(void) { return m_nMagicPoint; }								//MP取得処理
	void SetMpGauge(CGauge *pMpGauge) { m_pMpGauge = pMpGauge; }					//MPゲージのポインタ設定処理
	CGauge *GetMpGauge(void) { return m_pMpGauge; }									//MPゲージのポインタ取得処理
	void SetSpecialPoint(int nSpecialPoint) { m_nSpecialPoint = nSpecialPoint; }	//SP設定処理
	int GetSpecialPoint(void) { return m_nSpecialPoint; }							//SP取得処理
	void SetSpGauge(CGauge *pSpGauge) { m_pSpGauge = pSpGauge; }					//SPゲージのポインタ設定処理
	CGauge *GetSpGauge(void) { return m_pSpGauge; }									//SPゲージのポインタ取得処理
	void SetScore(int nScore) { m_nScore = nScore; }								//スコアの設定
	int GetScore(void) { return m_nScore; }											//スコアの取得
	void SetScorePoint(CScore *pScore) { m_pScore = pScore; }						//スコアのポインタ設定処理
	CScore *GetScorePoint(void) { return m_pScore; }								//スコアのポインタ取得処理
	void SetTime(int nTime) { m_nTime = nTime; }									//時間の設定
	int GetTime(void) { return m_nTime; }											//時間の取得
	void SetGameOver(bool bGameOver) { m_bGameOver = bGameOver; }					//ゲームオーバー設定処理
	bool GetGameOver(void) { return m_bGameOver; }									//ゲームオーバー取得処理
	void SetGameClear(bool bGameClear) { m_bGameClear = bGameClear; }				//ゲームクリア設定処理
	bool GetGameClear(void) { return m_bGameClear; }								//ゲームクリア取得処理

private:
	//メンバ変数
	int m_nHitPoint;				//プレイヤーのHP
	int m_nMagicPoint;				//プレイヤーのMP
	int m_nSpecialPoint;			//プレイヤーのSP
	CGauge *m_pHpGauge;				//HPゲージのポインタ
	CGauge *m_pMpGauge;				//MPゲージのポインタ
	CGauge *m_pSpGauge;				//SPゲージのポインタ
	int m_nScore;					//スコア
	CScore *m_pScore;				//スコアのポインタ
	int m_nTime;					//時間
	bool m_bGameOver;				//ゲームオーバーかどうか
	bool m_bGameClear;				//ゲームクリアかどうか
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PLAY_DATA_H_