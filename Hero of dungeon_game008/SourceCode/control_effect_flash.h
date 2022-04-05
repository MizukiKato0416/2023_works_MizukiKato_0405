//=============================================================================
// �M���G�t�F�N�g�̓����̏���
// Author:KatoMizuki
//=============================================================================
#ifndef _CONTROL_EFFECT_FLASH_H_
#define _CONTROL_EFFECT_FLASH_H_
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
class CControlEffectFlash : public CControl
{
public:
	//�����o�֐�
	CControlEffectFlash();			//�R���X�g���N�^	
	~CControlEffectFlash();			//�f�X�g���N�^	

	HRESULT Init(CObject *pObject);
	void Uninit(void);					
	void Update(CObject *pObject);		
	static CControlEffectFlash *Create(CObject *pObject);

private:
	//���
	enum class CONTROL_EFFECT_FLASH_STATE
	{
		NONE = 0,
		ADD_SIZE_SMALL,		//�T�C�Y��傫������(�ω��l��)
		SUBTRACTION_SIZE,	//�T�C�Y������������
		ADD_SIZE_BIG,		//�T�C�Y��傫������(�ω��l��)
		MAX
	};

	CONTROL_EFFECT_FLASH_STATE m_state;		//���
	int m_nCounter;							//��Ԃ�؂�ւ���܂ł̎���
};

#endif	//_CONTROL_EFFECT_FLASH_H_