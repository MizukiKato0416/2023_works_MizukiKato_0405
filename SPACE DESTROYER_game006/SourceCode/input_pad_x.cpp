//================================================
//パッド入力処理
//Authore:加藤瑞葵
//================================================
#include "input_pad_x.h"
#include "input.h"

//================================================
//静的メンバ変数宣言
//================================================

//================================================
//デフォルトコンストラクタ
//================================================
CInputPadX::CInputPadX()
{
	ZeroMemory(&m_state, sizeof(XINPUT_STATE));
	ZeroMemory(&m_stateLast, sizeof(XINPUT_STATE));
	ZeroMemory(&m_vibration, sizeof(XINPUT_VIBRATION));
	m_nCntVibration = 0;
	m_bVibration = false;
}

//================================================
//デストラクタ
//================================================
 CInputPadX::~ CInputPadX()
{

}

//================================================
//初期化処理
//================================================
HRESULT  CInputPadX::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	return S_OK;
}

//================================================
//終了処理
//================================================
void CInputPadX::Uninit(void)
{
	XInputEnable(false); // BOOL enable
	CInput::Uninit();
}

//================================================
//更新処理
//================================================
void CInputPadX::Update(void)
{
	XINPUT_STATE state;
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		m_bConnect = true;
	}
	else
	{
		// Controller is not connected
		m_bConnect = false;
	}

	//============================================
	//左スティック入力
	//============================================
	// Zero value if thumbsticks are within the dead zone
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	//============================================
	//右スティック入力
	//============================================
	// Zero value if thumbsticks are within the dead zone
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	//バイブレーション
	if (m_nCntVibration > 0)
	{
		m_nCntVibration--;
	}
	if (m_nCntVibration <= 0 && m_bVibration)
	{
		SetVibration(0, 0, 0);
		m_bVibration = false;
	}

	m_stateLast = m_state;
	m_state = state;

	//デバッグ終了
	if (GetButtonTrigger(XINPUT_GAMEPAD_START))
	{
		//PostQuitMessage(0);
	}
}

//=======================================================================
//パッドの入力情報取得
//=======================================================================
bool CInputPadX::GetButtonPress(int nButton)
{
	return m_state.Gamepad.wButtons & nButton ? true : false;
}

bool CInputPadX::GetButtonTrigger(int nButton)
{
	return (((m_stateLast.Gamepad.wButtons & nButton) == false) && (m_state.Gamepad.wButtons & nButton)) ? true : false;
}

bool CInputPadX::GetTriggerPress(int nTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGERTYPE_RIGHT:
		return m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case TRIGGERTYPE_LEFT:
		return m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool CInputPadX::GetTriggerTrigger(int nTrigger)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGERTYPE_RIGHT:
		return (((m_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case TRIGGERTYPE_LEFT:
		return (((m_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (m_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool CInputPadX::GetLeftStick(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool CInputPadX::GetLeftStickTrigger(int nLstick)//不完全
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool CInputPadX::GetRightStick(int nRstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nRstick)
	{
	case STICKTYPE_UP:
		return m_state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return m_state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return m_state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return m_state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool CInputPadX::GetLeftStickRelease(int nLstick)
{
	if (m_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return (((m_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return (((m_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_LEFT:
		return (((m_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	case STICKTYPE_DOWN:
		return (((m_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) == false) && (m_stateLast.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

//=======================================================================
//バイブレーション設定
//=======================================================================
void CInputPadX::SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd)
{
	m_vibration.wLeftMotorSpeed = nLeftSpeed;
	m_vibration.wRightMotorSpeed = nRightSpeed;
	XInputSetState(0, &m_vibration);
	m_nCntVibration = nCntEnd;
	m_bVibration = true;
}