//===========================================
//�`���[�g���A������
//Author:KatoMizuki
//===========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "object.h"

//�O���錾
class CObject2D;

//================================================
//�}�N����`
//================================================
#define TUTORIAL_MAX_TYPE		(2)		//�`���[�g���A���̎��

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTutorial : public CObject
{
public:
	CTutorial(int nPriority = PRIORITY_NONE);		//�R���X�g���N�^
	~CTutorial();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CObject2D *m_pObject2D[TUTORIAL_MAX_TYPE];	//object2D�̃|�C���^
};

#endif // !_TUTORIAL_H_