//===========================================
//ゲージ処理
//Author:KatoMizuki
//===========================================
#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object2D.h"

//前方宣言

//================================================
//マクロ定義
//================================================
#define GAUGE_HP_POS_X	(63.0f)									//HPゲージの位置X
#define GAUGE_HP_POS_Y	(668.0f + GAUGE_HP_SIZE_Y / 2.0f)		//HPゲージの位置Y
#define GAUGE_HP_SIZE_X	(610.99f)								//HPゲージのサイズX
#define GAUGE_HP_SIZE_Y	(15.01f)								//HPゲージのサイズY
#define GAUGE_MP_POS_X	(63.0f)									//MPゲージの位置X
#define GAUGE_MP_POS_Y	(696.0f + GAUGE_MP_SIZE_Y / 2.0f)		//MPゲージの位置Y
#define GAUGE_MP_SIZE_X	(610.99f)								//MPゲージのサイズX
#define GAUGE_MP_SIZE_Y	(8.99f)									//MPゲージのサイズY
#define GAUGE_SP_POS_X	(124.84f)								//SPゲージの位置X
#define GAUGE_SP_POS_Y	(644.0f + GAUGE_SP_SIZE_Y / 2.0f)		//SPゲージの位置Y
#define GAUGE_SP_SIZE_X	(317.36f)								//SPゲージのサイズX
#define GAUGE_SP_SIZE_Y	(15.01f)								//SPゲージのサイズY

//================================================
//クラスの定義
//================================================
//クラスの定義
class CGauge : public CObject2D
{
public:
	CGauge(int nPriority = PRIORITY_UI);		//コンストラクタ
	~CGauge();									//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nMaxNum, int nNum);

	void AddGauge(int nNum);					//ゲージ増減処理
	void SetGauge(int nNum);					//ゲージ設定処理
	int GetGauge(void) { return m_nNum; }		//ゲージ取得処理
	void SetMaxNum(int nMaxNum);				//ゲージ最大数値設定処理
	int GetMaxNum(void) { return m_nMaxNum; }	//ゲージ最大数値取得処理

private:
	int m_nMaxNum;					//ゲージの最大数値
	int m_nNum;						//ゲージの現在数値
	D3DXVECTOR3 m_sizeMax;			//サイズの最大値
};

#endif // !_GAUGE_H_