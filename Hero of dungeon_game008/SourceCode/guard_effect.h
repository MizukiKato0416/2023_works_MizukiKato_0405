//===========================================
//�K�[�h�G�t�F�N�g����
//Author:KatoMizuki
//===========================================
#ifndef _GUARD_EFFECT_H_
#define _GUARD_EFFECT_H_
#include "object.h"

//�O���錾
class CObject3D;

//================================================
//�}�N����`
//================================================
#define GUARD_EFFECT_POS			(10.0f)		//�K�[�h�G�t�F�N�g�̐����ʒu�����l
#define GUARD_EFFECT_POS_Y			(30.0f)		//�K�[�h�G�t�F�N�g�̐����ʒu�����lY
#define GUARD_EFFECT_SIZE			(1.0f)		//�K�[�h�G�t�F�N�g�̐��������T�C�Y

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGuardEffect : public CObject
{
public:
	//�����o�֐�
	CGuardEffect(int nPriority = PRIORITY_EFFECT3D);		//�R���X�g���N�^
	~CGuardEffect();										//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGuardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

private:
	CObject3D *m_pObject3D;			//Object3D�̃|�C���^
	D3DXVECTOR3 m_rot;				//����
};

#endif // !_GUARD_EFFECT_H_