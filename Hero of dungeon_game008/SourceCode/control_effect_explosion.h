//=============================================================================
// �����G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_EXPLOSION_H_
#define _CONTROL_EFFECT_EXPLOSION_H_
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
class CControlEffectExplosion : public CControl
{
public:
	//�����o�֐�
	CControlEffectExplosion();			//�R���X�g���N�^	
	~CControlEffectExplosion();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectExplosion *Create(CObject *pObject);

private:
	
};

#endif	//_CONTROL_EFFECT_EXPLOSION_H_