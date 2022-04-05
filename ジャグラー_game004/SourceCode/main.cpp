//=======================================================================
//メイン(システム系)処理
//Aouthor: 加藤　瑞葵
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdio.h>
#include "main.h"
#include "input.h"
#include "fade.h"
#include "databox.h"
#include "title.h"
#include "title_press_enter.h"
#include "result.h"
#include "juggler.h"
#include "sound.h"


//マクロ定義
#define CLASS_NAME "WindowClass"				//ウィンドウクラスの名前
#define WINDOWS_NAME "JUGGLER"					//ウィンドウの名前(キャプション名)
#define SCREEN_WIDTH (1280)						//ウィンドウの幅
#define SCREEN_HEIGHT (720)						//ウィンドウの高さ

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//=======================================================================
//グローバル変数宣言
//=======================================================================

LPDIRECT3D9 g_pD3D = NULL;					//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;					//現在のモード

#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;			// フォントへのポインタ
#endif
int					g_nCountFPS;			// FPSカウンタ


											//メイン関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	//構造体の設定
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						//WNDCLASSEXのメモリサイズの指定
		CS_CLASSDC,								//表示するウィンドウのスタイルを設定
		WindowProc,								//ウィンドウプロシージャのアドレス(関数名)を指定
		0,										//通常は使用しないので0を指定（ほぼ特例なし）
		0,										//上に同じ
		hInstance,								//Windowsの引数のインスタンスハンドルを設定
		LoadIcon(NULL,IDI_APPLICATION),			//タスクバーに使用するアイコンを指定
		LoadCursor(NULL,IDC_ARROW),				//使用するマウスカーソルを指定
		(HBRUSH)(COLOR_WINDOW + 1),				//ウィンドウのクライアント領域の背景色を指定
		NULL,									//Windowにつけるメニューを設定
		CLASS_NAME,								//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)			//ファイルに使用するアイコンを設定
	};

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;				//ウィンドウハンドル(識別子)
	MSG msg;				//メッセージを格納する変数
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	//ウィンドウを生成
	hWnd = CreateWindowEx(0,							//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィンドウクラスの名前
		WINDOWS_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,		//ウィンドウスタイル
		CW_USEDEFAULT,				//ウィンドウの左上X座標
		CW_USEDEFAULT,				//ウィンドウの左上Y座標
		(rect.right - rect.left),	//ウィンドウの幅
		(rect.bottom - rect.top),	//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル
		NULL,						//メニューウィンドウまたは子ウィンドウ
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ

									//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);			//ウィンドウの表示(ウィンドウの表示状態を決定)
	UpdateWindow(hWnd);					//ウィンドウの反映(ウィンドウのクライアント領域を更新)

										//初期化処理(ウィンドウを生成してから行う)(DirectX本体の生成を行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime =
		dwFPSLastTime = timeGetTime();
	dwCurrentTime =
		dwFrameCount = 0;

	//ウィンドウの表示(初期化の処理の後に行う)
	ShowWindow(hWnd, nCmdShow);		//ウィンドウの表示
	UpdateWindow(hWnd);				//ウィンドウの反映

									//メッセージループ(メッセージキューからメッセージを取得)
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)		//メッセージを取得しなかった場合0を返す
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//"WM_QUIT"メッセージが送られてきたらループを抜ける
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);			//仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);			//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=================================
//ウィンドウプロシージャ
//=================================

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを返す
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:		//	escキーが押された
							/*nID = MessageBox(hWnd, "終了しますか？", "終了？", MB_YESNO);
							if (nID == IDYES)
							{
							//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
							DestroyWindow(hWnd);
							}
							else
							{
							return 0;
							}*/

							//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE:		//閉じるボタン押したときのメッセージ
						/*nID = MessageBox(hWnd, "終了しますか？", "終了？", MB_YESNO);
						if (nID == IDYES)
						{
						//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
						DestroyWindow(hWnd);
						}
						else
						{
						return 0;
						}*/

						//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
		DestroyWindow(hWnd);
		break;

	case WM_ACTIVATEAPP:
		//
		// XInputEnable is implemented by XInput 1.3 and 1.4, but not 9.1.0
		//

		if (wParam == TRUE)
		{
			// App is now active, so re-enable XInput
			XInputEnable(TRUE);
		}
		else
		{
			// App is now inactive, so disable XInput to prevent
			// user input from effecting application and to
			// disable rumble.
			XInputEnable(FALSE);
		}

		break;
	}



	return DefWindowProc(hWnd, uMsg, wParam, lParam);		//既定の処理を返す
}

//=======================================================================
//初期化処理
//=======================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;				//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		//プレゼンテーションパラメータ

										//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.Windowed = bWindow;						// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

																// デバイスの生成
																// ディスプレイアダプタを表すためのデバイスを作成
																// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリングを行わない
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
																			//透明度の設定をできるようにしている
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

																			// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

																			// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

#ifdef _DEBUG
	// デバッグ情報表示用フォントを設定
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
#endif


	//各種オブジェの初期化処理
	InitKeyboard(hInstance, hWnd);
	InitSound(hWnd);
	InitFade(g_mode);
	SetMode(g_mode);
	Initdata();

	return S_OK;
}

//=======================================================================
//終了処理
//=======================================================================
void Uninit(void)
{
#ifdef _DEBUG
	if (g_pFont != NULL)
	{// デバッグ情報表示用フォントを設定
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif
	//DirectX3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3D->Release();
		g_pD3DDevice = NULL;
	}

	//終了処理
	UninitKeyboard();
	UninitTitle();
	UninitJuggler();
	UninitResult();
	UninitTitlePressEnter();
	UninitSound();
	UninitFade();
}

//=======================================================================
//更新処理
//=======================================================================
void Update(void)
{
	//更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		UpdateTitlePressEnter();
		break;
	case MODE_JUGGLER:
		UpdateJuggler();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
	UpdateFade();
}

//=======================================================================
//描画処理
//=======================================================================
void Draw(void)
{
	//デバックバッファ&Zバッファのクリア
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(255, 0, 0, 0), 1.0f, 0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

#ifdef _DEBUG
		// FPS表示
		DrawFPS();

#endif

		D3DVIEWPORT9 viewportDef;
		//現在のビューポートを取得
		g_pD3DDevice->GetViewport(&viewportDef);

		//各種オブジェクトの描画処理
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			DrawTitlePressEnter();
			break;
		case MODE_JUGGLER:
			DrawJuggler();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}

		DrawFade();

		//ビューポートを元に戻す
		g_pD3DDevice->SetViewport(&viewportDef);

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=======================================================================
//設定処理
//=======================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		UninitTitlePressEnter();
		break;
	case MODE_JUGGLER:
		UninitJuggler();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}

	g_mode = mode;
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		InitTitlePressEnter();
		break;
	case MODE_JUGGLER:
		InitJuggler();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}


}


//=======================================================================
//取得処理
//=======================================================================
MODE GetMode(void)
{
	return g_mode;
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}


#ifdef _DEBUG
//=============================================================================
// FPS表示処理
//=============================================================================
void DrawFPS(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	wsprintf(str, "FPS:%d\n", g_nCountFPS);

	// テキスト描画
	g_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

}

//=============================================================================
// いろいろ表示処理
//=============================================================================
void DrawCameratxt(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char strtage[1000];

	// テキスト描画
	g_pFont->DrawText(NULL, strtage, -1, &rect, DT_RIGHT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif