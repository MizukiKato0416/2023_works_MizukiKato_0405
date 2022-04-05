//================================================
//�V�[������
//Authore:��������
//================================================
#include "scene.h"
#include "scene2D.h"
#include "game01.h"
#include "tutorial.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CScene *CScene::m_apScene[PRIORITY_MAX][MAX_SCENE] = {};
int CScene::m_nNumAll = 0;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScene::CScene(int nPriority)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_apScene[nPriority][nCntScene] == NULL)
		{
			m_apScene[nPriority][nCntScene] = this;
			m_nPriority = nPriority;
			m_objType = OBJTYPE_NONE;
			m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_nID = nCntScene;
			m_nNumAll++;
			break;
		}
	}
}

//================================================
//�f�X�g���N�^
//================================================
CScene::~CScene()
{

}

//================================================
//�I������
//================================================
void CScene::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (nCntPriority != PRIORITY_FADE)
				{
					m_apScene[nCntPriority][nCntScene]->Uninit();
					delete m_apScene[nCntPriority][nCntScene];
					m_apScene[nCntPriority][nCntScene] = NULL;
				}
			}
		}
	}
}

//================================================
//�X�V����
//================================================
void CScene::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				if (CManager::GetMode() == CManager::MODE_GAME01)
				{
					//�|�[�Y���擾
					if (CGame01::GetPause() == false)
					{//�|�[�Y���ł͂Ȃ��Ƃ�
						m_apScene[nCntPriority][nCntScene]->Update();
					}
					else
					{//�|�[�Y���̎�
						if (nCntPriority == PRIORITY_NONE || nCntPriority == PRIORITY_UI || nCntPriority == PRIORITY_FADE)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
					}
				}
				else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
				{
					//�|�[�Y���擾
					if (CManager::GetTutorial()->GetPause() == false)
					{//�|�[�Y���ł͂Ȃ��Ƃ�
						if (CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_CONTROL ||
							CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_SHOOT ||
							CManager::GetTutorial()->GetPhase() == CTutorial::TUTORIAL_PHASE_PLAYER_LEVEL_UP_SHOOT)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
						else
						{
							if (nCntPriority != PRIORITY_PLAYER)
							{
								m_apScene[nCntPriority][nCntScene]->Update();
							}
						}
					}
					else
					{//�|�[�Y���̎�
						if (nCntPriority == PRIORITY_NONE || nCntPriority == PRIORITY_UI || nCntPriority == PRIORITY_FADE)
						{
							m_apScene[nCntPriority][nCntScene]->Update();
						}
					}
				}
				else
				{
					m_apScene[nCntPriority][nCntScene]->Update();
				}
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CScene::DrawAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			if (m_apScene[nCntPriority][nCntScene] != NULL)
			{
				m_apScene[nCntPriority][nCntScene]->Draw();
			}
		}
	}
}

//================================================
//�I������
//================================================
void CScene::Release(void)
{
	if (m_apScene[m_nPriority][m_nID] != NULL)
	{
		int nID = m_nID;
		int nPriority = m_nPriority;

		//�C���X�^���X�̔j��
		delete m_apScene[nPriority][nID];
		m_apScene[nPriority][nID] = NULL;
		m_nNumAll--;
	}
}

//================================================
//�I�u�W�F�N�g�̎�ނ̐ݒ菈��
//================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//================================================
//�I�u�W�F�N�g�̎�ނ̐ݒ菈��
//================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//================================================
//�I�u�W�F�N�g�擾����
//================================================
CScene *CScene::GetScene(int nScene, int nPriority)
{
	return m_apScene[nPriority][nScene];
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

//================================================
//�ʒu�ݒ菈��
//================================================
void CScene::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//================================================
//�T�C�Y�擾����
//================================================
D3DXVECTOR3 CScene::GetSize(void)
{
	return m_size;
}

//================================================
//�T�C�Y�ݒ菈��
//================================================
void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}