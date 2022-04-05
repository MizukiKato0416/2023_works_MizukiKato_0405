//===========================================
//マネージャ処理
//Authore:加藤瑞葵
//===========================================
#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "scene.h"

//前方宣言
class CRenderer;
class CInputKeyboard;
class CInputPadX;
class CSound;
class CTexture;
class CTitle;
class CMenu;
class CGame01;
class CResult;
class CFade;
class CPlayData;
class CTutorial;

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
		MODE_TITLE  = 0,		//タイトル
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

	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CInputPadX *GetInputPadX(void);
	static CSound *GetSound(void);
	static CTexture *GetTexture(void);
	static CFade *GetFade(void);
	static CPlayData *GetPlayData(void);
	static CTitle *GetTitle(void);
	static CMenu *GetMenu(void);
	static CTutorial *GetTutorial(void);
	static CGame01 *GetGame01(void);
	static CResult *GetResult(void);
	static void SetMode(MODE mode);
	static MODE GetMode();


private:
	static CTitle *m_pTitle;
	static CMenu *m_pMenu;
	static CTutorial *m_pTutorial;
	static CGame01 *m_pGame01;
	static CResult *m_pResult;
	static MODE m_mode;

	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CInputPadX *m_pInputPadX;
	static CSound *m_pSound;
	static CTexture *m_pTexture;
	static CFade *m_pFade;
	static CPlayData *m_pPlayData;
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_MANAGER_H_