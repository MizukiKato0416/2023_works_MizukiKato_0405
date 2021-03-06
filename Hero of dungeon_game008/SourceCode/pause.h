//===========================================
//ポーズ処理
//Author:KatoMizuki
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "object.h"
#include "main.h"

//前方宣言
class CObject2D;
class CManager;

//================================================
//マクロ定義
//================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CPause : public CObject
{
public:
	CPause(int nPriority = PRIORITY_PAUSE);			//コンストラクタ
	~CPause();										//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static bool GetPause(void);
	static bool SetPause(bool bPause);
	static CPause *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);

private:
	//画面遷移の選択肢ボタン
	typedef enum
	{
		SELECT_START = 0,		//再開ボタン
		SELECT_EXIT,			//メニューに戻るボタン
		SELECT_MAX
	}SELECT;

	CObject2D *m_apObject2D[SELECT_MAX];	//UI
	CObject2D *m_pObject2D;					//ポーズのフレーム
	int m_nSelect;							//選択肢
	static bool m_bPause;					//ポーズ画面かどうか
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PAUSE_H_