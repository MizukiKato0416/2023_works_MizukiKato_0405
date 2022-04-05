//===========================================
//�p�b�h���͏���
//Authore:��������
//===========================================
#ifndef _INPUT_PAD_X_H_
#define _INPUT_PAD_X_H_
#include "input.h"

//================================================
//�}�N����`
//================================================
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔


//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CInputPadX : public CInput
{
public:
	typedef enum
	{
		TRIGGERTYPE_RIGHT = 0,
		TRIGGERTYPE_LEFT,
		TRIGGERTYPE_MAX
	} TRIGGERTYPE;
	typedef enum
	{
		STICKTYPE_UP = 0,
		STICKTYPE_RIGHT,
		STICKTYPE_LEFT,
		STICKTYPE_DOWN,
		STICKTYPE_MAX
	} STICKTYPE;

	CInputPadX();			//�R���X�g���N�^
	~CInputPadX();			//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetButtonPress(int nButton);
	bool GetButtonTrigger(int nButton);
	bool GetTriggerPress(int nTrigger);
	bool GetTriggerTrigger(int nTrigger);
	bool GetLeftStick(int nLstick);
	bool GetLeftStickTrigger(int nLstick);
	bool GetLeftStickRelease(int nLstick);
	bool GetRightStick(int nRstick);
	void SetVibration(int nLeftSpeed, int nRightSpeed, int nCntEnd);

private:
	XINPUT_STATE m_state;
	XINPUT_STATE m_stateLast;
	XINPUT_VIBRATION m_vibration;
	bool m_bConnect;
	int m_nCntVibration;
	bool m_bVibration;
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_INPUT_PAD_X_H_