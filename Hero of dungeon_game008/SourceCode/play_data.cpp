//================================================
//�v���C�f�[�^�Ǘ�����
//Author:KatoMizuki
//================================================
#include "play_data.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPlayData::CPlayData()
{
	m_nHitPoint = 0;				
	m_nMagicPoint = 0;				
	m_nSpecialPoint = 0;			
	m_pHpGauge = nullptr;			
	m_pMpGauge = nullptr;			
	m_pSpGauge = nullptr;			
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;
}

//================================================
//�f�X�g���N�^
//================================================
CPlayData::~CPlayData()
{

}

//================================================
//����������
//================================================
HRESULT CPlayData::Init(void)
{
	m_nHitPoint = 0;
	m_nMagicPoint = 0;
	m_nSpecialPoint = 0;
	m_pHpGauge = nullptr;
	m_pMpGauge = nullptr;
	m_pSpGauge = nullptr;
	m_nScore = 0;
	m_pScore = nullptr;
	m_nTime = 0;

	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayData::Uninit(void)
{
	
}
