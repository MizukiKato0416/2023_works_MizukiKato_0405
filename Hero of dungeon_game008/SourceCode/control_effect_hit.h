//=============================================================================
// �q�b�g�G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_HIT_H_
#define _CONTROL_EFFECT_HIT_H_
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
class CControlEffectHit : public CControl
{
public:
	//�����o�֐�
	CControlEffectHit();			//�R���X�g���N�^	
	~CControlEffectHit();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectHit *Create(CObject *pObject);

private:
};

#endif	//_CONTROL_EFFECT_HIT_H_