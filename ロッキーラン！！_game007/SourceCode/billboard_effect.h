//============================================================================
// �r���{�[�h�̃G�t�F�N�g���� [billboard_effect.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _BILLBOARD_EFFECT_H_
#define _BILLBOARD_EFFECT_H_

#include "billboard.h"

//================================================
//�N���X�̒�`
//================================================
class CBillboardEffect : public CBillboard
{
public:
	CBillboardEffect();							//�R���X�g���N�^
	~CBillboardEffect();						//�f�X�g���N�^

												//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboardEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
};

#endif // _BILLBOARD_EFFECT_H_