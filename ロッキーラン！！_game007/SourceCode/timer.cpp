//================================================
//�^�C������
//Author:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "timer.h"
#include "manager.h"
#include "number.h"
#include "ui.h"
#include "play_data.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTimer::CTimer(int nPriority) : CScene(nPriority)
{
	m_nTime = START_TIME;
	m_pUi = NULL;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CTimer::~CTimer()
{

}

//================================================
//����������
//================================================
HRESULT CTimer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�J���}�̐���
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, pos.y - 5.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f), PRIORITY_UI, CUi::UI_TYPE_GAME_TIME_COMMA);

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		//�����_�����邽�߁A4�ڂ̐������炸�炷
		if (nCntNumber >= 3)
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x + 20.0f - (size.x * MAX_TIME_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
		else
		{
			m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_TIME_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		}
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CTimer::Uninit(void)
{
	//�v���C�f�[�^�̎擾
	CPlayData *pPlayData = NULL;
	pPlayData = CManager::GetPlayData();

	//�X�R�A���v���C�f�[�^�ɕۑ�
	pPlayData->SetScore(m_nTime);

	//�i���o�[�̔j��
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
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
void CTimer::Update(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		if (nCntNumber == 0)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime / (int)powf(10, MAX_TIME_POLYGON - 1));
		}
		else if (nCntNumber == MAX_TIME_POLYGON - 1)
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % 10);
		}
		else
		{
			m_apNumber[nCntNumber]->SetNumber(m_nTime % (int)powf(10, MAX_TIME_POLYGON - (float)nCntNumber) / (int)powf(10, MAX_TIME_POLYGON - 1 - (float)nCntNumber));
		}
	}
}

//================================================
//�`�揈��
//================================================
void CTimer::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//��������
//================================================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CTimer *pTimer = NULL;
	if (pTimer == NULL)
	{
		pTimer = new CTimer;
		if (pTimer != NULL)
		{
			pTimer->Init(pos, size);
		}
	}
	return pTimer;
}

//================================================
//�X�R�A�擾����
//================================================
int CTimer::GetTime(void)
{
	return m_nTime;
}

//================================================
//�X�R�A�ݒ菈��
//================================================
void CTimer::SetTime(int nTime)
{
	m_nTime = nTime;
}

//================================================
//�X�R�A���Z����
//================================================
void CTimer::AddTime(int nValue)
{
	m_nTime += nValue;
}

//=============================================================================
// number�擾����
//=============================================================================
CNumber* CTimer::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}