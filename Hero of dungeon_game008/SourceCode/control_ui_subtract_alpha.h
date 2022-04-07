//=============================================================================
// �q�b�g�G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_UI_SUBTRACT_ALPHA_H_
#define _CONTROL_UI_SUBTRACT_ALPHA_H_
#include "control.h"

//�O���錾
class CObject;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CControlUiSubtractAlpha : public CControl
{
public:
	//�����o�֐�
	CControlUiSubtractAlpha();			//�R���X�g���N�^	
	~CControlUiSubtractAlpha();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlUiSubtractAlpha *Create(CObject *pObject, float fSubtractAlpha, int nDelay);

private:
	float m_fSubtractAlpha;		//���l���Z�l
	int m_nDelay;				//�f�B���C
	int m_nDelayCounter;		//�f�B���C�̃J�E���^�[
};

#endif	//_CONTROL_UI_SUBTRACT_ALPHA_H_