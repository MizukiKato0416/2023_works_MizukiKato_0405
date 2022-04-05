//============================================================================
// �ʏ�̃r���{�[�h���� [billboard_normal.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_NORMAL_H_
#define _BILLBOARD_NORMAL_H_

#include "billboard.h"

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CBillboardNormal : public CBillboard
{
public:
	CBillboardNormal();							//�R���X�g���N�^
	~CBillboardNormal();						//�f�X�g���N�^

												//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboardNormal *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
};

#endif // _BILLBOARD_NORMAL_H_