//============================================================================
// �V���h�E���� [shadow.h]
// Author : KUSAKARI KAKERU
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "scene3D.h"

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CShadow : public CScene3D
{
public:
	CShadow();						//�R���X�g���N�^
	~CShadow();						//�f�X�g���N�^

									//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);
	void SetShadow(D3DXVECTOR3 pos, float fRange);	// �e�̐ݒ菈��
	void SetUseShadow(bool bUse);					// �g�p��Ԃ̐ݒ菈��

private:
	//�����o�֐�
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_move;						// �|���S���̈ړ���
	D3DXVECTOR3 m_Defaultsize;				// �f�t�H���g�̉e�̃T�C�Y
	bool m_bUse;							// �g�p���Ă��邩�ǂ���
};

#endif // _SHADOW_H_