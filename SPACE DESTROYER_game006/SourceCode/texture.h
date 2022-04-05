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
		TYPE_PLAYER = 0,					//プレイヤー
		TYPE_BULLET_PLAYER_NORMAL,			//プレイヤーの通常弾
		TYPE_BULLET_SPHERE,					//丸い弾
		TYPE_BULLET_BOSS_STRAIGHT,			//ボスの直進弾
		TYPE_BULLET_BOSS_LASER,				//ボスのレーザー弾
		TYPE_BULLET_BOSS_BODY_HOMING,		//ボスの体から出すホーミング弾
		TYPE_EXPLOSION,						//爆発
		TYPE_BG_00,							//背景00
		TYPE_BG_01,							//背景01
		TYPE_BG_02,							//背景02
		TYPE_BG_MENU,						//背景(メニュー画面)
		TYPE_BG_RESULT,						//背景(リザルト画面)
		TYPE_ENEMY_FIGHTER,					//敵戦闘機
		TYPE_ENEMY_UFO,						//敵UFO
		TYPE_ENEMY_SPHERE,					//球体型敵
		TYPE_ENEMY_ITEM_POWER,				//パワーアップアイテムを落とす敵
		TYPE_ENEMY_ITEM_SPEED,				//スピードアップアイテムを落とす敵
		TYPE_PLAYER_BULLET_00,				//プレイヤーの弾00
		TYPE_EFFECT,						//エフェクト
		TYPE_NUMBER,						//ナンバー
		TYPE_PLAYER_LIFE,					//プレイヤーのライフ
		TYPE_ITEM_SPEED,					//弾の連射スピードが上がるアイテム
		TYPE_ITEM_POWER,					//弾のレベルがアップするアイテム
		TYPE_ITEM_SCORE,					//スコアがアップするアイテム
		TYPE_MENU_BAND,						//メニュー画面にある上下の帯
		TYPE_MENU_CIRCLE_SMALL,				//メニュー画面にある円(小)
		TYPE_MENU_CIRCLE_BIG,				//メニュー画面にある円(大)
		TYPE_MENU_EXPLANATION_GAME,			//メニュー画面にある説明欄(GameStart)
		TYPE_MENU_EXPLANATION_TUTORIAL,		//メニュー画面にある説明欄(Tutorial)
		TYPE_MENU_EXPLANATION_EXIT,			//メニュー画面にある説明欄(Exit)
		TYPE_MENU_GAME_START,				//メニュー画面のGameStart
		TYPE_MENU_TUTORIAL,					//メニュー画面のTutorial
		TYPE_MENU_EXIT,						//メニュー画面のExit
		TYPE_BOSS_WING,						//ボスの羽
		TYPE_BOSS_BODY,						//ボスの体
		TYPE_BOSS_CANNON,					//ボスの大砲
		TYPE_PAUSE,							//ポーズ画面の枠
		TYPE_PAUSE_EXIT,					//ポーズ画面のExit
		TYPE_PAUSE_CONTINUE,				//ポーズ画面のContinue
		TYPE_DAMAGE_MASK,					//ダメージを受けた際のマスク
		TYPE_TUTORIAL_EXPLANATION_000,		//チュートリアルの説明欄
		TYPE_TUTORIAL_EXPLANATION_001,		//チュートリアルの説明欄
		TYPE_TUTORIAL_EXPLANATION_002,		//チュートリアルの説明欄
		TYPE_TUTORIAL_EXPLANATION_003,		//チュートリアルの説明欄
		TYPE_TUTORIAL_EXPLANATION_004,		//チュートリアルの説明欄
		TYPE_TUTORIAL_EXPLANATION_005,		//チュートリアルの説明欄
		TYPE_GAME_CLEAR,					//ゲームクリア
		TYPE_GAME_OVER,						//ゲームオーバー
		TYPE_TITLE,							//タイトル名
		TYPE_PRESS_START,					//pressStart
		TYPE_ENEMY_KILL_SCORE_100,			//敵を倒したときに出るスコア(100)
		TYPE_ENEMY_KILL_SCORE_200,			//敵を倒したときに出るスコア(200)
		TYPE_ENEMY_KILL_SCORE_400,			//敵を倒したときに出るスコア(400)
		TYPE_MAX							//テクスチャの最大数
	} TYPE;

	CTexture();			//コンストラクタ
	~CTexture();		//デストラクタ

	void Init(void);	// テクスチャの生成
	LPDIRECT3DTEXTURE9 GetTexture(TYPE Type);	// テクスチャの割り当て
	void Uninit(void);	// 終了
private:
	LPDIRECT3DTEXTURE9	m_pTexture[TYPE_MAX];	//テクスチャ
};

#endif