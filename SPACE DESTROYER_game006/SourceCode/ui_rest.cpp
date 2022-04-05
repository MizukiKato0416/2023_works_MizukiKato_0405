//================================================
//�����̂Ȃ�UI�̏���
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "ui_rest.h"
#include "renderer.h"
#include "texture.h"

#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CUiRest::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CUiRest::CUiRest()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = UI_REST_TYPE_NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CUiRest::~CUiRest()
{

}

//================================================
//����������
//================================================
HRESULT CUiRest::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	CUi::Init(pos, size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CUiRest::Uninit(void)
{
	CUi::Uninit();
}

//================================================
//�X�V����
//================================================
void CUiRest::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CUiRest::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CUiRest *CUiRest::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CUiRest::UI_REST_TYPE type)
{
	//�C���X�^���X�̐���
	CUiRest *pUiRest = NULL;
	if (pUiRest == NULL)
	{
		pUiRest = new CUiRest;
		if (pUiRest != NULL)
		{
			pUiRest->Init(pos, size);
			switch (type)
			{
			case UI_REST_TYPE_MENU_BAND:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_MENU_BAND);
				break;
			case UI_REST_TYPE_PAUSE:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PAUSE);
				break;
			case UI_REST_TYPE_DAMAGE_MASK:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_DAMAGE_MASK);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_000:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_000);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_001:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_001);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_002:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_002);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_003:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_003);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_004:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_004);
				break;
			case UI_REST_TYPE_TUTORIAL_EXPLANATION_005:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_TUTORIAL_EXPLANATION_005);
				break;
			case UI_REST_TYPE_GAME_CLEAR:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_GAME_CLEAR);
				break;
			case UI_REST_TYPE_GAME_OVER:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_GAME_OVER);
				break;
			default:
				break;
			}
			pUiRest->BindTexture(m_pTexture);
			pUiRest->m_nType = type;
		}
	}
	return pUiRest;
}