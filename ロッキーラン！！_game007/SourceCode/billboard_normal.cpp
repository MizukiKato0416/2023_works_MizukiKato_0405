//============================================================================
// �r���{�[�h���� [billboard.cpp]
// Author : KUSAKARI KAKERU
//=============================================================================
#include "renderer.h"
#include "billboard_normal.h"
#include "manager.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBillboardNormal::CBillboardNormal()
{
	
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CBillboardNormal::~CBillboardNormal()
{

}

//================================================
//����������
//================================================
HRESULT CBillboardNormal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �p�����N���X�̏���������
	CBillboard::Init(pos, size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBillboardNormal::Uninit(void)
{
	// �p�����N���X�̏I������
	CBillboard::Uninit();
}

//================================================
//�X�V����
//================================================
void CBillboardNormal::Update(void)
{

}

//================================================
//�`�揈��
//================================================
void CBillboardNormal::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAREF, 240);				//�A���t�@�l�̎Q�ƒl

	D3DXMATRIX mtxView;						//�r���[�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	//�v�Z�p�}�g���b�N�X
	D3DXMatrixIdentity(&m_mtxWorld);		//���[���h�}�g���b�N�X�̏�����

											//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�

													//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		2);											//�`�悷��v���~�e�B�u��

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);				//�A���t�@�l�̎Q�ƒl

																//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================================
//��������
//================================================
CBillboardNormal *CBillboardNormal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CBillboardNormal *pBillboardNormal = NULL;
	if (pBillboardNormal == NULL)
	{
		pBillboardNormal = new CBillboardNormal;
		if (pBillboardNormal != NULL)
		{
			pBillboardNormal->Init(pos, size); 
		}
	}
	return pBillboardNormal;
}