//================================================
//�v���C���[�̃��[�V��������
//Author:��������
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "motion_player.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMotionPlayer::CMotionPlayer()
{
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		m_aInfo[nCntMotion].bLoop = false;
		m_aInfo[nCntMotion].nNumKey = 0;
		for (int nCntKey = 0; nCntKey < MOTION_PLAYER_MAX_KEY_INFO; nCntKey++)
		{
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = 0;
			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	m_type = MOTION_PLAYER_TYPE_NEUTRAL;
	m_typeNext = MOTION_PLAYER_TYPE_NEUTRAL;
	m_nNumKey = 0;
	m_nKeyOld = 0;
	m_fCounter = 0.0f;
	m_nKey = 0;
	m_bConnect = false;
}

//================================================
//�f�X�g���N�^
//================================================
CMotionPlayer::~CMotionPlayer()
{

}

//================================================
//����������
//================================================
HRESULT CMotionPlayer::Init(CPlayer *pPlayer)
{
	//text�t�@�C���ǂݍ���
	FILE *pfile = fopen("data/MOTION/motion_player.txt", "r");

	char cString[MOTION_PLAYER_MAX_STRING];

	//���[�V�����̓ǂݍ���
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		//��s���ۑ�
		while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
		{
			//�������ۑ�
			fscanf(pfile, "%s", cString);
			//������̒���MOTIONSET����������
			if (strncmp("MOTIONSET", cString, 10) == 0)
			{
				//���[�v���̎擾
				//�L�[���̎擾
				fscanf(pfile, "%s%*s%d%*s%*s%*s%*s", cString, &m_aInfo[nCntMotion].bLoop);
				fscanf(pfile, "%s%*s%d", cString, &m_aInfo[nCntMotion].nNumKey);
				break;
			}
		}

		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
			{
				//�������ۑ�
				fscanf(pfile, "%s", cString);
				//������̒���FRAME����������
				if (strncmp("FRAME", cString, 6) == 0)
				{
					//�t���[�����̎擾
					fscanf(pfile, "%s%d", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame);
					break;
				}
			}

			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
				{
					//�������ۑ�
					fscanf(pfile, "%s", cString);
					//������̒���POS����������
					if (strncmp("POS", cString, 4) == 0)
					{
						//�ʒu�A��]���̎擾
						fscanf(pfile, "%s%f%f%f", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.x, 
																&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.y,
																&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].pos.z);
						fscanf(pfile, "%s%*s%f%f%f%*s", cString, &m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.x,
																	&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.y,
																	&m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntModel].rot.z);
						break;
					}
				}
			}

			while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
			{
				//�������ۑ�
				fscanf(pfile, "%s", cString);
				//������̒���END_KEYSET����������
				if (strncmp("END_KEYSET", cString, 11) == 0)
				{
					break;
				}
			}
		}

		while (fgets(cString, MOTION_PLAYER_MAX_STRING, pfile) != NULL)
		{
			//�������ۑ�
			fscanf(pfile, "%s", cString);
			//������̒���END_MOTIONSET����������
			if (strncmp("END_MOTIONSET", cString, 14) == 0)
			{
				break;
			}
		}
	}
	fclose(pfile);

	//�e�q�֌W�ɂ��ʒu����̏C��
	for (int nCntMotion = 0; nCntMotion < MOTION_PLAYER_TYPE_MAX; nCntMotion++)
	{
		for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotion].nNumKey; nCntKey++)
		{
			for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
			{
				//���f���̈ʒu�ƌ����擾
				D3DXVECTOR3 pos = pPlayer->GetModelPos(nCntModel);
				D3DXVECTOR3 rot = pPlayer->GetModelRot(nCntModel);

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
	m_type = MOTION_PLAYER_TYPE_NEUTRAL;
	m_typeNext = MOTION_PLAYER_TYPE_NEUTRAL;
	m_fCounter = 0.0f;
	m_nKey = 0;
	m_bConnect = false;

	return S_OK;
}

//================================================
//�I������
//================================================
void CMotionPlayer::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CMotionPlayer::Update(CPlayer *pPlayer)
{
	D3DXVECTOR3 posAsk[MAX_PLAYER_MODEL];		//���߂����l
	D3DXVECTOR3 rotAsk[MAX_PLAYER_MODEL];		//���߂����l
	D3DXVECTOR3 posDiffer[MAX_PLAYER_MODEL];	//����
	D3DXVECTOR3 rotDiffer[MAX_PLAYER_MODEL];	//����

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

	for (int nCntModel = 0; nCntModel < MAX_PLAYER_MODEL; nCntModel++)
	{
		//�t���[����
		int nFrame = 0;
		if (m_bConnect == true)
		{
			nFrame = 10;
			if (m_aInfo[m_type].bLoop == 1)	//���[�v���鎞
			{
				nFrame = m_aInfo[m_type].aKeyInfo[0].nFrame;
			}
		}
		else
		{
			nFrame = m_aInfo[m_type].aKeyInfo[m_nKey].nFrame;
		}

		if (m_bConnect == true)		//�Ȃ���Ƃ�
		{
			//���f���̈ʒu�ƌ������擾
			D3DXVECTOR3 pos = pPlayer->GetModelPos(nCntModel);
			D3DXVECTOR3 rot = pPlayer->GetModelRot(nCntModel);

			//���݂̃L�[�Ǝ��̃L�[�̈ʒu�̍��������߂�
			posDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.x - pos.x;
			posDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.y - pos.y;
			posDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].pos.z - pos.z;

			//���݂̃L�[�Ǝ��̃L�[�̉�]�̍��������߂�
			rotDiffer[nCntModel].x = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.x - rot.x;
			rotDiffer[nCntModel].y = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.y - rot.y;
			rotDiffer[nCntModel].z = m_aInfo[m_typeNext].aKeyInfo[0].aKey[nCntModel].rot.z - rot.z;

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			posAsk[nCntModel].x = pos.x + posDiffer[nCntModel].x * (m_fCounter / nFrame);
			posAsk[nCntModel].y = pos.y + posDiffer[nCntModel].y * (m_fCounter / nFrame);
			posAsk[nCntModel].z = pos.z + posDiffer[nCntModel].z * (m_fCounter / nFrame);

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			rotAsk[nCntModel].x = rot.x + rotDiffer[nCntModel].x * (m_fCounter / nFrame);
			rotAsk[nCntModel].y = rot.y + rotDiffer[nCntModel].y * (m_fCounter / nFrame);
			rotAsk[nCntModel].z = rot.z + rotDiffer[nCntModel].z * (m_fCounter / nFrame);
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

			if (rotDiffer[nCntModel].y <= -D3DX_PI)
			{
				rotDiffer[nCntModel].y += D3DX_PI * 2.0f;
			}
			else if (rotDiffer[nCntModel].y > D3DX_PI)
			{
				rotDiffer[nCntModel].y -= D3DX_PI * 2.0f;
			}

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			posAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.x
				+ posDiffer[nCntModel].x * (m_fCounter / nFrame);
			posAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.y
				+ posDiffer[nCntModel].y * (m_fCounter / nFrame);
			posAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].pos.z
				+ posDiffer[nCntModel].z * (m_fCounter / nFrame);

			//���݂̃L�[���玟�̃L�[�ɓ���������̈ʒu�����߂�
			rotAsk[nCntModel].x = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.x
				+ rotDiffer[nCntModel].x * (m_fCounter / nFrame);
			rotAsk[nCntModel].y = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.y
				+ rotDiffer[nCntModel].y * (m_fCounter / nFrame);
			rotAsk[nCntModel].z = m_aInfo[m_type].aKeyInfo[m_nKey].aKey[nCntModel].rot.z
				+ rotDiffer[nCntModel].z * (m_fCounter / nFrame);
		}

		//���f���̈ʒu�ƌ����ɔ��f
		pPlayer->SetModelPos(nCntModel, posAsk[nCntModel]);
		pPlayer->SetModelRot(nCntModel, rotAsk[nCntModel]);
	}

	//�J�E���^�[�����Z
	m_fCounter += 1.0f;

	if (m_bConnect == false)
	{
		//�t���[�����ő�l�𒴂�����
		if (m_fCounter >= m_aInfo[m_type].aKeyInfo[m_nKey].nFrame)
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
					if (m_type == MOTION_PLAYER_TYPE_DIVE)
					{
						//���̃��[�V�������_�C�u���n���[�V�����ɂ���
						SetMotion(MOTION_PLAYER_TYPE_DIVE_LAND);
					}
					else if (m_type == MOTION_PLAYER_TYPE_LAND)
					{
						D3DXVECTOR3 movePlayer = pPlayer->GetMove();
						if (movePlayer.x == 0.0f && movePlayer.z == 0.0f)
						{
							//���̃��[�V�������j���[�g�������[�V�����ɂ���
							SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
						}
						else
						{
							//���̃��[�V�������ړ����[�V�����ɂ���
							SetMotion(MOTION_PLAYER_TYPE_MOVE);
						}
					}
					else if (m_type == MOTION_PLAYER_TYPE_DIVE_LAND)
					{
						D3DXVECTOR3 movePlayer = pPlayer->GetMove();
						if (movePlayer.x == 0.0f && movePlayer.z == 0.0f)
						{
							//���̃��[�V�������j���[�g�������[�V�����ɂ���
							SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
						}
						else
						{
							//���̃��[�V�������ړ����[�V�����ɂ���
							SetMotion(MOTION_PLAYER_TYPE_MOVE);
						}
					}
					else
					{
						//���̃��[�V�������j���[�g�������[�V�����ɂ���
						SetMotion(MOTION_PLAYER_TYPE_NEUTRAL);
					}
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
		float nMaxFrame = 10.0f;
		
		if (m_fCounter >= nMaxFrame)
		{
			m_bConnect = false;
			m_fCounter = 0.0f;
			m_nKey = 0;
			//���݂̃��[�V�����̎�ނ����̃��[�V�����̎�ނɂ���
			m_type = m_typeNext;
		}
	}
}

//================================================
//��������
//================================================
CMotionPlayer *CMotionPlayer::Create(CPlayer *pPlayer)
{
	//�C���X�^���X�̐���
	CMotionPlayer *pMotionPlayer = NULL;
	if (pMotionPlayer == NULL)
	{
		pMotionPlayer = new CMotionPlayer;
		if (pMotionPlayer != NULL)
		{
			pMotionPlayer->Init(pPlayer);
		}
	}
	return pMotionPlayer;
}


//================================================
//���[�V�����ݒ菈��
//================================================
void CMotionPlayer::SetMotion(MOTION_PLAYER_TYPE type)
{
	m_typeNext = type;
	m_bConnect = true;
	m_fCounter = 0.0f;
}

//================================================
//���[�V�����擾����
//================================================
CMotionPlayer::MOTION_PLAYER_TYPE CMotionPlayer::GetMotion(void)
{
	return m_type;
}


//================================================
//���[�V�������Ȃ��Ă���Œ����ǂ����擾����
//================================================
bool CMotionPlayer::GetConnect(void)
{
	return m_bConnect;
}