//================================================
//�X�R�A����
//Author:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "number.h"
#include "play_data.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScore::CScore(int nPriority) :CScene(nPriority)
{
	m_nScore = MAX_SCORE;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CScore::~CScore()
{

}

//================================================
//����������
//================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		//�����_�����邽�߁A4�ڂ̐������炸�炷
		if (nCntNumber >= MAX_SCORE_POLYGON / 2)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x + 20.0f - (size.x * MAX_SCORE_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_SCORE_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
	}
	m_size = size;
	m_pos = pos;

	SetPos(m_pos);
	SetSize(m_size);
	return S_OK;
}

//================================================
//�I������
//================================================
void CScore::Uninit(void)
{
	//�i���o�[�̔j��
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (m_apNumber[nCntNumber] != NULL)
		{
			m_apNumber[nCntNumber]->Uninit();
			delete m_apNumber[nCntNumber];
			m_apNumber[nCntNumber] = NULL;
		}
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CScore::Update(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore / (int)powf(10, MAX_SCORE_POLYGON - 1));
		}
		else if (nCntNumber == MAX_SCORE_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//�`�揈��
//================================================
void CScore::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//��������
//================================================
CScore* CScore::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CScore *pScore = NULL;
	if (pScore == NULL)
	{
		pScore = new CScore;
		if (pScore != NULL)
		{
			pScore->Init(pos, size);
		}
	}
	return pScore;
}

//================================================
//�X�R�A�擾����
//================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//================================================
//�X�R�A�ݒ菈��
//================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//================================================
//�X�R�A���Z����
//================================================
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;
}

//=============================================================================
// number�擾����
//=============================================================================
CNumber* CScore::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}

//================================================
//�X�R�A�ʒu�ݒ菈��
//================================================
void CScore::SetScorePos(D3DXVECTOR3 pos)
{
	//�ʒu�ݒ�
	m_pos = pos;
	for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
	{
		//�����_�����邽�߁A4�ڂ̐������炸�炷
		if (nCntNumber >= MAX_SCORE_POLYGON / 2)
		{
			m_apNumber[nCntNumber]->SetPos(D3DXVECTOR3(pos.x + 20.0f - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), pos.y, 0.0f));
		}
		else
		{
			m_apNumber[nCntNumber]->SetPos(D3DXVECTOR3(pos.x - (m_size.x * MAX_SCORE_POLYGON / 2) + (m_size.x * nCntNumber) + (m_size.x / 2.0f), pos.y, 0.0f));
		}
	}
	//�ʒu��ݒ�
	SetPos(m_pos);
}