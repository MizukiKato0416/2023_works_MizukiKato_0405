//================================================
//�΂̕��̏���
//Author:KatoMizuki
//================================================
#include "spark.h"
#include "effect3D.h"

//================================================
//�}�N����`
//================================================
#define SPARK_MOVE_ROTATE			(float((rand() % 629 + -314)) / 100.0f)		//�ړ��������
#define SPARK_SIZE_SUBTRACTION		(0.99f)										//�T�C�Y���Z�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CSpark::CSpark(int nPriority) :CObject(nPriority)
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
CSpark::~CSpark()
{

}

//================================================
//����������
//================================================
HRESULT CSpark::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCnt = 0; nCnt < m_nNumEffect; nCnt++)
	{
		//���I�Ɋm��
		m_pEffect3D.push_back(CEffect3D::Create(pos, size, m_col, CEffect3D::EFFECT3D_TYPE::NONE));

		//�ړ�������������߂�
		float fRotX = SPARK_MOVE_ROTATE;
		float fRotY = SPARK_MOVE_ROTATE;
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
void CSpark::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CSpark::Update(void)
{
	for (int nCntEffect = 0; nCntEffect < static_cast<int>(m_pEffect3D.size()); nCntEffect++)
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
void CSpark::Draw(void)
{
	
}

//================================================
//��������
//================================================
CSpark* CSpark::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nNumEffect, D3DXCOLOR col, float fMoveMin, float fMoveMax,
	                           float fGravity, float fColAMin, float fColAMax, float SubtractionMove)
{
	//�C���X�^���X�̐���
	CSpark *pSpark = nullptr;
	if (pSpark == nullptr)
	{
		pSpark = new CSpark();
		if (pSpark != nullptr)
		{
			pSpark->m_nNumEffect = nNumEffect;
			pSpark->m_col = col;
			pSpark->m_fGravity = fGravity;
			pSpark->m_fSubtractionMove = SubtractionMove;
			//�����_���l�͐����ł���������Ȃ��̂Ő����ɂ���
			pSpark->m_nColAMin = int(fColAMin * 100000.0f);
			pSpark->m_nColAMax = int(fColAMax * 100000.0f);
			//�����_���̐��l�������Ɉ����Ŏw�肵�������ő�l�ɂ��邽�߂Ɍv�Z
			pSpark->m_nColAMax -= pSpark->m_nColAMin;
			//�����_���l�͐����ł���������Ȃ��̂Ő����ɂ���
			int nMoveMin = int(fMoveMin * 100.0f);
			int nMoveMax = int(fMoveMax * 100.0f);
			//�����_���̐��l�������Ɉ����Ŏw�肵�������ő�l�ɂ��邽�߂Ɍv�Z
			nMoveMax -= nMoveMin;
			for (int nCnt = 0; nCnt < pSpark->m_nNumEffect; nCnt++)
			{
				//���I�m��
				pSpark->m_fInitMove.push_back(float(rand() % nMoveMax + nMoveMin) / 100.0f);
			}
			pSpark->Init(pos, size);
		}
	}
	return pSpark;
}
