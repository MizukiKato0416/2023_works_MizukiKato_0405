//=============================================================================
// �`�F�b�N�|�C���g�̃G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_CHECK_H_
#define _CONTROL_EFFECT_CHECK_H_
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
class CControlEffectCheck : public CControl
{
public:
	//�����o�֐�
	CControlEffectCheck();			//�R���X�g���N�^	
	~CControlEffectCheck();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectCheck *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_CHECK_H_