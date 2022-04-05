//=============================================================================
// ���G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_THUNDER_H_
#define _CONTROL_EFFECT_THUNDER_H_
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
class CControlEffectThunder : public CControl
{
public:
	//�����o�֐�
	CControlEffectThunder();			//�R���X�g���N�^	
	~CControlEffectThunder();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectThunder *Create(CObject *pObject);

private:
	int m_nDestroyCounter;				//������܂ł̎���
};

#endif	//_CONTROL_EFFECT_THUNDER_H_