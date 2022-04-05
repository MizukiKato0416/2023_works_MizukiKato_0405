//=============================================================================
// �W�����v��2D�A�j���[�V�������� [2Danimation_jump.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _2DANIMATION_JUMP_H_
#define _2DANIMATION_JUMP_H_

#include "billboard.h"

//================================================
// �}�N����`
//================================================
#define MAX_SMOKE_SPEED	(0.8f)	//�ړ����x�̍ő�l

//*****************************************************************************
// �W�����v��2D�A�j���[�V�����N���X
//*****************************************************************************
class C2DAnimationJump : public CBillboard
{
public:
	C2DAnimationJump();		// �R���X�g���N�^
	~C2DAnimationJump();	// �f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	static C2DAnimationJump *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, float fMaxSpeed);		//��������

private:
	int m_nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int m_nPatternAnim;		// �A�j���[�V�����p�^�[��
	int m_nLife;			// ����
	float m_fMaxSpeed;		// �ő�ړ���
};

#endif	//_2DANIMATION_JUMP_H_