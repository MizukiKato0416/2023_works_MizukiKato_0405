//=============================================================================
//テクスチャ処理
//Authore:加藤瑞葵
//=============================================================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CTexture::CTexture()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTexture::~CTexture()
{

}

//=============================================================================
//テクスチャの生成
//=============================================================================
void CTexture::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice; //デバイスのポインタ
	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスを取得する

	//テクスチャの読み込み
	//空
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/base/sky.jpg",
		&m_pTexture[TEX_TYPE_SKY]);

	//地面
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/base/mist.png",
		&m_pTexture[TEX_TYPE_TILE]);

	//ナンバー
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/number.png",
		&m_pTexture[TEX_TYPE_NUMBER]);

	//カンマ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/comma.png",
		&m_pTexture[TEX_TYPE_COMMA]);

	//タイトル背景
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_bg.png",
		&m_pTexture[TEX_TYPE_TITLE_BG]);

	//タイトルUI:タイトルロゴ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_logo.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_LOGO]);

	//タイトルUI:Press文字
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/press_start_or_B!.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PRESS]);

	//タイトルUI:1P切り抜き画像
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_player_1p.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PLAYER_1P]);

	//タイトルUI:2P切り抜き画像
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TITLE/title_ui_player_2p.png",
		&m_pTexture[TEX_TYPE_TITLE_UI_PLAYER_2P]);

	//メニュー背景
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_bg.png",
		&m_pTexture[TEX_TYPE_MENU_BG]);

	//メニュー説明枠
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_explanation_frame.png",
		&m_pTexture[TEX_TYPE_MEMU_EXPLANATION_FRAME]);

	//メニューUI:星
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/star.png",
		&m_pTexture[TEX_TYPE_MENU_UI_STAR]);

	//メニューUI:メニューロゴ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_logo.png",
		&m_pTexture[TEX_TYPE_MENU_LOGO]);

	//メニューUI:チュートリアル
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_tutorial_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_TUTORIAL]);

	//メニューUI:ゲームスタート
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_game_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_GAME]);

	//メニューUI:タイトルに戻る
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_backtitle_button.png",
		&m_pTexture[TEX_TYPE_MENU_UI_BACKTITLE]);

	//メニューUI:チュートリアル説明
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_tutorial_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_TUTORIAL_EXPLANATION]);

	//メニューUI:ゲーム説明
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_game_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_GAME_EXPLANATION]);

	//メニューUI:ゲーム終了説明
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/MENU/menu_ui_backtitle_explanation.png",
		&m_pTexture[TEX_TYPE_MENU_UI_BACKTITLE_EXPLANATION]);

	//チュートリアルUI:操作説明
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/TUTORIAL/tutorial_ui_explanation.png",
		&m_pTexture[TEX_TYPE_TUTORIAL_EXPLANATION]);

	//ゲームUI:カウントダウン3
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown3.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN03]);

	//ゲームUI:カウントダウン2
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown2.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN02]);

	//ゲームUI:カウントダウン1
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_countdown1.png",
		&m_pTexture[TEX_TYPE_GAME_UI_COUNTDOWN01]);

	//ゲームUI:スタート
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_start.png",
		&m_pTexture[TEX_TYPE_GAME_UI_START]);

	//ゲームUI:ゲームクリア
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/game_clear.png",
		&m_pTexture[TEX_TYPE_GAME_UI_CLEAR]);

	//ゲームUI:タイムアップ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/timeup.png",
		&m_pTexture[TEX_TYPE_GAME_UI_TIME_UP]);

	//ゴールテープ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GAME/goal_tape.jpg",
		&m_pTexture[TEX_TYPE_GOAL_TAPE]);

	//リザルト背景
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/result_bg.png",
		&m_pTexture[TEX_TYPE_RESULT_BG]);

	//リザルトUI:Win
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/Win!.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_WIN]);

	//リザルトUI:ランキング1位
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/1st.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING01]);

	//リザルトUI:ランキング2位
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/2nd.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING02]);

	//リザルトUI:ランキング3位
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/3rd.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING03]);

	//リザルトUI:ランキング4位
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/4th.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING04]);

	//リザルトUI:ランキング5位
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/RESULT/5th.png",
		&m_pTexture[TEX_TYPE_RESULT_UI_RANKING05]);

	//ポーズUI:枠
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_frame.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_FRAME]);

	//ポーズUI:再開
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_start.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_START]);

	//ポーズUI:終了
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_exit.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_EXIT]);

	//ポーズUI:やり直し
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PAUSE/pause_ui_restart.png",
		&m_pTexture[TEX_TYPE_PAUSE_UI_RESTART]);

	//ジャンプエフェクト
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/Jump_kemuri.png",
		&m_pTexture[TEX_TYPE_JUMP_SMOKE]);

	//影エフェクト
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/effect000.jpg",
		&m_pTexture[TEX_TYPE_EFFECT]);

	//1P
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/1P.png",
		&m_pTexture[TEX_TYPE_PLAYER_UI_1P]);

	//2P
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PLAYER/2P.png",
		&m_pTexture[TEX_TYPE_PLAYER_UI_2P]);
}

//=============================================================================
//終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < TEX_TYPE_MAX; nCntTexture++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTexture] != NULL)
		{
			m_pTexture[nCntTexture]->Release();
			m_pTexture[nCntTexture] = NULL;
		}
	}
}

//=============================================================================
//テクスチャ割り当て
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEX_TYPE type)
{
	return m_pTexture[type];
}