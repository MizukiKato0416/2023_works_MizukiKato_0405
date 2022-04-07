//=============================================================================
// �K�[�h�G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_GUARD_H_
#define _CONTROL_EFFECT_GUARD_H_
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
class CControlEffectGuard : public CControl
{
public:
	//�����o�֐�
	CControlEffectGuard();			//�R���X�g���N�^	
	~CControlEffectGuard();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectGuard *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_GUARD_H_