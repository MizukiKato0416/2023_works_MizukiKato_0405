//================================================
//��������
//Authore:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "explosion.h"
#include "renderer.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CExplosion::CExplosion(int nPriority) :CScene2D(nPriority)
{
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CExplosion::~CExplosion()
{

}

//================================================
//����������
//================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_EXPLOSION);

	//�e�N�X�`�����W�X�V
	SetTex(m_nPatternAnim, MAX_PATTERN);

	return S_OK;
}

//================================================
//�I������
//================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CExplosion::Update(void)
{
	//�J�E���^�[�X�V
	m_nCounterAnim++;
	if (m_nCounterAnim % PATTERN_FRAME == 0)
	{
		//�p�^�[��No�X�V
		m_nPatternAnim++;
		//�e�N�X�`�����W�X�V
		SetTex(m_nPatternAnim , MAX_PATTERN);

		if (m_nPatternAnim > MAX_PATTERN)
		{
			Uninit();
			return;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CExplosion *pExplosion = NULL;
	if (pExplosion == NULL)
	{
		pExplosion = new CExplosion;
		if (pExplosion != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_EXPLOSION);
			pExplosion->Init(pos, size);
			pExplosion->BindTexture(m_pTexture);
		}
	}
	return pExplosion;
}
