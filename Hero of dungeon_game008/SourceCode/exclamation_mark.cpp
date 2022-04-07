//================================================
//�r�b�N���}�[�N����
//Author:KatoMizuki
//================================================
#include "exclamation_mark.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//================================================
//�}�N����`
//================================================


//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CExclamationMark::CExclamationMark(int nPriority) :CBillboard(nPriority)
{
	m_addSize = { 0.0f, 0.0f, 0.0f };
	m_size = { 0.0f, 0.0f, 0.0f };
	m_pObject = nullptr;
	m_nLife = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CExclamationMark::~CExclamationMark()
{

}

//================================================
//����������
//================================================
HRESULT CExclamationMark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::EXCLAMATION_MARK);

	//���e�X�g���s���ݒ�
	SetAlphaTest(true);
	//���C�e�B���O�𖳌��ɂ���
	SetLighting(false);

	return S_OK;
}

//================================================
//�I������
//================================================
void CExclamationMark::Uninit(void)
{
	CBillboard::Uninit();
}

//================================================
//�X�V����
//================================================
void CExclamationMark::Update(void)
{
	//���������炷
	m_nLife--;

	//������0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		//0�ɂ���
		m_nLife = 0;
		//����
		Uninit();
		return;
	}

	//�ʒu�ƃT�C�Y���擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	//�Ώۂ̃I�u�W�F�N�g�̈ʒu���擾���Č��݂̈ʒu�ɑ��
	D3DXVECTOR3 objectPos = m_pObject->GetPos();
	pos.x = objectPos.x;
	pos.z = objectPos.z;

	//�T�C�Y�����Z
	size += m_addSize;

	//����̒l�ȏ�ɂȂ�����
	if (size.x >= m_size.x)
	{
		//����̒l�ɂ���
		size.x = m_size.x;
	}
	if (size.y >= m_size.y)
	{
		//����̒l�ɂ���
		size.y = m_size.y;
	}

	//�ʒu�̐ݒ�
	SetPos(pos,size);
}

//================================================
//�`�揈��
//================================================
void CExclamationMark::Draw(void)
{
	CBillboard::Draw();
}

//================================================
//��������
//================================================
CExclamationMark* CExclamationMark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 initSize, D3DXVECTOR3 addSize, CObject *pObject, int nLife)
{
	//�C���X�^���X�̐���
	CExclamationMark *pExclamationMark = nullptr;
	if (pExclamationMark == nullptr)
	{
		pExclamationMark = new CExclamationMark();
		if (pExclamationMark != nullptr)
		{
			pExclamationMark->m_size = size;
			pExclamationMark->m_addSize = addSize;
			pExclamationMark->m_pObject = pObject;
			pExclamationMark->m_nLife = nLife;
			pExclamationMark->Init(pos, initSize);
			pExclamationMark->m_pTexture = CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_EXCLAMATION_MARK");
		}
	}
	return pExclamationMark;
}
