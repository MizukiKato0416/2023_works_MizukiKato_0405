//================================================
//���[�V�����ǂݍ��ݏ���
//Author:KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "motion_road.h"
#include "player.h"
#include "enemy_bee.h"
#include "enemy_fat.h"
#include "enemy_boss.h"

//================================================
//�}�N����`
//================================================
#define MOTION_MAX_STRING	(128)	//������̍ő�l

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMotionRoad::CMotionRoad()
{
	//���[�V�����ő吔�ۑ��p�ϐ�
	int nMotionTypeMax = 0;
	//���f���̐��ۑ��p�ϐ�
	int nModelMax = 0;

	//���[�V�����������Ă���I�u�W�F�N�g�̎�ނ̐�������
	for (int nCntMotionHaveType = 0; nCntMotionHaveType < MOTION_HAVE_TYPE_MAX; nCntMotionHaveType++)
	{
		//���[�V�����������Ă���I�u�W�F�N�g�̎�ނɂ���ă��[�V�����ő吔�ƃ��f���ő吔��ς���
		switch (nCntMotionHaveType)
		{
		case MOTION_HAVE_TYPE_PLAYER:		//�v���C���[�̏ꍇ
			nMotionTypeMax = MOTION_PLAYER_TYPE_MAX;
			nModelMax = MAX_PLAYER_MODEL;
			break;
		case MOTION_HAVE_TYPE_ENEMY_BEE:	//�I�^�G�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_BEE_TYPE_MAX;
			nModelMax = MAX_ENEMY_BEE_MODEL;
			break;
		case MOTION_HAVE_TYPE_ENEMY_FAT:	//���^�G�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_FAT_TYPE_MAX;
			nModelMax = MAX_ENEMY_FAT_MODEL;
			break;
		case MOTION_HAVE_TYPE_ENEMY_BOSS:	//�{�X�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_BOSS_TYPE_MAX;
			nModelMax = MAX_ENEMY_BOSS_MODEL;
			break;
		default:
			break;
		}

		//���[�V�����̐�������
		for (int nCntMotionRoad = 0; nCntMotionRoad < nMotionTypeMax; nCntMotionRoad++)
		{
			//���[�V�����̏�������ϐ��𓮓I�Ɋm��
			m_aInfo[nCntMotionHaveType].push_back({});
			//������
			m_aInfo[nCntMotionHaveType][nCntMotionRoad].bLoop = false;
			m_aInfo[nCntMotionHaveType][nCntMotionRoad].nNumKey = 0;

			//�L�[�̐�����
			for (int nCntKey = 0; nCntKey < MOTION_MAX_KEY_INFO; nCntKey++)
			{
				//������
				m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].nFrame = 0;

				//���f���̐�����
				for (int nCntModel = 0; nCntModel < nModelMax; nCntModel++)
				{
					//���f���̐����K�v�ȕϐ��𓮓I�m��
					m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey.push_back({});

					//������
					m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}
}

//================================================
//�f�X�g���N�^
//================================================
CMotionRoad::~CMotionRoad()
{

}

//================================================
//����������
//================================================
HRESULT CMotionRoad::Init(void)
{
	//text�t�@�C���ǂݍ��݂悤�ϐ�
	FILE *pfile = nullptr;
	//������ۑ��p�ϐ�
	char cString[MOTION_MAX_STRING];
	//���[�V�����ő吔�ۑ��p�ϐ�
	int nMotionTypeMax = 0;
	//���f���̐��ۑ��p�ϐ�
	int nModelMax = 0;

	//���[�V�����������Ă���I�u�W�F�N�g�̎�ނ̐�������
	for (int nCntMotionHaveType = 0; nCntMotionHaveType < MOTION_HAVE_TYPE_MAX; nCntMotionHaveType++)
	{
		//���[�V�����������Ă���I�u�W�F�N�g�̎�ނɂ���ă��[�V�����ő吔�A���f���ő吔�A�ǂݍ��ރt�@�C����ς���
		switch (nCntMotionHaveType)
		{
		case MOTION_HAVE_TYPE_PLAYER:		//�v���C���[�̏ꍇ
			nMotionTypeMax = MOTION_PLAYER_TYPE_MAX;
			nModelMax = MAX_PLAYER_MODEL;
			pfile = fopen("data/MOTION/motion_player.txt", "r");
			break;
		case MOTION_HAVE_TYPE_ENEMY_BEE:	//�I�^�G�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_BEE_TYPE_MAX;
			nModelMax = MAX_ENEMY_BEE_MODEL;
			pfile = fopen("data/MOTION/motion_enemy_bee.txt", "r");
			break;
		case MOTION_HAVE_TYPE_ENEMY_FAT:	//���^�G�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_FAT_TYPE_MAX;
			nModelMax = MAX_ENEMY_FAT_MODEL;
			pfile = fopen("data/MOTION/motion_enemy_fat.txt", "r");
			break;
		case MOTION_HAVE_TYPE_ENEMY_BOSS:	//�{�X�̏ꍇ
			nMotionTypeMax = MOTION_ENEMY_BOSS_TYPE_MAX;
			nModelMax = MAX_ENEMY_BOSS_MODEL;
			pfile = fopen("data/MOTION/motion_enemy_boss.txt", "r");
			break;
		default:
			break;
		}

		//���[�V�����̓ǂݍ���
		for (int nCntMotionRoad = 0; nCntMotionRoad < nMotionTypeMax; nCntMotionRoad++)
		{
			//��s���ۑ�
			while (fgets(cString, MOTION_MAX_STRING, pfile) != nullptr)
			{
				//�������ۑ�
				fscanf(pfile, "%s", cString);
				//������̒���MOTIONSET����������
				if (strncmp("MOTIONSET", cString, 10) == 0)
				{
					//���[�v���̎擾
					//�L�[���̎擾
					fscanf(pfile, "%s%*s%d%*s%*s%*s%*s", cString, (int*)&m_aInfo[nCntMotionHaveType][nCntMotionRoad].bLoop);
					fscanf(pfile, "%s%*s%d", cString, &m_aInfo[nCntMotionHaveType][nCntMotionRoad].nNumKey);
					break;
				}
			}

			for (int nCntKey = 0; nCntKey < m_aInfo[nCntMotionHaveType][nCntMotionRoad].nNumKey; nCntKey++)
			{
				while (fgets(cString, MOTION_MAX_STRING, pfile) != nullptr)
				{
					//�������ۑ�
					fscanf(pfile, "%s", cString);
					//������̒���FRAME����������
					if (strncmp("FRAME", cString, 6) == 0)
					{
						//�t���[�����̎擾
						fscanf(pfile, "%s%d", cString, &m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].nFrame);
						break;
					}
				}

				for (int nCntModel = 0; nCntModel < nModelMax; nCntModel++)
				{
					while (fgets(cString, MOTION_MAX_STRING, pfile) != nullptr)
					{
						//�������ۑ�
						fscanf(pfile, "%s", cString);
						//������̒���POS����������
						if (strncmp("POS", cString, 4) == 0)
						{
							//�ʒu�A��]���̎擾
							fscanf(pfile, "%s%f%f%f", cString, &m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].pos.x,
								&m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].pos.y,
								&m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].pos.z);
							fscanf(pfile, "%s%*s%f%f%f%*s", cString, &m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].rot.x,
								&m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].rot.y,
								&m_aInfo[nCntMotionHaveType][nCntMotionRoad].aKeyInfo[nCntKey].aKey[nCntModel].rot.z);
							break;
						}
					}
				}

				while (fgets(cString, MOTION_MAX_STRING, pfile) != nullptr)
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

			while (fgets(cString, MOTION_MAX_STRING, pfile) != nullptr)
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
	}
	return S_OK;
}

//================================================
//�I������
//================================================
void CMotionRoad::Uninit(void)
{
	
}

//================================================
//��������
//================================================
CMotionRoad *CMotionRoad::Create(void)
{
	//�C���X�^���X�̐���
	CMotionRoad *pMotionRoad = nullptr;
	if (pMotionRoad == nullptr)
	{
		pMotionRoad = new CMotionRoad;
		if (pMotionRoad != nullptr)
		{
			pMotionRoad->Init();
		}
	}
	return pMotionRoad;
}

//================================================
//���[�V�������擾����
//================================================
MOTION_INFO CMotionRoad::GetMotionInfo(MOTION_HAVE_TYPE motionHaveType, int nMotionType)
{
	return m_aInfo[motionHaveType][nMotionType];
}

//================================================
//���[�V�������->�L�[���->�Đ��t���[���擾����
//================================================
int CMotionRoad::GetMotionKeyInfoFrame(MOTION_HAVE_TYPE motionHaveType, int nMotionType, int nCntKey)
{
	return m_aInfo[motionHaveType][nMotionType].aKeyInfo[nCntKey].nFrame;
}

//================================================
//���[�V�������->�L�[���->�ʒu�擾����
//================================================
D3DXVECTOR3 CMotionRoad::GetMotionKeyInfoPos(MOTION_HAVE_TYPE motionHaveType, int nMotionType, int nCntKey, int nCntModel)
{
	return m_aInfo[motionHaveType][nMotionType].aKeyInfo[nCntKey].aKey[nCntModel].pos;
}

//================================================
//���[�V�������->�L�[���->��]�擾����
//================================================
D3DXVECTOR3 CMotionRoad::GetMotionKeyInfoRot(MOTION_HAVE_TYPE motionHaveType, int nMotionType, int nCntKey, int nCntModel)
{
	return m_aInfo[motionHaveType][nMotionType].aKeyInfo[nCntKey].aKey[nCntModel].rot;
}

//================================================
//���[�V�������->�L�[���->�ʒu�Ɖ�]�ݒ菈��
//================================================
void CMotionRoad::SetMotionKeyInfoPosRot(MOTION_HAVE_TYPE motionHaveType, int nMotionType, int nCntKey, int nCntModel, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_aInfo[motionHaveType][nMotionType].aKeyInfo[nCntKey].aKey[nCntModel].pos = pos;
	m_aInfo[motionHaveType][nMotionType].aKeyInfo[nCntKey].aKey[nCntModel].rot = rot;
}