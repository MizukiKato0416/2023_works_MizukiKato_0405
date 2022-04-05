#//=============================================================================
// �^�C�g�����S�R���g���[������ [control_title_logo.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_LOGO_H_
#define _CONTROL_TITLE_LOGO_H_

#include "control.h"

//�O���錾
class CScene;

//*****************************************************************************
// �^�C�g�����S�R���g���[���N���X
//*****************************************************************************
class CControlTitleLogo : public CControl
{
public:
	CControlTitleLogo();					// �R���X�g���N�^
	~CControlTitleLogo();					// �f�X�g���N�^
	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(CScene *pScene);			// �X�V����
	static CControlTitleLogo *Create();	// ��������

private:
	float m_fMaxMove;						// �ړ��ʂ̍ő�l
};

#endif	//_CONTROL_TITLE_LOGO_H_