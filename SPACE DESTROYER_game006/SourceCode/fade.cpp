//================================================
//�t�F�[�h����
//Authore:��������
//================================================
#include "fade.h"
#include "scene.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CFade::CFade(int nPriority) :CScene2D(nPriority)
{
	m_fade = FADE_NONE;								//�t�F�[�h�̏��
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�t�F�[�h�̐F
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CFade::~CFade()
{

}

//================================================
//����������
//================================================
HRESULT CFade::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_fade = FADE_IN;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CScene2D::Init(pos, size);

	return S_OK;
}

//================================================
//�I������
//================================================
void CFade::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CFade::Update(void)
{
	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_color.a -= 0.05f;
			if (m_color.a <= 0.0f)
			{
				m_color.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{
			m_color.a += 0.05f;
			if (m_color.a >= 1.0f)
			{
				m_color.a = 1.0f;
				m_fade = FADE_IN;

				//���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
		CScene2D::SetCol(m_color);
	}
}

//================================================
//�`�揈��
//================================================
void CFade::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CFade *CFade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CManager::MODE modeNext)
{
	//�C���X�^���X�̐���
	CFade *pFade = NULL;
	if (pFade == NULL)
	{
		pFade = new CFade;
		if (pFade != NULL)
		{
			pFade->Init(pos, size);
			pFade->m_fade = FADE_OUT;
			pFade->m_modeNext = modeNext;				//���̉��(���[�h)
			pFade->m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	return pFade;
}

//================================================
//�ݒ菈��
//================================================
void CFade::SetFade(CManager::MODE modeNext)
{
	m_fade = FADE_OUT;
	m_modeNext = modeNext;
	m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//================================================
//�擾����
//================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}