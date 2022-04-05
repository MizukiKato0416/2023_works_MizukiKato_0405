//================================================
//�w�i����
//Authore:��������
//================================================
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "bg.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_BG_POLYGON] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBg::CBg(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		m_apScene2D[nCntPolygon] = NULL;
		m_fPosTexV[nCntPolygon] = 0.0f;
	}
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CBg::~CBg()
{

}

//================================================
//����������
//================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		//�|���S���̐���
		m_apScene2D[nCntPolygon] = new CScene2D(PRIORITY_BG_0);
		m_apScene2D[nCntPolygon]->Init(pos, size);

		//�e�N�X�`���̊��蓖��
		m_apScene2D[nCntPolygon]->BindTexture(m_pTexture[nCntPolygon]);

		//�e�N�X�`��V���W
		m_fPosTexV[nCntPolygon] = 0.0f;
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CBg::Uninit(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		if (m_apScene2D[nCntPolygon] != NULL)
		{
			m_apScene2D[nCntPolygon]->Uninit();
			m_apScene2D[nCntPolygon] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CBg::Update(void)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_BG_POLYGON; nCntPolygon++)
	{
		//�w�i�ɂ���ē���������ς���
		if (nCntPolygon == 0)
		{
			m_fPosTexV[nCntPolygon] -= 0.0005f;
		}
		else if (nCntPolygon == 1)
		{
			m_fPosTexV[nCntPolygon] -= 0.001f;
		}
		else if (nCntPolygon == 2)
		{
			m_fPosTexV[nCntPolygon] -= 0.002f;
		}

		if (m_fPosTexV[nCntPolygon] < -1.0f)
		{
			m_fPosTexV[nCntPolygon] += 0.0f;
		}

		m_apScene2D[nCntPolygon]->SetTex(0.0f, m_fPosTexV[nCntPolygon]);
	}
}

//================================================
//�`�揈��
//================================================
void CBg::Draw(void)
{
	
}

//================================================
//��������
//================================================
CBg* CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CBg *pBg = NULL;
	if (pBg == NULL)
	{
		pBg = new CBg;
		if (pBg != NULL)
		{
			//�e�N�X�`�����蓖��
			m_pTexture[0] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_00);
			m_pTexture[1] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_01);
			m_pTexture[2] = CManager::GetTexture()->GetTexture(CTexture::TYPE_BG_02);
			pBg->Init(pos, size);
		}
	}
	return pBg;
}