//=======================================================================
//���͂Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "pad.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "stage1.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
XINPUT_STATE g_state;
XINPUT_STATE g_stateLast;
XINPUT_VIBRATION g_vibration;
bool g_bConnect;
int g_nCntVibration;
bool g_bVibration;


//=======================================================================
//����������
//=======================================================================
HRESULT InitPad(void)
{
	ZeroMemory(&g_state, sizeof(XINPUT_STATE));
	ZeroMemory(&g_stateLast, sizeof(XINPUT_STATE));
	ZeroMemory(&g_vibration, sizeof(XINPUT_VIBRATION));
	g_nCntVibration = 0;
	g_bVibration = false;
	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitPad(void)
{
	XInputEnable(false); // BOOL enable
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdatePad(void)
{
	Camera *pCamera;
	pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	Stage1 *pStage1 = GetStage1();

	XINPUT_STATE state;
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);
	
	g_stateLast = g_state;
	g_state = state;

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		g_bConnect = true;
	}
	else
	{
		// Controller is not connected
		g_bConnect = false;
	}

	//============================================
	//���X�e�B�b�N����
	//============================================
	// Zero value if thumbsticks are within the dead zone
	if ((g_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbLX = 0;
		g_state.Gamepad.sThumbLY = 0;
	}

	//============================================
	//�E�X�e�B�b�N����
	//============================================
	// Zero value if thumbsticks are within the dead zone
	if ((g_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		g_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(g_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			g_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		g_state.Gamepad.sThumbRX = 0;
		g_state.Gamepad.sThumbRY = 0;
	}

	//�o�C�u���[�V����
	if (g_nCntVibration > 0)
	{
		g_nCntVibration--;
	}
	if (g_nCntVibration <= 0 && g_bVibration)
	{
		SetVibration(0,0,0);
		g_bVibration = false;
	}
	/*
	//�^�C�g�����̏���
	if (GetMode() == MODE_TITLE)
	{
		//�|�[�Y�@�X�^�[�g�{�^��
		if (g_state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			SetMode(MODE_STAGE1);
		}
	}
	//�������̏���
	if (GetMode() == MODE_DESCRIPTION)
	{
		//�E�����ꂽ
		if (g_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			pPlayer->move.x = +cosf(pCamera->rot.y) * PLAYER_SPEED;
			pPlayer->move.z = -sinf(pCamera->rot.y) * PLAYER_SPEED;

			pCamera->posV.x = pCamera->posV.x + cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
			pCamera->posV.z = pCamera->posV.z - sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

			pPlayer->fNumTurnPlayer = pCamera->rot.y + D3DX_PI / 2.0f;
			pPlayer->bTurnPlayer = true;
		}
		//�������ꂽ
		else if (g_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			pPlayer->move.x = -cosf(pCamera->rot.y) * PLAYER_SPEED;
			pPlayer->move.z = +sinf(pCamera->rot.y) * PLAYER_SPEED;

			pCamera->posV.x = pCamera->posV.x - cosf(pCamera->rot.y) * CAMERA_VR_SPEED;
			pCamera->posV.z = pCamera->posV.z + sinf(pCamera->rot.y) * CAMERA_VR_SPEED;

			pPlayer->fNumTurnPlayer = pCamera->rot.y - D3DX_PI / 2.0f;
			pPlayer->bTurnPlayer = true;
		}
	}
	*/
	

	//�f�o�b�O�I��
	if(GetButtonTrigger(XINPUT_GAMEPAD_START))
	{
		//PostQuitMessage(0);
	}
}

//=======================================================================
//�L�[�{�[�h�̓��͏��擾
//=======================================================================
bool GetButtonPress(int nButton)
{
	return g_state.Gamepad.wButtons & nButton ? true : false;
}

bool GetButtonTrigger(int nButton)
{
	return (((g_stateLast.Gamepad.wButtons & nButton) == false)  && (g_state.Gamepad.wButtons & nButton)) ? true : false;
}

bool GetTriggerPress(int nTrigger)
{
	if (g_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGERTYPE_RIGHT:
		return g_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	case TRIGGERTYPE_LEFT:
		return g_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool GetTriggerTrigger(int nTrigger)
{
	if (g_bConnect == false)
	{
		return false;
	}

	switch (nTrigger)
	{
	case TRIGGERTYPE_RIGHT:
		return (((g_stateLast.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (g_state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	case TRIGGERTYPE_LEFT:
		return (((g_stateLast.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) == false) && (g_state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool GetLeftStick(int nLstick)
{
	if (g_bConnect == false)
	{
		return false;
	}

	switch (nLstick)
	{
	case STICKTYPE_UP:
		return g_state.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return g_state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return g_state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return g_state.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}

bool GetRightStick(int nRstick)
{
	if (g_bConnect == false)
	{
		return false;
	}

	switch (nRstick)
	{
	case STICKTYPE_UP:
		return g_state.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_RIGHT:
		return g_state.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_LEFT:
		return g_state.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	case STICKTYPE_DOWN:
		return g_state.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ? true : false;
		break;
	default:
		return false;
		break;
	}
}

void SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd)
{
	g_vibration.wLeftMotorSpeed = nLeftSpeed;
	g_vibration.wRightMotorSpeed = nRightSpeed;
	XInputSetState(0, &g_vibration);
	g_nCntVibration = nCntEnd;
	g_bVibration = true;
}