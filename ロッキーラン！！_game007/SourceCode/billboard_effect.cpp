//============================================================================
// �r���{�[�h�̃G�t�F�N�g���� [billboard_effect.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "renderer.h"
#include "billboard_effect.h"
#include "manager.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBillboardEffect::CBillboardEffect()
{

}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CBillboardEffect::~CBillboardEffect()
{

}

//================================================
//����������
//================================================
HRESULT CBillboardEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �p�����N���X�̏���������
	CBillboard::Init(pos, size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBillboardEffect::Uninit(void)
{
	// �p�����N���X�̏I������
	CBillboard::Uninit();
}

//================================================
//�X�V����
//================================================
void CBillboardEffect::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CBillboardEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	// �p�����N���X�̏I������
	CBillboard::Draw();

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���Z��������ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//��������
//================================================
CBillboardEffect *CBillboardEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CBillboardEffect *pBillboardEffect = NULL;
	if (pBillboardEffect == NULL)
	{
		pBillboardEffect = new CBillboardEffect;
		if (pBillboardEffect != NULL)
		{
			pBillboardEffect->m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_EFFECT);
			pBillboardEffect->BindTexture(pBillboardEffect->m_pTexture);
			pBillboardEffect->Init(pos, size);
		}
	}
	return pBillboardEffect;
}