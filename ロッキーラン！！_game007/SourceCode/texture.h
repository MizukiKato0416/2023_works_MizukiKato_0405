//=============================================================================
//テクスチャ処理
//Authore:加藤瑞葵
//=============================================================================
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//=============================================================================
// ヘッダファイルのインクルード
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CTexture
{
public:
	//テクスチャタイプ
	typedef enum
	{
		TEX_TYPE_SKY = 0,							//空
		TEX_TYPE_TILE,								//地面
		TEX_TYPE_NUMBER,							//ナンバー
		TEX_TYPE_COMMA,								//カンマ

		TEX_TYPE_TITLE_BG,							//タイトル背景
		TEX_TYPE_TITLE_UI_LOGO,						//タイトルUI:タイトルロゴ
		TEX_TYPE_TITLE_UI_PRESS,					//タイトルUI:Press文字
		TEX_TYPE_TITLE_UI_PLAYER_1P,				//タイトルUI:1P切り抜き画像
		TEX_TYPE_TITLE_UI_PLAYER_2P,				//タイトルUI:2P切り抜き画像

		TEX_TYPE_MENU_BG,							//メニュー背景
		TEX_TYPE_MEMU_EXPLANATION_FRAME,			//メニュー説明枠
		TEX_TYPE_MENU_UI_STAR,						//メニューUI:星
		TEX_TYPE_MENU_LOGO,							//メニューUI:メニューロゴ
		TEX_TYPE_MENU_UI_TUTORIAL,					//メニューUI:選択肢(チュートリアル)
		TEX_TYPE_MENU_UI_GAME,						//メニューUI:選択肢(ゲームスタート)
		TEX_TYPE_MENU_UI_BACKTITLE,					//メニューUI:選択肢(タイトルに戻る)
		TEX_TYPE_MENU_UI_TUTORIAL_EXPLANATION,		//メニューUI:選択肢の説明(チュートリアル)
		TEX_TYPE_MENU_UI_GAME_EXPLANATION,			//メニューUI:選択肢の説明(ゲームスタート)
		TEX_TYPE_MENU_UI_BACKTITLE_EXPLANATION,		//メニューUI:選択肢の説明(タイトルに戻る)

		TEX_TYPE_TUTORIAL_EXPLANATION,				//チュートリアルUI:操作説明
			
		TEX_TYPE_GAME_UI_COUNTDOWN03,				//ゲームUI:カウントダウン3
		TEX_TYPE_GAME_UI_COUNTDOWN02,				//ゲームUI:カウントダウン2
		TEX_TYPE_GAME_UI_COUNTDOWN01,				//ゲームUI:カウントダウン1
		TEX_TYPE_GAME_UI_START,						//ゲームUI:スタート
		TEX_TYPE_GAME_UI_CLEAR,						//ゲームUI:ゲームクリア
		TEX_TYPE_GAME_UI_TIME_UP,					//ゲームUI:タイムアップ
		TEX_TYPE_GOAL_TAPE,							//ゴールテープ

		TEX_TYPE_RESULT_BG,							//リザルト背景
		TEX_TYPE_RESULT_UI_WIN,						//リザルトUI:Win
		TEX_TYPE_RESULT_UI_RANKING01,				//リザルトUI:ランキング1位
		TEX_TYPE_RESULT_UI_RANKING02,				//リザルトUI:ランキング2位
		TEX_TYPE_RESULT_UI_RANKING03,				//リザルトUI:ランキング3位
		TEX_TYPE_RESULT_UI_RANKING04,				//リザルトUI:ランキング4位
		TEX_TYPE_RESULT_UI_RANKING05,				//リザルトUI:ランキング5位

		TEX_TYPE_PAUSE_UI_FRAME,					//ポーズUI:枠
		TEX_TYPE_PAUSE_UI_START,					//ポーズUI:再開
		TEX_TYPE_PAUSE_UI_EXIT,						//ポーズUI:終了
		TEX_TYPE_PAUSE_UI_RESTART,					//ポーズUI:やり直し

		TEX_TYPE_JUMP_SMOKE,						//ジャンプエフェクト
		TEX_TYPE_EFFECT,							//エフェクト
		TEX_TYPE_PLAYER_UI_1P,						//プレイヤーUI:1P
		TEX_TYPE_PLAYER_UI_2P,						//プレイヤーUI:2P
		TEX_TYPE_MAX								//テクスチャの最大数
	} TEX_TYPE;

	CTexture();										//コンストラクタ
	~CTexture();									//デストラクタ

	void Init(void);								// テクスチャの生成
	LPDIRECT3DTEXTURE9 GetTexture(TEX_TYPE Type);	// テクスチャの割り当て
	void Uninit(void);								// 終了
private:
	LPDIRECT3DTEXTURE9	m_pTexture[TEX_TYPE_MAX];	//テクスチャ
};

#endif