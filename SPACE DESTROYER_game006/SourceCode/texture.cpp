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

	//プレイヤー
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player000.png",
		&m_pTexture[TYPE_PLAYER]);

	//弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/player_bullet000.png",
		&m_pTexture[TYPE_BULLET_PLAYER_NORMAL]);

	//丸い弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bullet000.png",
		&m_pTexture[TYPE_BULLET_SPHERE]);

	//ボスの直進弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_000.png",
		&m_pTexture[TYPE_BULLET_BOSS_STRAIGHT]);

	//ボスのレーザー弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_laser_000.png",
		&m_pTexture[TYPE_BULLET_BOSS_LASER]);

	//ボスの体から出すホーミング弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_bullet_001.png",
		&m_pTexture[TYPE_BULLET_BOSS_BODY_HOMING]);

	//爆発
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/explosion000.png",
		&m_pTexture[TYPE_EXPLOSION]);

	//背景00
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg000.jpg",
		&m_pTexture[TYPE_BG_00]);

	//背景01
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg001.png",
		&m_pTexture[TYPE_BG_01]);

	//背景02
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/bg002.png",
		&m_pTexture[TYPE_BG_02]);

	//背景(メニュー画面)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/menu_bg000.jpg",
		&m_pTexture[TYPE_BG_MENU]);

	//背景(リザルト画面)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/result_bg.png",
		&m_pTexture[TYPE_BG_RESULT]);

	//敵戦闘機
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy000.png",
		&m_pTexture[TYPE_ENEMY_FIGHTER]);

	//敵UFO
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy001.png",
		&m_pTexture[TYPE_ENEMY_UFO]);

	//球体型敵
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy003.png",
		&m_pTexture[TYPE_ENEMY_SPHERE]);

	//パワーアップアイテムを落とす敵
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_item_power.png",
		&m_pTexture[TYPE_ENEMY_ITEM_POWER]);

	//スピードアップアイテムを落とす敵
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_item_speed.png",
		&m_pTexture[TYPE_ENEMY_ITEM_SPEED]);

	//プレイヤーの弾
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/hamehame.png",
		&m_pTexture[TYPE_PLAYER_BULLET_00]);

	//エフェクト
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&m_pTexture[TYPE_EFFECT]);

	//ナンバー
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/number.png",
		&m_pTexture[TYPE_NUMBER]);

	//プレイヤーのライフ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/life000.png",
		&m_pTexture[TYPE_PLAYER_LIFE]);

	//弾の連射スピードがアップするアイテム
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_speed.png",
		&m_pTexture[TYPE_ITEM_SPEED]);

	//弾のレベルが上がるアイテム
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_power.png",
		&m_pTexture[TYPE_ITEM_POWER]);

	//スコアが上がるアイテム
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/item_score.png",
		&m_pTexture[TYPE_ITEM_SCORE]);

	//メニュー画面の上下にある帯
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_000.png",
		&m_pTexture[TYPE_MENU_BAND]);

	//メニュー画面にある円(小)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_001.png",
		&m_pTexture[TYPE_MENU_CIRCLE_SMALL]);

	//メニュー画面にある円(大)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_002.png",
		&m_pTexture[TYPE_MENU_CIRCLE_BIG]);

	//メニュー画面にある説明欄(GameStart)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_003.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_GAME]);

	//メニュー画面にある説明欄(Tutorial)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_005.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_TUTORIAL]);

	//メニュー画面にある説明欄(Exit)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_006.png",
		&m_pTexture[TYPE_MENU_EXPLANATION_EXIT]);

	//メニュー画面にあるGameStart
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_004.png",
		&m_pTexture[TYPE_MENU_GAME_START]);

	//メニュー画面にあるTutorial
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_007.png",
		&m_pTexture[TYPE_MENU_TUTORIAL]);

	//メニュー画面にあるExit
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ui_menu_008.png",
		&m_pTexture[TYPE_MENU_EXIT]);

	//ボスの羽
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_wing.png",
		&m_pTexture[TYPE_BOSS_WING]);

	//ボスの体
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_body.png",
		&m_pTexture[TYPE_BOSS_BODY]);

	//ボスの大砲
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/boss_cannon.png",
		&m_pTexture[TYPE_BOSS_CANNON]);

	//ポーズ画面の枠
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/pause.png",
		&m_pTexture[TYPE_PAUSE]);

	//ポーズ画面のExit
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/exit.png",
		&m_pTexture[TYPE_PAUSE_EXIT]);

	//ポーズ画面のContinue
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/continue.png",
		&m_pTexture[TYPE_PAUSE_CONTINUE]);

	//ダメージを受けた際のマスク
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/damage_mask.png",
		&m_pTexture[TYPE_DAMAGE_MASK]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_000.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_000]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_001.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_001]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_002.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_002]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_003.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_003]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_004.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_004]);

	//チュートリアルの説明欄
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tutorial_explanation_005.png",
		&m_pTexture[TYPE_TUTORIAL_EXPLANATION_005]);

	//ゲームクリア
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/game_clear_ui.png",
		&m_pTexture[TYPE_GAME_CLEAR]);

	//ゲームオーバー
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/game_over_ui.png",
		&m_pTexture[TYPE_GAME_OVER]);

	//タイトルロゴ
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/title_name.png",
		&m_pTexture[TYPE_TITLE]);

	//pressStart
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enter_or_start.png",
		&m_pTexture[TYPE_PRESS_START]);

	//敵を倒したときに出るスコア(100)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_100.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_100]);

	//敵を倒したときに出るスコア(200)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_200.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_200]);

	//敵を倒したときに出るスコア(400)
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/enemy_kill_score_400.png",
		&m_pTexture[TYPE_ENEMY_KILL_SCORE_400]);
}	

//=============================================================================
//終了
//=============================================================================
void CTexture::Uninit(void)
{
	for (int nCntTexture = 0; nCntTexture < TYPE_MAX; nCntTexture++)
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
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TYPE type)
{
	return m_pTexture[type]; 
}