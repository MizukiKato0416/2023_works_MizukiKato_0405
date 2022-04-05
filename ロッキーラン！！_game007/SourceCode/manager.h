//===========================================
//マネージャ処理
//Author:加藤瑞葵
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "scene.h"
#include "camera.h"
#include "light.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CTitle;
class CTexture;
class CXload;
class CMenu;
class CGame01;
class CResult;
class CFade;
class CTutorial;
class CPlayData;
class CSound;
class CMotion;

//================================================
//マクロ定義
//================================================
#define MAX_STRINGS (128)

//================================================
//クラスの定義
//================================================
//クラスの定義
class CManager
{
public:
	//モードの種類
	typedef enum
	{
		MODE_TITLE = 0,			//タイトル
		MODE_MENU,				//メニュー
		MODE_TUTORIAL,			//チュートリアル
		MODE_GAME01,			//ゲーム01
		MODE_RESULT,			//リザルト
		MODE_MAX
	} MODE;

	CManager();				//コンストラクタ
	~CManager();			//デストラクタ

	//メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CRenderer *GetRenderer(void);				//レンダラー取得処理
	static CInputKeyboard *GetInputKeyboard(void);		//キーボード取得処理
	static CInputPadX *GetInputPadX(void);				//パッド(X)取得処理
	static CTitle *GetTitle(void);						//タイトル取得処理
	static CMenu *GetMenu(void);						//メニュー取得処理
	static CTutorial *GetTutorial(void);				//チュートリアル処理
	static CGame01 *GetGame01(void);					//ゲーム01取得処理
	static CResult *GetResult(void);					//リザルト取得処理
	static CTexture *GetTexture(void);					//テクスチャ取得処理
	static CXload *GetXload(void);						//xファイル読み込み取得処理
	static void SetMode(MODE mode);						//モード設定
	static MODE GetMode(void);							//モード取得
	static CFade *GetFade(void);						//フェード取得処理
	static CPlayData *GetPlayData(void);				//プレイデータ取得処理
	static CCamera **GetCamera(void);					//カメラ取得処理
	static CLight *GetLight(void);						//ライト取得処理
	static CSound *GetSound(void);						//サウンド取得処理

private:
	static CTitle *m_pTitle;							//タイトルのポインタ
	static CMenu *m_pMenu;								//メニューのポインタ
	static CTutorial *m_pTutorial;						//チュートリアルのポインタ
	static CGame01 *m_pGame01;							//ゲーム01のポインタ
	static CResult *m_pResult;							//リザルトのポインタ
	static CRenderer *m_pRenderer;						//レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;			//キーボードのポインタ
	static CInputPadX *m_pInputPadX;					//パッド(X)のポインタ
	static CTexture *m_pTexture;						//テクスチャのポインタ
	static CXload *m_pXload;							//xファイル読み込みのポインタ
	static MODE m_mode;									//モード
	static CFade *m_pFade;								//フェードのポインタ
	static CPlayData *m_pPlayData;						//プレイデータクラスのポインタ
	static CCamera *m_apCamera[MAX_CAMERA];				//カメラのポインタ
	static CLight *m_apLight[MAX_LIGHT];				//ライトのポインタ
	static CSound *m_pSound;							//サウンドのポインタ
	static CMotion *m_pMotion;							//モーションのポインタ
};


#endif // !_MANAGER_H_