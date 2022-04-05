//===========================================
//�^�C�g������
//Author:KatoMizuki
//===========================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "object.h"

//�O���錾
class CObject2D;

//================================================
//�}�N����`
//================================================

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CTitle : public CObject
{
public:
	CTitle(int nPriority = PRIORITY_NONE);		//�R���X�g���N�^
	~CTitle();									//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nTitleCounter;				//���U���g�ɍs���܂ł̂܂ł̎���
};

#endif // !_TITLE_H_