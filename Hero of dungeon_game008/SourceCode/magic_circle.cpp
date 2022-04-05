//================================================
//���@�w�̏���
//Author:KatoMizuki
//================================================
#include "magic_circle.h"
#include "manager.h"
#include "renderer.h"
#include "effect3D.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMagicCircle::CMagicCircle(int nPriority) :CObject3D(nPriority)
{
	m_rotateType = ROTATE_TYPE::NONE;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMagicCircle::~CMagicCircle()
{

}

//================================================
//����������
//================================================
HRESULT CMagicCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CObject3D::Init(pos,size);

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::MAGIC_CIRCLE);
	
	//�ϐ�������
	m_rotateType = ROTATE_TYPE::Y;

	//���C�e�B���O�𖳌��ɂ���
	SetLighting(false);
	//���e�X�g��L���ɂ���
	SetAlphaTest(true);

	return S_OK;
}

//================================================
//�I������
//================================================
void CMagicCircle::Uninit(void)
{
	CObject3D::Uninit();
}

//================================================
//�X�V����
//================================================
void CMagicCircle::Update(void)
{
	switch (m_rotateType)
	{
	case CMagicCircle::ROTATE_TYPE::NONE:
		break;
	case CMagicCircle::ROTATE_TYPE::X:
		//��]������
		m_rot.x += 0.01f;

		if (m_rot.x >= D3DX_PI)
		{
			m_rot.x -= D3DX_PI * 2.0f;
		}
		break;
	case CMagicCircle::ROTATE_TYPE::Y:
		//��]������
		m_rot.y += 0.01f;

		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		break;
	case CMagicCircle::ROTATE_TYPE::Z:
		//��]������
		m_rot.z += 0.01f;

		if (m_rot.z >= D3DX_PI)
		{
			m_rot.z -= D3DX_PI * 2.0f;
		}
		break;
	default:
		break;
	}
}

//================================================
//�`�揈��
//================================================
void CMagicCircle::Draw(void)
{
	CObject3D::Draw();
}

//================================================
//��������
//================================================
CMagicCircle* CMagicCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot)
{
	//�C���X�^���X�̐���
	CMagicCircle *pMagicCircle = nullptr;
	if (pMagicCircle == nullptr)
	{
		pMagicCircle = new CMagicCircle();
		if (pMagicCircle != nullptr)
		{
			pMagicCircle->m_rot = rot;
			pMagicCircle->Init(pos, size);
		}
	}
	return pMagicCircle;
}
