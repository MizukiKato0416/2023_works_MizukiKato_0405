//===========================================
//サウンド処理
//Authore:一戸健
//===========================================
#ifndef _SOUND_H_
#define _SOUND_H_
#include "main.h"

//================================================
//マクロ定義
//================================================

//========================================================
//構造体の定義
//========================================================

//================================================
//クラスの定義
//================================================
//クラスの定義
class CSound
{
public:
	CSound();				//コンストラクタ
	~CSound();				//デストラクタ

	//サウンドファイル
	typedef enum
	{
		SOUND_LABEL_CANCEL_SE = 0,			//キャンセルSE
		SOUND_LABEL_CHOICE_SE,				//選択SE
		SOUND_LABEL_COLLISION_SE,			//衝突時のSE
		SOUND_LABEL_COUNTDOWN_SE,			//カウントダウンSE
		SOUND_LABEL_DECISION_SE,			//決定SE
		SOUND_LABEL_GAMECLEAR_SE,			//ゴールSE
		SOUND_LABEL_GAMEOVER_SE,			//ゲームオーバーSE
		SOUND_LABEL_JUMP_SE,				//ジャンプSE
		SOUND_LABEL_POSESCREEN_SE,			//ポーズ画面を開くSE
		SOUND_LABEL_POSESCREENCLOSE_SE,		//ポーズ画面を閉じるSE
		SOUND_LABEL_START_SE,				//スタートSE
		SOUND_LABEL_TIPS_SE,				//ヒントSE
		SOUND_LABEL_SPRING_SE,				//バネSE
		SOUND_LABEL_ICE_SE,					//氷SE
		SOUND_LABEL_RESPAWN_SE,				//復活SE
		SOUND_LABEL_RANKING_SE,				//ランキングSE
		SOUND_LABEL_WIN_SE,					//勝利時SE
		SOUND_LABEL_DIVE_SE,				//ダイブSE
		SOUND_LABEL_TITLE_BGM,				//タイトルBGM
		SOUND_LABEL_MENU_BGM,				//メニューBGM
		SOUND_LABEL_TUTORIAL_BGM,			//チュートリアルBGM
		SOUND_LABEL_GAME_BGM,				//ゲーム内BGM
		SOUND_LABEL_RESULT_BGM,				//リザルトBGM
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);
	void ControllVoice(SOUND_LABEL label, float fVolume) { m_apSourceVoice[label]->SetVolume(fVolume); }	//音量調整

private:
	//パラメーター構造体
	typedef struct
	{
		char *filename;		// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;

	//メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2 = NULL;										// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;					// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};			// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};							// オーディオデータ
	DWORD m_asizeAudio[SOUND_LABEL_MAX] = {};							// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];								// 各音素材のパラメータ
};

//================================================
//プロトタイプ宣言
//================================================
#endif // !_SOUND_H_