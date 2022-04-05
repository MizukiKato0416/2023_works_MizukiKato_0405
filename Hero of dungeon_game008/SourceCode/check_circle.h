//===========================================
//�`�F�b�N�|�C���g���@�w����
//Author:KatoMizuki
//===========================================
#ifndef _CHECK_CIRCLE_H_
#define _CHECK_CIRCLE_H_

#include "magic_circle.h"

//�O���錾
class CObject2D;
class CGauge;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CCheckCircle : public CMagicCircle
{
public:
	CCheckCircle(int nPriority = PRIORITY_CHECK_CIRCLE);		//�R���X�g���N�^
	~CCheckCircle();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCheckCircle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	bool CollisionPlayer(void);			//�v���C���[�Ƃ̓����蔻��

private:
	int m_nEffectCounter;			//�G�t�F�N�g���o���p�x�̃J�E���^�[
	CObject2D *m_pMask;				//�I�u�W�F�N�g2D�̃|�C���^(�}�X�N�p)
	CObject2D *m_pGaugeFrame;		//�I�u�W�F�N�g2D�̃|�C���^(�Q�[�W�̃t���[���p)
	CGauge *m_pGauge;				//�Q�[�W�̃|�C���^
};

#endif // !_CHECK_CIRCLE_H_