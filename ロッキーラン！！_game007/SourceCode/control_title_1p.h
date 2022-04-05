//=============================================================================
// �^�C�g��1P�摜�R���g���[������ [control_title_1p.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _CONTROL_TITLE_1P_H_
#define _CONTROL_TITLE_1P_H_

#include "control.h"

//================================================
//�}�N����`
//================================================
#define TITLE_1P_GRAVITY	(0.1f)		//�d��
#define TITLE_1P_RISE		(9.0f)		//�㏸��

//================================================
//�O���錾
//================================================
class CScene;

//*****************************************************************************
// �^�C�g��1P�摜�R���g���[���N���X
//*****************************************************************************
class CControlTitle1P : public CControl
{
public:
	CControlTitle1P();					// �R���X�g���N�^
	~CControlTitle1P();					// �f�X�g���N�^
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(CScene *pScene);		// �X�V����
	static CControlTitle1P *Create();	// ��������
};

#endif	//_CONTROL_TITLE_1P_H_