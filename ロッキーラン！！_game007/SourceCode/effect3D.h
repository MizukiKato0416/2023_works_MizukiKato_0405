//============================================================================
// 3D�G�t�F�N�g���� [3Deffect.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _3D_EFFECT_H_
#define _3D_EFFECT_H_

#include "billboard.h"

//================================================
// �}�N����`
//================================================
#define EFFECT_SHRINK_SIZE	(0.2f)	// �k��������T�C�Y

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CEffect3D : public CBillboard
{
public:
	CEffect3D(int nPriority = PRIORITY_PLAYER);	//�R���X�g���N�^
	~CEffect3D();								//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int nPriolty);

private:
	int m_nLife;							// ����
};

#endif // _3D_EFFECT_H_