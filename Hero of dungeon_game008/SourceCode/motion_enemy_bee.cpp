//================================================
//�I�^�G�̃��[�V��������
//Author:KatoMizuki
//================================================
#include "motion_enemy_bee.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMotionEnemyBee::CMotionEnemyBee()
{
	//���[�V�����̐�����
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BEE_TYPE_MAX; nCntMotion++)
	{
		//���[�V�������̕ϐ��𓮓I�Ɋm��
		m_aInfo.push_back({});
		//������
		m_aInfo[nCntMotion].bLoop = false;
		m_aInfo[nCntMotion].nNumKey = 0;
		//�L�[�ő吔����
		for (int nCntKey = 0; nCntKey < MOTION_MAX_KEY_INFO; nCntKey++)
		{
			//������
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = 0;
			//���f���̐�����
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
			{
				//���f���̃L�[�v�f�̕ϐ��𓮓I�Ɋm��
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey.push_back({});
				//������
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//���I�m�ۂ��ď�����
				m_posOld.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_rotOld.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			}
		}
	}

	//������
	m_type = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_typeNext = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_typeOld = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 0.0f;
	m_nKey = 0;
	m_bConnect = false;
}

//================================================
//�f�X�g���N�^
//================================================
CMotionEnemyBee::~CMotionEnemyBee()
{

}

//================================================
//����������
//================================================
HRESULT CMotionEnemyBee::Init(CEnemyBee *pEnemyBee)
{
	//���[�V�����̐�����
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BEE_TYPE_MAX; nCntMotion++)
	{
		//�L�[���擾
		m_aInfo[nCntMotion].nNumKey = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, nCntMotion).nNumKey;
		//���[�v���擾
		m_aInfo[nCntMotion].bLoop = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, nCntMotion).bLoop;
		
		//�L�[�̐�����
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			//�t���[�����̎擾
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, nCntMotion).aKeyInfo[nCntKey].nFrame;
			
			//���f���̐�����
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
			{
				//�ʒu�Ɖ�]�̎擾
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, nCntMotion).aKeyInfo[nCntKey].aKey[nCntModel].pos;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = CManager::GetInstance()->GetMotionRoad()->GetMotionInfo(CMotionRoad::MOTION_HAVE_TYPE_ENEMY_BEE, nCntMotion).aKeyInfo[nCntKey].aKey[nCntModel].rot;
			}
		}
	}

	//�e�q�֌W�ɂ��ʒu����̏C��
	for (int nCntMotion = 0; nCntMotion < CMotionRoad::MOTION_ENEMY_BEE_TYPE_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
			{
				//���f���̈ʒu�ƌ����擾
				D3DXVECTOR3 pos = pEnemyBee->GetModelPos();
				D3DXVECTOR3 rot = pEnemyBee->GetModelRot();

				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x = pos.x + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y = pos.y + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z = pos.z + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x = rot.x + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y = rot.y + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y;
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z = rot.z + m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z;
			}
		}
	}

	//�ϐ�������
	m_type = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_typeNext = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_typeOld = CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 0.0f;
	m_nKey = 0;
	m_bConnect = false;

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
	{
		//���f���̈ʒu�ƌ����ɔ��f
		pEnemyBee->SetModelPos(m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos);
		pEnemyBee->SetModelRot(m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot);
		m_posOld[nCntModel] = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos;
		m_rotOld[nCntModel] = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot;
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CMotionEnemyBee::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMotionEnemyBee::Update(CEnemyBee *pEnemyBee)
{
	D3DXVECTOR3 posAsk[MAX_ENEMY_BEE_MODEL];		//���߂����l
	D3DXVECTOR3 rotAsk[MAX_ENEMY_BEE_MODEL];		//���߂����l
	D3DXVECTOR3 posDiffer[MAX_ENEMY_BEE_MODEL];	//����
	D3DXVECTOR3 rotDiffer[MAX_ENEMY_BEE_MODEL];	//����

	//���̃L�[
	int nKeyNext = 0;

	if (m_nKey >= m_aInfo[m_type].nNumKey - 1)	//���݂̃L�[���ő�l�ȏゾ������
	{
		nKeyNext = 0;
	}
	else			//���݂̃L�[���ő�l��菬����������
	{
		nKeyNext = m_nKey + 1;
	}

	//���[�V�������Ȃ���Ƃ�
	if (m_bConnect == true)	
	{
		//���̃L�[��0�ɂ���
		nKeyNext = 0;
	}
	else
	{
		m_fConnectMaxFrame = (float)m_aInfo[m_type].aKeyInfo[m_nKey].nFrame;
	}
	

	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
	{
		if (m_bConnect == true)		//�Ȃ���Ƃ�
		{
			//���݂̃L�[�Ǝ��̃L�[�̈ʒu�̍��������߂�
			posDiffer[nCntModel].x = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.x - m_posOld[nCntModel].x;
			posDiffer[nCntModel].y = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.y - m_posOld[nCntModel].y;
			posDiffer[nCntModel].z = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].pos.z - m_posOld[nCntModel].z;

			//���݂̃L�[�Ǝ��̃L�[�̉�]�̍��������߂�
			rotDiffer[nCntModel].x = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.x - m_rotOld[nCntModel].x;
			rotDiffer[nCntModel].y = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.y - m_rotOld[nCntModel].y;
			rotDiffer[nCntModel].z = m_aInfo[m_type].aKeyInfo[0].aKey[nCntModel].rot.z - m_rotOld[nCntModel].z;

			if (rotDiffer[nCntModel].x <= -D3DX_PI)
			{
				rotDiffer[nCntModel].x += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].x > D3DX_PI)
			{
				rotDiffer[nCntModel].x -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].z <= -D3DX_PI)
			{
				rotDiffer[nCntModel].z += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].z > D3DX_PI)
			{
				rotDiffer[nCntModel].z -= D3DX_PI * 2.0f;
			}

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			posAsk[nCntModel].x = m_posOld[nCntModel].x + posDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].y = m_posOld[nCntModel].y + posDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].z = m_posOld[nCntModel].z + posDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);

			//���݂̃L�[���玟�̃L�[�ɓ���������̌��������߂�
			rotAsk[nCntModel].x = m_rotOld[nCntModel].x + rotDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].y = m_rotOld[nCntModel].y + rotDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].z = m_rotOld[nCntModel].z + rotDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);
		}
		else	//�Ȃ��Ȃ��Ƃ�
		{
			//���݂̃L�[�Ǝ��̃L�[�̈ʒu�̍��������߂�
			posDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.x
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x;
			posDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.y
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y;
			posDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].pos.z
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z;

			//���݂̃L�[�Ǝ��̃L�[�̉�]�̍��������߂�
			rotDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.x
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x;
			rotDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.y
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y;
			rotDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[nKeyNext].aKey[nCntModel].rot.z
				- m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z;

			if (rotDiffer[nCntModel].x <= -D3DX_PI)
			{
				rotDiffer[nCntModel].x += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].x > D3DX_PI)
			{
				rotDiffer[nCntModel].x -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}
			if (rotDiffer[nCntModel].z <= -D3DX_PI)
			{
				rotDiffer[nCntModel].z += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].z > D3DX_PI)
			{
				rotDiffer[nCntModel].z -= D3DX_PI * 2.0f;
			}

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			posAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x
				+ posDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y
				+ posDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			posAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z
				+ posDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);

			//���݂̃L�[���玟�̃L�[�ɓ���������̌��������߂�
			rotAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x
				+ rotDiffer[nCntModel].x * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y
				+ rotDiffer[nCntModel].y * (m_fCounter / m_fConnectMaxFrame);
			rotAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z
				+ rotDiffer[nCntModel].z * (m_fCounter / m_fConnectMaxFrame);
		}

		//���f���̈ʒu�ƌ����ɔ��f
		pEnemyBee->SetModelPos(posAsk[nCntModel]);
		pEnemyBee->SetModelRot(rotAsk[nCntModel]);
	}

	//�J�E���^�[�����Z
	m_fCounter += 1.0f;

	if (m_bConnect == false)
	{
		//�t���[�����ő�l�𒴂�����
		if (m_fCounter > m_aInfo[m_type].aKeyInfo[m_nKey].nFrame)
		{
			m_nKey++;
			if (m_nKey < m_aInfo[m_type].nNumKey - 1)//�L�[�̍ő吔-1
			{
				m_fCounter = 0.0f;
			}
			else if (m_nKey >= m_aInfo[m_type].nNumKey - 1)
			{
				if (m_aInfo[m_type].bLoop == 0)	//���[�v���Ȃ��Ƃ�
				{
					//���̃��[�V�������j���[�g�������[�V�����ɂ���
					SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE_NEUTRAL, pEnemyBee);
				}
				else	//���[�v����Ƃ�
				{
					//���̃��[�V�����𓯂����[�V�����ɂ���
					if (m_nKey > m_aInfo[m_type].nNumKey - 1)
					{
						m_nKey = 0;
					}
				}
				
				m_fCounter = 0.0f;
			}
		}
	}
	else
	{
		//�t���[�����ő�l�𒴂�����
		if (m_fCounter > m_fConnectMaxFrame)
		{
			m_bConnect = false;
			m_fCounter = 0.0f;
			m_nKey = 0;
			//���݂̃��[�V�����̎�ނ����̃��[�V�����̎�ނɂ���
			m_typeOld = m_type;
		}
	}
}

//================================================
//��������
//================================================
CMotionEnemyBee *CMotionEnemyBee::Create(CEnemyBee *pEnemyBee)
{
	//�C���X�^���X�̐���
	CMotionEnemyBee *pMotionEnemyBee = nullptr;
	if (pMotionEnemyBee == nullptr)
	{
		pMotionEnemyBee = new CMotionEnemyBee;
		if (pMotionEnemyBee != nullptr)
		{
			pMotionEnemyBee->Init(pEnemyBee);
		}
	}
	return pMotionEnemyBee;
}

//================================================
//���[�V�����ݒ菈��
//================================================
void CMotionEnemyBee::SetMotion(CMotionRoad::MOTION_ENEMY_BEE_TYPE type, CEnemyBee *pEnemyBee)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
	{
		//���f���̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = pEnemyBee->GetModelPos();
		D3DXVECTOR3 rot = pEnemyBee->GetModelRot();

		//���݂̃��f���̈ʒu�ƌ�����ۑ�
		m_posOld[nCntModel] = pos;
		m_rotOld[nCntModel] = rot;
	}
	m_typeOld = m_type;
	m_type = type;
	m_typeNext = type;
	m_bConnect = true;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 10;
}

//================================================
//���[�V�����ݒ菈��
//================================================
void CMotionEnemyBee::SetMotion(int nType, CEnemyBee *pEnemyBee)
{
	for (int nCntModel = 0; nCntModel < MAX_ENEMY_BEE_MODEL; nCntModel++)
	{
		//���f���̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = pEnemyBee->GetModelPos();
		D3DXVECTOR3 rot = pEnemyBee->GetModelRot();

		//���݂̃��f���̈ʒu�ƌ�����ۑ�
		m_posOld[nCntModel] = pos;
		m_rotOld[nCntModel] = rot;
	}

	m_typeOld = m_type;
	m_type = (CMotionRoad::MOTION_ENEMY_BEE_TYPE)nType;
	m_typeNext = (CMotionRoad::MOTION_ENEMY_BEE_TYPE)nType;
	m_bConnect = true;
	m_fCounter = 0.0f;
	m_fConnectMaxFrame = 10;
}

//================================================
//���[�V�����擾����
//================================================
CMotionRoad::MOTION_ENEMY_BEE_TYPE CMotionEnemyBee::GetMotion(void)
{
	return m_type;
}

//================================================
//���[�V�������Ȃ��Ă���Œ����ǂ����擾����
//================================================
bool CMotionEnemyBee::GetConnect(void)
{
	return m_bConnect;
}