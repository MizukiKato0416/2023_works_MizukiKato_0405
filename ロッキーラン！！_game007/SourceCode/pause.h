//===========================================
//ポーズ処理
//Authore:寺下琉生
//===========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"

//================================================
//マクロ定義
//================================================
#define PAUSE_SELECT_COL					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		//選択中の色(白い方)
#define PAUSE_DEFAULT_COL					(D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f))		//デフォの色(グレーの方)

#define PAUSE_FRAME_SIXEX					(770.0f)								//ポーズフレームのsizeX
#define PAUSE_FRAME_SIXEY					(570.0f)								//ポーズフレームのsizeY
#define PAUSE_CHOICES_SPACE					(100.0f)								//選択肢の間隔	
#define PAUSE_UI_SIZEX						(370.0f)								//選択肢のsizeX
#define PAUSE_UI_SIZEY						(90.0f)									//選択肢のsizeY
#define PAUSE_START_BUTTON_POSY				(180.0f)								//選択肢:再開のposY
#define PAUSE_EXIT_BUTTON_POSY				(320.0f)								//選択肢:メニューに戻るのposY
#define PAUSE_RESTART_BUTTON_POSY			(460.0f)								//選択肢:リスタートのposY
//========================================================
//構造体の定義
//========================================================

//========================================================
//前方宣言
//========================================================
class CUi;
class CScene2D;
class CManager;
//================================================
//クラスの定義
//================================================
//クラスの定義
class CPause : public CScene
{
public:
	CPause(int nPriority = PRIORITY_PAUSE);				//コンストラクタ
	~CPause();				//デストラクタ

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
		SELECT_START,			//再開ボタン
		SELECT_EXIT,			//メニューに戻るボタン
		SELECT_RESTART,			//リスタートボタン
		SELECT_MAX
	}SELECT;

	CUi *m_apSelect[SELECT_MAX];		//各選択肢
	CScene2D *m_pScene2D;				//Scene2Dのポインタ
	CManager *m_pManager;				//Managerのポインタ
	int m_nSelect;						//今の選択肢
	static bool m_bPause;				//ポーズ画面かどうか
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_PAUSE_H_