//================================================
//�e����
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "effect.h"
#include "texture.h"
#include "boss.h"
#include "game01.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEffect::CEffect(int nPriority) :CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col.r = 0.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 0.0f;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEffect::~CEffect()
{

}

//================================================
//����������
//================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col)
{
	m_col = col;
	m_size = size;
	m_move = move;

	CScene2D::Init(pos, size);

	//�J���[���f
	CScene2D::SetCol(m_col);
	return S_OK;
}

//================================================
//�I������
//================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CEffect::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�ړ��ʔ��f
	pos += m_move;

	//�����̏���
	MoveType();

	//�ʒu���f
	CScene2D::SetPos(pos, m_size);
	//�J���[���f
	CScene2D::SetCol(m_col);

	if (m_size.x <= 0.0f || m_size.y <= 0.0f || m_col.a <= 0.0f)
	{
		Uninit();
		return;
	}
}

//================================================
//�`�揈��
//================================================
void CEffect::Draw(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//���̐ݒ�ɖ߂�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//================================================
//��������
//================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, D3DCOLORVALUE col, EFFECT_TYPE type)
{
	//�C���X�^���X�̐���
	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{
		pEffect = new CEffect;
		if (pEffect != NULL)
		{
			pEffect->m_type = type;
			pEffect->Init(pos, size, move, col);
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_EFFECT);
			pEffect->BindTexture(m_pTexture);
		}
	}
	return pEffect;
}

//================================================
////�^�C�v�ɂ�铮��
//================================================
void CEffect::MoveType(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�{�X�ƒe�̊p�x�v�Z�p
	float fTanR = 0.0f;
	//�{�X�̃|�C���^�[
	CBoss *pBoss = CGame01::GetBoss();
	//�{�X�̈ʒu�ۑ��p
	D3DXVECTOR3 posBoss = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�{�X�Ƃ̋���
	float fDiffer = 0;

	switch (m_type)
	{
	case EFFECT_TYPE_NONE:
		break;
	case EFFECT_TYPE_NORMAL:
		//�T�C�Y������������
		m_size.x -= 2.5f;
		m_size.y -= 2.5f;
		//�J���[�𔖂�����
		m_col.a -= 20.0f;
		break;
	case EFFECT_TYPE_BOSS_LASER:
		//�T�C�Y��傫������
		m_size.x += 0.1f;
		m_size.y += 0.1f;
		//�{�X�̈ʒu���擾
		posBoss = pBoss->GetBodyPos();
		//y���W�𒲐�
		posBoss.y += 150.0f;
		//�{�X�Ƃ̋���
		fDiffer = sqrtf(((posBoss.x - pos.x) * (posBoss.x - pos.x)) + ((posBoss.y - pos.y) * (posBoss.y - pos.y)));
		//�{�X�ƃG�t�F�N�g�̊p�x���v�Z
		fTanR = atan2f(posBoss.y - pos.y, posBoss.x - pos.x);
		//�{�X�Ɍ������čs���悤�ړ��ʂ��v�Z
		m_move = D3DXVECTOR3(cosf(fTanR) * 2.0f, sinf(fTanR) * 2.0f, 0.0f);
		if (fDiffer <= 20.0f)
		{
			m_col.a = 0.0f;
		}
		break;
	default:
		break;
	}
}