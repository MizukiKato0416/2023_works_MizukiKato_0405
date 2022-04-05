//================================================
//�����L���O����
//Authore:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "score.h"
#include "manager.h"
#include "ranking.h"
#include "scene.h"
#include "play_data.h"
#include "number.h"
#include "result.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CScore *CRanking::m_pScore[MAX_RANKING] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CRanking::CRanking()
{
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		m_nScore[nCntRanking] = 0;
	}
	m_nNowScore = 0;
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
CRanking::~CRanking()
{

}

//================================================
//����������
//================================================
HRESULT CRanking::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�X�R�A�̐���
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_pScore[nCntRanking] = CScore::Create(D3DXVECTOR3((pos.x), (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)) * nCntRanking + (float)(SCREEN_HEIGHT / (MAX_RANKING + 1)), 0.0f),
												size);
	}

	//���[�h����
	FILE *pFile;
	pFile = fopen("data/ranking.txt", "r");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fscanf(pFile, "%d", &m_nScore[nCntRanking]);
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//�v���C�f�[�^�ɕۑ����Ă��鍡��̃X�R�A��ϐ��ɕۑ�
	m_nScore[MAX_SCORE_DATA - 1] = pPlayData->GetScore();
	m_nNowScore = pPlayData->GetScore();

	//�\�[�g
	for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA; nCntRanking++)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_SCORE_DATA - 1; nCntRanking++)
		{
			if (m_nScore[nCntRanking] < m_nScore[nCntRanking + 1])
			{
				int nScore = m_nScore[nCntRanking];
				m_nScore[nCntRanking] = m_nScore[nCntRanking + 1];
				m_nScore[nCntRanking + 1] = nScore;
			}
		}
	}

	//�X�R�A�̐ݒ�
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		m_pScore[nCntRanking]->SetScore(m_nScore[nCntRanking]);
	}

	//�Z�[�u����
	pFile = fopen("data/ranking.txt", "w");
	if (pFile != NULL)
	{
		for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
		{
			fprintf(pFile, "%d\n", m_pScore[nCntRanking]->GetScore());
		}
	}
	else
	{
		printf("�t�@�C�����J���܂���ł���\n");
	}
	fclose(pFile);

	//�J���[�̐ݒ�
	m_col.r = 255.0f;
	m_col.g = 0.0f;
	m_col.b = 0.0f;
	m_col.a = 255.0f;

	return S_OK;
}

//================================================
//�I������
//================================================
void CRanking::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CRanking::Update(void)
{
	for (int nCntRanking = 0; nCntRanking < MAX_RANKING; nCntRanking++)
	{
		if (m_nScore[nCntRanking] == m_nNowScore)
		{
			//�J���[�𔖂�����
			m_col.a -= 255;
			if (m_col.r == 255)
			{
				m_col.r = 0;
				m_col.g = 255;
				m_col.b = 0;
			}
			else if(m_col.g == 255)
			{
				m_col.r = 0;
				m_col.g = 0;
				m_col.b = 255;
			}
			else if (m_col.b == 255)
			{
				m_col.r = 255;
				m_col.g = 0;
				m_col.b = 0;
			}

			if (m_col.a < 0)
			{
				m_col.a = 255;
			}

			for (int nCntNumber = 0; nCntNumber < MAX_SCORE_POLYGON; nCntNumber++)
			{
				//�i���o�[���擾���ăJ���[��ݒ�
				m_pScore[nCntRanking]->GetNumber(nCntNumber)->SetCol(m_col);
			}

			break;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CRanking::Draw(void)
{
	
}

//================================================
//��������
//================================================
CRanking* CRanking::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CRanking *pRanking = NULL;
	if (pRanking == NULL)
	{
		pRanking = new CRanking;
		if (pRanking != NULL)
		{
			pRanking->Init(pos, size);
		}
	}
	return pRanking;
}

