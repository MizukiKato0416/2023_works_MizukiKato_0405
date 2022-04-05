//===========================================
//ゲーム03処理
//Author:KatoMizuki
//===========================================
#ifndef _GAME03_H_
#define _GAME03_H_
#include "object.h"
#include "main.h"
#include "player.h"

//前方宣言
class CGauge;
class CObject2D;

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CGame03 : public CObject
{
public:
	CGame03(int nPriority = PRIORITY_NONE);		//コンストラクタ
	~CGame03();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	//メンバ関数
	void GameOver(void);		//ゲームオーバー処理

	//メンバ変数
	CGauge *m_pHpGauge;			//HPゲージのポインタ
	CGauge *m_pMpGauge;			//MPゲージのポインタ
	CGauge *m_pSpGauge;			//SPゲージのポインタ
	int m_nRecoveryCounter;		//回復するカウンター
	int m_nGameCounter;			//ゲーム中のカウンター
	CObject2D *m_pObjet2DGame;	//ゲームオーバー時のUI
};

#endif // !_GAME03_H_