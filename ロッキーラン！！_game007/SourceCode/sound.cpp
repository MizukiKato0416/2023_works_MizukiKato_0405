//================================================
//サウンド処理
//Authore:一戸健
//================================================
#include "sound.h"

//================================================
//静的メンバ変数宣言
//================================================
CSound::PARAM CSound::m_aParam[SOUND_LABEL_MAX] =
{
	{ "data/SE/Cancel_SE.wav", 0 },				//キャンセルSE
	{ "data/SE/Choice_SE.wav", 0 },				//選択SE
	{ "data/SE/Collision_SE.wav", 0 },			//衝突時のSE
	{ "data/SE/Countdown_SE.wav", 0 },			//カウントダウンSE
	{ "data/SE/Decision_SE.wav", 0 },			//決定SE
	{ "data/SE/GameClear_SE.wav", 0 },			//ゴールSE
	{ "data/SE/GameOver_SE.wav", 0 },			//ゲームオーバーSE
	{ "data/SE/Jump_SE.wav", 0 },				//ジャンプSE
	{ "data/SE/PoseScreen_SE.wav", 0 },			//ポーズ画面を開くSE
	{ "data/SE/PoseScreenClose_SE.wav", 0 },	//ポーズ画面を閉じるSE
	{ "data/SE/Start_SE.wav", 0 },				//スタートSE
	{ "data/SE/Tips_SE.wav", 0 },				//ヒントSE
	{ "data/SE/Spring_SE.wav", 0 },				//バネSE
	{ "data/SE/Ice_SE.wav", -1 },				//氷SE
	{ "data/SE/Respawn_SE.wav", 0 },			//復活SE
	{ "data/SE/Ranking1_SE.wav", 0 },			//ランキングSE
	{ "data/SE/Win_SE.wav", 0 },				//勝利時SE
	{ "data/SE/Dive_SE.wav", 0 },				//ダイブSE
	{ "data/BGM/Titele_BGM.wav", -1 },			//タイトルBGM
	{ "data/BGM/Menu_BGM.wav", -1 },			//メニューBGM
	{ "data/BGM/Tutorial_BGM.wav", -1 },		//チュートリアルBGM
	{ "data/BGM/Game_BGM.wav", -1 },			//ゲーム内BGM
	{ "data/BGM/Result_BGM.wav", -1 },			//リザルトBGM
};

//================================================
//デフォルトコンストラクタ
//================================================
CSound::CSound()
{
	
}

//================================================
//デストラクタ
//================================================
CSound::~CSound()
{

}

//================================================
//初期化処理
//================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		if (m_pXAudio2)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
		}

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunksize = 0;
		DWORD dwChunkPosition = 0;
		DWORD filetype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aParam[nCntSound].filename, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunksize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunk(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		if (filetype != 'EVAW')
		{
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunksize, &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		hr = ReadChunk(hFile, &wfx, dwChunksize, dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_asizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_asizeAudio[nCntSound]);
		hr = ReadChunk(hFile, m_apDataAudio[nCntSound], m_asizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));

		// バッファの設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_asizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aParam[nCntSound].nCntLoop;

		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}

//================================================
//終了処理
//================================================
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();

	if (m_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(停止)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER       buffer;

	// バッファの設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_asizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aParam[label].nCntLoop;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[label]->Stop(0);

		// クリア
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// 登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中
	 // 一時停止
		m_apSourceVoice[label]->Stop(0);

		// クリア
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止
//=============================================================================
void CSound::Stop(void)
{
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// クリア
			m_apSourceVoice[nCntSound]->FlushSourceBuffers();
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunksize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDatasize;
	DWORD dwRIFFDatasize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDatasize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDatasize = dwChunkDatasize;
			dwChunkDatasize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDatasize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunksize = dwChunkDatasize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDatasize;
		if (dwBytesRead >= dwRIFFDatasize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}