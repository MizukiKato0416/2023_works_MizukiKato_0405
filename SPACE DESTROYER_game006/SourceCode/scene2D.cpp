//================================================
//2D�|���S������
//Authore:��������
//================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScene2D::CScene2D(int nPriority):CScene(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CScene2D::~CScene2D()
{

}

//================================================
//����������
//================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//�ϐ�������
	m_pos = pos;
	m_size = size;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CScene2D::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	pDevice->SetTexture(0, m_pTexture);	//�e�N�X�`���̐ݒ�

												//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�`����J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}

//================================================
//��������
//================================================
CScene2D* CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nPriolity)
{
	//�C���X�^���X�̐���
	CScene2D *pScene2D = NULL;
	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D(nPriolity);
		if (pScene2D != NULL)
		{
			pScene2D->Init(pos, size);
		}
	}
	return pScene2D;
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	VERTEX_2D *pVtx;	// ���_���
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y - m_size.y / 2.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x / 2.0f, m_pos.y + m_size.y / 2.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, D3DXVECTOR3 size, float fRot)
{
	m_pos = pos;
	m_size = size;
	CScene::SetPos(m_pos);
	CScene::SetSize(m_size);

	//�p�x�����߂�
	float fTanR = atan2f(m_size.y / 2.0f, m_size.x / 2.0f);
	//���a�����߂�
	float fCircleR = sqrtf((float)pow(m_size.x / 2.0f, 2.0f) + (float)pow(m_size.y / 2.0f, 2.0f));

	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fCircleR * cosf(fTanR - fRot), m_pos.y - fCircleR * sinf(fTanR - fRot), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fCircleR * cosf(fTanR + fRot), m_pos.y - fCircleR * sinf(fTanR + fRot), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fCircleR * cosf(fTanR + fRot), m_pos.y + fCircleR * sinf(fTanR + fRot), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fCircleR * cosf(fTanR - fRot), m_pos.y + fCircleR * sinf(fTanR - fRot), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CScene2D::SetTex(int nPattern, int nMaxPattern)
{
	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((1.0f / nMaxPattern) * nPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((1.0f / nMaxPattern) + (1.0f / nMaxPattern) * nPattern, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`���ݒ菈��
//================================================
void CScene2D::SetTex(float fMoveTexU, float fMoveTexV)
{
	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[1].tex = D3DXVECTOR2(1.0f + fMoveTexU, 0.0f + fMoveTexV);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fMoveTexU, 1.0f + fMoveTexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + fMoveTexU, 1.0f + fMoveTexV);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CScene2D::SetCol(D3DCOLORVALUE col)
{
	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[1].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[2].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);
	pVtx[3].col = D3DCOLOR_RGBA((int)col.r, (int)col.g, (int)col.b, (int)col.a);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�J���[�ݒ菈��
//================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//4���_�ݒ菈��
//================================================
void CScene2D::SetVtx(D3DXVECTOR3 pos, D3DXVECTOR3 vtx0, D3DXVECTOR3 vtx1, D3DXVECTOR3 vtx2, D3DXVECTOR3 vtx3)
{
	m_pos = pos;

	VERTEX_2D *pVtx;	// ���_���
						//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = vtx0;
	pVtx[1].pos = vtx1;
	pVtx[2].pos = vtx2;
	pVtx[3].pos = vtx3;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}
