//================================================
//���C�t����
//Authore:��������
//================================================
#include "renderer.h"
#include "polygon.h"
#include "manager.h"
#include "life.h"
#include "texture.h"
#include "game01.h"
#include "player.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CLife::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CLife::CLife(int nPriority) :CScene(nPriority)
{
	for (int nCntPolygon = 0; nCntPolygon < MAX_LIFE_POLYGON; nCntPolygon++)
	{
		m_apPolygon[nCntPolygon] = NULL;
	}

	m_nLife = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CLife::~CLife()
{

}

//================================================
//����������
//================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nLife = MAX_PLAYER_INIT_LIFE;
	m_pos = pos;

	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		m_apPolygon[nCntPolygon] = CPolygon::Create(D3DXVECTOR3(pos.x - (LIFE_POLYGON_WIDTH * m_nLife / 2) + (LIFE_POLYGON_WIDTH * nCntPolygon) + (LIFE_POLYGON_WIDTH / 2.0f), pos.y, 0.0f),
												D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CLife::Uninit(void)
{
	//�i���o�[�̔j��
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Uninit();
			delete m_apPolygon[nCntPolygon];
			m_apPolygon[nCntPolygon] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CLife::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CLife::Draw(void)
{
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] != NULL)
		{
			m_apPolygon[nCntPolygon]->Draw();
		}
	}
}

//================================================
//��������
//================================================
CLife* CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CLife *pLife = NULL;
	if (pLife == NULL)
	{
		pLife = new CLife;
		if (pLife != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PLAYER_LIFE);
			pLife->Init(pos, size);
			CGame01::GetPolygon()->BindTexture(m_pTexture);
		}
	}
	return pLife;
}

//================================================
//���C�t�擾����
//================================================
int CLife::GetLife(void)
{
	return m_nLife;
}

//================================================
//���C�t�ݒ菈��
//================================================
void CLife::SetLife(int nLife)
{
	m_nLife = nLife;
}

//================================================
//���C�t���Z����
//================================================
void CLife::AddLife(int nValue)
{
	//���C�t�̉��Z
	m_nLife += nValue;

	//���Z�������̃��C�t�|���S������
	for (int nCntPolygon = 0; nCntPolygon < m_nLife; nCntPolygon++)
	{
		if (m_apPolygon[nCntPolygon] == NULL)
		{
			m_apPolygon[nCntPolygon] = CPolygon::Create(D3DXVECTOR3(m_pos.x - (LIFE_POLYGON_WIDTH * START_LIFE_POLYGON / 2) + (LIFE_POLYGON_WIDTH * nCntPolygon) + (LIFE_POLYGON_WIDTH / 2.0f), m_pos.y, 0.0f),
														D3DXVECTOR3(LIFE_POLYGON_WIDTH, LIFE_POLYGON_HEIGHT, 0.0f));
		}
	}
}

//================================================
//���C�t���Z����
//================================================
void CLife::SubtractLife(int nValue)
{
	//���Z�������̃��C�t�|���S���j��
	if (m_nLife > 0)
	{
		for (int nCntPolygon = m_nLife - 1; nCntPolygon > m_nLife - 1 - nValue; nCntPolygon--)
		{
			m_apPolygon[nCntPolygon]->Uninit();
			delete m_apPolygon[nCntPolygon];
			m_apPolygon[nCntPolygon] = NULL;
		}
	}
	else
	{
		m_nLife = 0;
	}

	//���C�t�̌��Z
	m_nLife -= nValue;
}