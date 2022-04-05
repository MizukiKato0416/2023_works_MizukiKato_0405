//=============================================================================
// �Q�[���J�E���g�_�E�������R���g���[������ [control_game_countdown.h]
// Author :��������
//=============================================================================
#ifndef _CONTROL_GAME_COUNTDOWN_H_
#define _CONTROL_GAME_COUNTDOWN_H_

#include "control.h"

//�O���錾
class CScene;

//*****************************************************************************
// �Q�[���J�E���g�_�E���R���g���[���N���X
//*****************************************************************************
class CControlGameCountdown : public CControl
{
public:
	CControlGameCountdown();					// �R���X�g���N�^
	~CControlGameCountdown();					// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlGameCountdown *Create();	// ��������

private:
	typedef enum
	{
		COUNTDOWN_03=0,
		COUNTDOWN_02,
		COUNTDOWN_01,
		COUNTDOUN_MAX
	} COUNTDOWN;

	float m_fMaxMove;						// �ړ��ʂ̍ő�l
	int m_nCount;							// �J�E���g
	D3DXCOLOR m_col;						//�|���S���̐F
};

#endif	//_CONTROL_TITLE_LOGO_H_