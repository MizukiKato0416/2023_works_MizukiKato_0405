//============================================================================
// �V���h�E���� [shadow.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "shadow.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//================================================
// �ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CShadow::m_pTexture = NULL;	//���L�e�N�X�`���̃|�C���^

//================================================
// �f�t�H���g�R���X�g���N�^
//================================================
CShadow::CShadow()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUse = false;
}

//================================================
// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
// �f�X�g���N�^
//================================================
CShadow::~CShadow()
{

}

//================================================
// ����������
//================================================
HRESULT CShadow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�ϐ��̏�����
	m_pos = pos;
	m_size = size;
	m_Defaultsize = size;
	m_bUse = false;

	// �p�����N���X�̏���������
	CScene3D::Init(pos, size);

	return S_OK;
}

//================================================
// �I������
//================================================
void CShadow::Uninit(void)
{
	// �p�����N���X�̏I������
	CScene3D::Uninit();
}

//================================================
// �X�V����
//================================================
void CShadow::Update(void)
{
	
}

//================================================
// �`�揈��
//================================================
void CShadow::Draw(void)
{
	//�g�p���Ă��鎞�̂ݕ`�悳����
	if (m_bUse == true)
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

		// �p�����N���X�̕`�揈��
		CScene3D::Draw();

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
}

//================================================
// ��������
//================================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CShadow *pShadow = NULL;
	if (pShadow == NULL)
	{
		pShadow = new CShadow;
		if (pShadow != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TEX_TYPE_EFFECT);
			pShadow->m_rot = rot;
			pShadow->Init(pos, size);
			pShadow->BindTexture(m_pTexture);
		}
	}
	return pShadow;
}

//================================================
// �ʒu�̐ݒ菈��
//================================================
void CShadow::SetShadow(D3DXVECTOR3 pos, float fRange)
{
	m_pos = pos;

	//�v���C���[�Ɖe�̈ʒu�̋����ɂ���ĉe��傫������
	m_size.x = m_Defaultsize.x + (fRange / 3.0f);
	m_size.z = m_Defaultsize.z + (fRange / 3.0f);

	//�v���C���[�Ɖe�̈ʒu�̋����ɂ���ĉe�𔖂�����
	CScene3D::SetCol(D3DXCOLOR(255.0f, 255.0f, 255.0f, 1.0f - (fRange / 75.0f)));

	//�ʒu�E�T�C�Y�ݒ菈��
	CScene3D::SetPos(m_pos, m_size);
}

//================================================
// �g�p��Ԃ̐ݒ菈��
//================================================
void CShadow::SetUseShadow(bool bUse)
{
	m_bUse = bUse;
}