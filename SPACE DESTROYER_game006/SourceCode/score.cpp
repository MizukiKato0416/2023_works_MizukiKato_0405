//================================================
//�X�R�A����
//Authore:��������
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
	m_nScore = 0;
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
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_SCORE_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f),
												size);
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CScore::Uninit(void)
{
	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//�X�R�A���v���C�f�[�^�ɕۑ�
	pPlayData->SetScore(m_nScore);

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
			m_apNumber[nCntNumber]->SetNumber(m_nScore % (int)powf(10, MAX_SCORE_POLYGON - nCntNumber) / (int)powf(10, MAX_SCORE_POLYGON - 1 - nCntNumber));
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