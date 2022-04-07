//================================================
//�^�C������
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "renderer.h"
#include "time.h"
#include "manager.h"
#include "number.h"
#include "ui.h"
#include "play_data.h"
#include "texture.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	m_nTime = 0;
	m_nCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CTime::~CTime()
{

}

//================================================
//����������
//================================================
HRESULT CTime::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_nCounter = 0;

	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber] = CNumber::Create(D3DXVECTOR3(pos.x - (size.x * MAX_TIME_POLYGON / 2) + (size.x * nCntNumber) + (size.x / 2.0f), pos.y, 0.0f), size);
		m_apNumber[nCntNumber]->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_NUMBER"));
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CTime::Uninit(void)
{
	//���Ԃ�ۑ�
	CManager::GetInstance()->GetPlayData()->SetTime(m_nTime);

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
void CTime::Update(void)
{
	//�J�E���^�[�����Z
	m_nCounter++;

	//�J�E���^�[60����1�b�o�߂�����
	if (m_nCounter % 60 == 0)
	{
		AddTime(1);
	}
}

//================================================
//�`�揈��
//================================================
void CTime::Draw(void)
{
	for (int nCntNumber = 0; nCntNumber < MAX_TIME_POLYGON; nCntNumber++)
	{
		m_apNumber[nCntNumber]->Draw();
	}
}

//================================================
//��������
//================================================
CTime* CTime::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nStartTime)
{
	//�C���X�^���X�̐���
	CTime *pTime = NULL;
	if (pTime == NULL)
	{
		pTime = new CTime;
		if (pTime != NULL)
		{
			pTime->m_nTime = nStartTime;
			pTime->Init(pos, size);
			pTime->SetTime(pTime->m_nTime);
		}
	}
	return pTime;
}

//================================================
//�X�R�A�擾����
//================================================
int CTime::GetTime(void)
{
	return m_nTime;
}

//================================================
//�X�R�A�ݒ菈��
//================================================
void CTime::SetTime(int nTime)
{
	m_nTime = nTime;

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
//�X�R�A���Z����
//================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;

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

//=============================================================================
// number�擾����
//=============================================================================
CNumber* CTime::GetNumber(int nNumber)
{
	return m_apNumber[nNumber];
}