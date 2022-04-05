//=============================================================================
// ���G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_FIRE_H_
#define _CONTROL_EFFECT_FIRE_H_
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
class CControlEffectFire : public CControl
{
public:
	//�����o�֐�
	CControlEffectFire();			//�R���X�g���N�^	
	~CControlEffectFire();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectFire *Create(CObject *pObject);

private:
	int m_nTexAnimCounter;		//�e�N�X�`���A�j���[�V�����̃J�E���^�[
	int m_nTexAnimNum;			//�e�N�X�`���A�j���[�V�����̔ԍ�
};

#endif	//_CONTROL_EFFECT_FIRE_H_