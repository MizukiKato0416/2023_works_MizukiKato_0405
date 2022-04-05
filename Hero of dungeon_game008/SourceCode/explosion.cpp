//================================================
//�����̏���
//Author:KatoMizuki
//================================================
#include "explosion.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define EXPLOSION_MOVE_ROTATE			(float((rand() % 629 + -314)) / 100.0f)		//�ړ��������
#define EXPLOSION_SIZE_SUBTRACTION		(0.99f)										//�T�C�Y���Z�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CExplosion::CExplosion(int nPriority) :CObject(nPriority)
{
	m_pEffect3D.clear();
	m_fRotX.clear();
	m_fRotY.clear();
	m_fInitMove.clear();
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nNumEffect = 0;
	m_fGravity = 0.0f;
	m_nColAMin = 0;
	m_nColAMax = 0;
	m_fSubtractionMove = 0.0f;
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
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		//���I�Ɋm��
		m_pEffect3D.push_back(CEffect3D::Create(pos, size, m_col, CEffect3D::EFFECT3D_TYPE::FIRE));

		//�ړ�������������߂�
		float fRotX = EXPLOSION_MOVE_ROTATE;
		float fRotY = EXPLOSION_MOVE_ROTATE;
		//���I�m��
		m_fRotX.push_back(fRotX);
		m_fRotY.push_back(fRotY);
	}

	//�I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::OBJTYPE::FIRE_BALL);

	//�ʒu�ƃT�C�Y��ݒ�
	SetPos(pos);

	return S_OK;
}

//================================================
//�I������
//================================================
void CExplosion::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CExplosion::Update(void)
{
	for (int nCntEffect = 0; nCntEffect < m_nNumEffect; nCntEffect++)
	{
		if (m_pEffect3D[nCntEffect] != nullptr)
		{
			//�ʒu�ƃT�C�Y���擾
			D3DXVECTOR3 pos = m_pEffect3D[nCntEffect]->GetPos();
			D3DXVECTOR3 size = m_pEffect3D[nCntEffect]->GetSize();

			//�ړ��ʂ�ݒ�
			D3DXVECTOR3 move = D3DXVECTOR3(sinf(m_fRotX[nCntEffect]) * sinf(m_fRotY[nCntEffect]) * m_fInitMove[nCntEffect],
				                           sinf(m_fRotX[nCntEffect]) * cosf(m_fRotY[nCntEffect]) * m_fInitMove[nCntEffect],
				                           cosf(m_fRotX[nCntEffect]) * m_fInitMove[nCntEffect]);
			//�d��
			move.y -= m_fGravity;

			//�ړ��ʔ��f
			pos += move;

			//�T�C�Y������������
			size.x *= EXPLOSION_SIZE_SUBTRACTION;
			size.y *= EXPLOSION_SIZE_SUBTRACTION;

			//�J���[���擾
			D3DXCOLOR col = m_pEffect3D[nCntEffect]->GetCol();
			//��������
			float fCola = float((rand() % m_nColAMax + m_nColAMin)) / 100000.0f;
			col.a -= fCola;
			//�����Ȃ��Ȃ�����
			if (col.a <= 0.0f)
			{
				//����
				m_pEffect3D[nCntEffect]->Uninit();
				m_pEffect3D[nCntEffect] = nullptr;
			}
			else
			{
				//�J���[��ݒ�
				m_pEffect3D[nCntEffect]->SetCol(col);

				//�ʒu��ݒ�
				m_pEffect3D[nCntEffect]->SetPos(pos, size);

				//�ړ��ʂ����炵�Ă���
				m_fInitMove[nCntEffect] *= m_fSubtractionMove;
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CExplosion::Draw(void)
{
	
}

//================================================
//��������
//================================================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
	                           float fGravity, float fColAMin, float fColAMax, float SubtractionMove)
{
	//�C���X�^���X�̐���
	CExplosion *pExplosion = nullptr;
	if (pExplosion == nullptr)
	{
		pExplosion = new CExplosion();
		if (pExplosion != nullptr)
		{
			pExplosion->m_nNumEffect = nNumEffect;
			pExplosion->m_col = col;
			pExplosion->m_fGravity = fGravity;
			pExplosion->m_fSubtractionMove = SubtractionMove;
			//�����_���l�͐����ł���������Ȃ��̂Ő����ɂ���
			pExplosion->m_nColAMin = int(fColAMin * 100000.0f);
			pExplosion->m_nColAMax = int(fColAMax * 100000.0f);
			//�����_���̐��l�������Ɉ����Ŏw�肵�������ő�l�ɂ��邽�߂Ɍv�Z
			pExplosion->m_nColAMax -= pExplosion->m_nColAMin;
			//�����_���l�͐����ł���������Ȃ��̂Ő����ɂ���
			int nMoveMin = int(fMoveMin * 100.0f);
			int nMoveMax = int(fMoveMax * 100.0f);
			//�����_���̐��l�������Ɉ����Ŏw�肵�������ő�l�ɂ��邽�߂Ɍv�Z
			nMoveMax -= nMoveMin;
			for (int nCnt = 0; nCnt < pExplosion->m_nNumEffect; nCnt++)
			{
				//���I�m��
				pExplosion->m_fInitMove.push_back(float(rand() % nMoveMax + nMoveMin) / 100.0f);
			}
			pExplosion->Init(pos, size);
		}
	}
	return pExplosion;
}
