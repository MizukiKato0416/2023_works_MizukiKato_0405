//===========================================
//�r�b�N���}�[�N����
//Author:KatoMizuki
//===========================================
#ifndef _EXCLAMATION_MARK_H_
#define _EXCLAMATION_MARK_H_
#include "billboard.h"

//�O���錾
class CControl;

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CExclamationMark : public CBillboard
{
public:
	CExclamationMark(int nPriority = PRIORITY_EXCLAMATION_MARK);	//�R���X�g���N�^
	~CExclamationMark();											//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExclamationMark *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 initSize, D3DXVECTOR3 addSize, CObject *pObject, int nLife);

private:
	D3DXVECTOR3 m_size;		//�T�C�Y
	D3DXVECTOR3 m_addSize;	//�T�C�Y���Z�l
	CObject *m_pObject;		//�Ώۂ̃|�C���^
	int m_nLife;			//����
};

#endif // !_EXCLAMATION_MARK_H_