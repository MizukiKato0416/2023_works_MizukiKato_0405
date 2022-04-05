//===========================================
//動きのあるUIの処理
//Authore:加藤瑞葵
//===========================================
#ifndef _UI_MOVE_H_
#define _UI_MOVE_H_
#include "ui.h"

//================================================
//マクロ定義
//================================================
#define UI_MENU_CIRCLE_SMALL_WIDTH					(458.0f)				//円(小)のポリゴンの幅
#define UI_MENU_CIRCLE_SMALL_HEIGHT					(460.0f)				//円(小)のポリゴンの高さ
#define UI_MENU_CIRCLE_BIG_WIDTH					(594.0f)				//円(大)のポリゴンの幅
#define UI_MENU_CIRCLE_BIG_HEIGHT					(596.0f)				//円(大)のポリゴンの高さ
#define UI_MENU_CIRCLE_POS_X						(239.0f)				//円のポリゴンのX座標
#define UI_MENU_CIRCLE_POS_Y						(295.0f)				//円のポリゴンのY座標
#define UI_MENU_CIRCLE_INIT_POS_Y					(-295.0f)				//円のポリゴンの初期Y座標
#define UI_MENU_EXPLANATION_GAME_WIDTH				(402.0f)				//説明欄(GameStart)のポリゴンの幅
#define UI_MENU_EXPLANATION_GAME_HEIGHT				(440.0f)				//説明欄(GameStart)のポリゴンの高さ
#define UI_MENU_EXPLANATION_TUTORIAL_WIDTH			(388.0f)				//説明欄(Tutorial)のポリゴンの幅
#define UI_MENU_EXPLANATION_TUTORIAL_HEIGHT			(429.0f)				//説明欄(Tutorial)のポリゴンの高さ
#define UI_MENU_EXPLANATION_EXIT_WIDTH				(388.0f)				//説明欄(Exit)のポリゴンの幅
#define UI_MENU_EXPLANATION_EXIT_HEIGHT				(429.0f)				//説明欄(Exit)のポリゴンの高さ
#define UI_MENU_EXPLANATION_TRUE_POS_X				(385.0f)				//表示されてる説明欄のポリゴンのX座標
#define UI_MENU_EXPLANATION_TRUE_POS_Y				(360.0f)				//表示されてる説明欄のポリゴンのY座標
#define UI_MENU_EXPLANATION_FALSE_POS_X				(-385.0f)				//表示されていない説明欄のポリゴンのX座標
#define UI_MENU_EXPLANATION_FALSE_POS_Y				(360.0f)				//表示されていない説明欄のポリゴンのY座標
#define UI_MENU_GAME_POS_Y							(360.0f)				//GameStartのポリゴンのY座標
#define UI_MENU_TUTORIAL_POS_Y						(210.0f)				//TutorialのポリゴンのY座標
#define UI_MENU_EXIT_POS_Y							(520.0f)				//ExitのポリゴンのY座標
#define UI_MENU_SELECT_TRUE_POS_X					(950.0f)				//表示されている選択肢のポリゴンのX座標
#define UI_MENU_SELECT_FALSE_POS_X					(1847.0f)				//表示されていない選択肢のポリゴンのX座標
#define UI_MENU_SELECT_TRUE_WIDTH					(567.0f)				//選択されている選択肢のポリゴンの幅
#define UI_MENU_SELECT_TRUE_HEIGHT					(131.0f)				//選択されている選択肢のポリゴンの高さ
#define UI_MENU_SELECT_FALSE_WIDTH					(379.0f)				//選択されていない選択肢のポリゴンの幅
#define UI_MENU_SELECT_FALSE_HEIGHT					(80.0f)					//選択されていない選択肢のポリゴンの高さ
#define UI_MENU_FLOAT_MOVE							(0.1f)					//浮遊の動きの速さ
#define UI_MENU_CIRCLE_FLOAT_MOVE_REVERSE			(120)					//円の浮遊の動きの上下を反転させるまでのカウント数
#define UI_MENU_EXPLANATION_FLOAT_MOVE_REVERSE		(130)					//説明欄の浮遊の動きの上下を反転させるまでのカウント数
#define UI_MENU_SELECT_FLOAT_MOVE_REVERSE			(140)					//選択肢の浮遊の動きの上下を反転させるまでのカウント数
#define UI_MENU_EXPLANATION_MOVE					(60.0f)					//説明欄の出現、退去の速度
#define UI_MENU_CIRCLE_INIT_MOVE					(40.0f)					//円が出現するときの初速
#define UI_MENU_SELECT_INIT_MOVE					(-60.0f)				//選択肢が出現するときの初速
#define UI_MENU_CIRCLE_SMALL_ROTATE_MAX_SPEED		(0.08f)					//円(小)の最大回転速度
#define UI_MENU_CIRCLE_BIG_ROTATE_MAX_SPEED			(0.06f)					//円(大)の最大回転速度
#define UI_MENU_CIRCLE_SMALL_ADD_ROTATE_SPEED		(0.001f)				//円(小)の回転速度の上昇スピード
#define UI_MENU_CIRCLE_BIG_ADD_ROTATE_SPEED			(0.0005f)				//円(大)の回転速度の上昇スピード
#define UI_MENU_NOT_SELECT_COLOR					(0.5f)					//選ばれていないときの選択肢の色の濃さ
#define UI_PAUSE_CONTINUE_POS_X						(640.0f)				//ポーズ画面にあるContinueのポリゴンのX座標
#define UI_PAUSE_CONTINUE_POS_Y						(333.0f)				//ポーズ画面にあるContinueのポリゴンのY座標
#define UI_PAUSE_CONTINUE_WIDTH						(316.0f)				//ポーズ画面にあるContinueのポリゴンの幅
#define UI_PAUSE_CONTINUE_HEIGHT					(50.0f)					//ポーズ画面にあるContinueのポリゴンの高さ
#define UI_PAUSE_EXIT_POS_X							(640.0f)				//ポーズ画面にあるExitのポリゴンのX座標
#define UI_PAUSE_EXIT_POS_Y							(441.0f)				//ポーズ画面にあるExitのポリゴンのY座標
#define UI_PAUSE_EXIT_WIDTH							(316.0f)				//ポーズ画面にあるExitのポリゴンの幅
#define UI_PAUSE_EXIT_HEIGHT						(50.0f)					//ポーズ画面にあるExitのポリゴンの高さ
#define UI_TITLE_INIT_POS_X							(SCREEN_WIDTH / 2.0f)	//タイトルのポリゴンのX座標
#define UI_TITLE_INIT_POS_Y							(-230.0f / 2.0f)		//タイトルのポリゴンのY座標
#define UI_TITLE_WIDTH								(860.0f)				//タイトルのポリゴンの幅
#define UI_TITLE_HEIGHT								(230.0f)				//タイトルのポリゴンの高さ
#define UI_TITLE_MOVE_Y								(4.0f)					//タイトルのポリゴンの移動量
#define UI_TITLE_PRESS_START_POS_X					(SCREEN_WIDTH / 2.0f)	//PRESSSTARTのポリゴンのX座標
#define UI_TITLE_PRESS_START_POS_Y					(556.0f)				//PRESSSTARTのポリゴンのY座標
#define UI_TITLE_PRESS_START_WIDTH					(298.0f)				//PRESSSTARTのポリゴンの幅
#define UI_TITLE_PRESS_START_HEIGHT					(52.0f)					//PRESSSTARTのポリゴンの高さ
#define UI_TITLE_PRESS_START_BLINK_COUNT			(30)					//PRESSSTARTの点滅の間隔
#define UI_ENEMY_KILL_SCORE_WIDTH					(50.0f * 1.2f)			//敵を倒したときに出るスコアの幅
#define UI_ENEMY_KILL_SCORE_HEIGHT					(14.0f * 1.2f)			//敵を倒したときに出るスコアの高さ
#define UI_ENEMY_KILL_SCORE_COUNT					(30)					//敵を倒したときに出るスコア表示時間

//================================================
//クラスの定義
//================================================
//クラスの定義
class CUiMove : public CUi
{
public:
	//UIの種類
	typedef enum
	{
		UI_MOVE_TYPE_NONE = 0,
		UI_MOVE_TYPE_TITLE,							//タイトル
		UI_MOVE_TYPE_PRESS_START,					//pressスタートのUI
		UI_MOVE_TYPE_MENU_CIRCLE_SMALL,				//メニュー画面にある円(小)
		UI_MOVE_TYPE_MENU_CIRCLE_BIG,				//メニュー画面にある円(大)
		UI_MOVE_TYPE_MENU_EXPLANATION_GAME,			//メニュー画面にある説明欄(GameStart)
		UI_MOVE_TYPE_MENU_EXPLANATION_TUTORIAL,		//メニュー画面にある説明欄(Tutorial)
		UI_MOVE_TYPE_MENU_EXPLANATION_EXIT,			//メニュー画面にある説明欄(Exit)
		UI_MOVE_TYPE_MENU_GAME_START,				//メニュー画面にあるGameStart
		UI_MOVE_TYPE_MENU_TUTORIAL,					//メニュー画面にあるTutorial
		UI_MOVE_TYPE_MENU_EXIT,						//メニュー画面にあるExit
		UI_MOVE_TYPE_PAUSE_EXIT,					//ポーズ画面にあるExit
		UI_MOVE_TYPE_PAUSE_CONTINUE,				//ポーズ画面にあるContinue
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_100,			//敵を倒したときに出るスコア
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_200,			//敵を倒したときに出るスコア
		UI_MOVE_TYPE_ENEMY_KILL_SCORE_400,			//敵を倒したときに出るスコア
		UI_MOVE_TYPE_MAX
	} UI_MOVE_TYPE;

	CUiMove();				//コンストラクタ
	~CUiMove();				//デストラクタ

	//メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUiMove *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CUiMove::UI_MOVE_TYPE);

private:
	//メンバ関数
	void TitleUi(void);		//タイトルに使うUiの処理
	void MenuUi(void);		//メニューに使うUiの処理
	void TutorialUi(void);	//チュートリアルに使うUiの処理
	bool GameUi(void);		//ゲーム中に使うUiの処理
	void ResultUi(void);	//リザルトに使うUiの処理
	void FloatMove(void);	//浮遊の動きの処理

	D3DXVECTOR3 m_pos;									//ポリゴンの位置
	D3DXVECTOR3	m_size;									//サイズ
	D3DXVECTOR3	m_move;									//移動量
	static LPDIRECT3DTEXTURE9 m_pTexture;				//共有テクスチャのポインタ
	UI_MOVE_TYPE m_nType;								//UIの種類
	bool m_bFloatMove;									//浮遊しているかしていないかのフラグ
	float m_fRot;										//ポリゴンを回転させるための角度
	D3DXVECTOR3 m_vertex[VERTEX_NUM];					//ポリゴンの4頂点の位置
	float m_fTanR;										//原点から頂点までの角度
	float m_fCircleR;									//回転させるポリゴンの4頂点の円軌道の半径
	float m_fRotateSpeed;								//回転させる速度
	bool m_bRotateReverse;								//逆回転状態かどうかfalseで逆回転
	int m_nBlinkCounter;								//点滅させるためのカウンター
	bool m_bBlink;										//点滅の状態
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_UI_MOVE_H_