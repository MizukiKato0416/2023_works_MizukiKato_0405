//================================================
//�V�[������
//Author:��������
//================================================
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "pause.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
CScene *CScene::m_pTop[PRIORITY_MAX] = {};
CScene *CScene::m_pCur[PRIORITY_MAX] = {};

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CScene::CScene(int nPriority)
{
	if (m_pTop[nPriority] == NULL && m_pCur[nPriority] == NULL)
	{
		//�O�̃I�u�W�F�N�g��񂪂Ȃ����TOP�ɂ���
		m_pTop[nPriority] = this;
		//���̃I�u�W�F�N�g��񂪂Ȃ����CUR�ɂ���
		m_pCur[nPriority] = this;
		m_pPrev = NULL;
		m_pNext = NULL;
	}
	else
	{
		//�O�̃I�u�W�F�N�g��񂪂�������O�̃I�u�W�F�N�g�������Ă�����
		m_pPrev = m_pCur[nPriority];
		//�O�̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g�������̃I�u�W�F�N�g�ɂ���
		m_pCur[nPriority]->m_pNext = this;
		//��ԍŌ�ɂ���
		m_pCur[nPriority] = this;
		m_pNext = NULL;
	}
	m_objType = OBJTYPE_NONE;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nPriority = nPriority;
	m_bDeath = false;
}

//================================================
//�f�X�g���N�^
//================================================
CScene::~CScene()
{
	int nPriority = m_nPriority;

	//���̃I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	pObject = this;


	//�g�b�v�ł��J�����g�ł��Ȃ��ꍇ
	if (pObject != m_pTop[m_nPriority] && pObject != m_pCur[m_nPriority])
	{
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g���������̎��̃I�u�W�F�N�g���ɂ���
		pObject->m_pPrev->m_pNext = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g���������̑O�̃I�u�W�F�N�g���ɂ���
		pObject->m_pNext->m_pPrev = pObject->m_pPrev;
	}
	if (pObject == m_pTop[m_nPriority])
	{
		//�g�b�v��������g�b�v�����̃I�u�W�F�N�g�ɂ��炷
		m_pTop[m_nPriority] = pObject->m_pNext;
		//�����̎��̃I�u�W�F�N�g�������Ă���O�̃I�u�W�F�N�g����NULL�ɂ���
		if (pObject->m_pNext != NULL)
		{
			pObject->m_pNext->m_pPrev = NULL;
		}
	}
	if (pObject == m_pCur[m_nPriority])
	{
		//�J�����g��������J�����g��O�̃I�u�W�F�N�g�ɂ��炷
		m_pCur[m_nPriority] = pObject->m_pPrev;
		//�����̑O�̃I�u�W�F�N�g�������Ă��鎟�̃I�u�W�F�N�g����NULL�ɂ���
		if (pObject->m_pPrev != NULL)
		{
			pObject->m_pPrev->m_pNext = NULL;
		}
	}
}

//================================================
//�I������
//================================================
void CScene::ReleaseAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		if (nCntPriority != PRIORITY_FADE)
		{
			//�擪�̃|�C���^����
			pObject = m_pTop[nCntPriority];
			while (pObject != NULL)
			{
				//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
				pSaveObject = pObject;
				pObject->Uninit();
				if (pObject->m_bDeath == true)
				{
					//�j��
					delete pObject;
					pObject = NULL;
				}
				//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
				pObject = pSaveObject->m_pNext;
			}
		}
	}
}

//================================================
//�X�V����
//================================================
void CScene::UpdateAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			if (CPause::GetPause() == false)
			{
				pObject->Update();
			}
			else
			{
				if (nCntPriority == PRIORITY_FADE || nCntPriority == PRIORITY_PAUSE)
				{
					pObject->Update();
				}
			}
			pObject = pObject->m_pNext;
		}
	}


	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject;
			//���S�t���O�`�F�b�N
			if (pObject->m_bDeath == true)
			{
				//�j��
				delete pObject;
				pObject = NULL;
			}
			//���̃I�u�W�F�N�g�̃|�C���^�ɂ���
			pObject = pSaveObject->m_pNext;
		}
	}
}

//================================================
//�`�揈��
//================================================
void CScene::DrawAll(void)
{
	//���̃I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�擪�̃|�C���^����
		pObject = m_pTop[nCntPriority];
		while (pObject != NULL)
		{
			//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
			pSaveObject = pObject;
			pObject->Draw();
			pObject = pSaveObject->m_pNext;
		}
	}
}

//================================================
//�P�̂�j�����鏈��
//================================================
void CScene::Release(void)
{
	m_bDeath = true;	
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
//�����̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾����
//================================================
CScene *CScene::GetObjNext(CScene *pObject)
{
	return pObject->m_pNext;
}

//================================================
//�I�u�W�F�N�g�擾����
//================================================
CScene *CScene::GetTopObj(int nPriority)
{
	return m_pTop[nPriority];
}

//================================================
//�ʒu�擾����
//================================================
D3DXVECTOR3 CScene::GetPos(void)
{
	return m_pos;
}

//================================================
//1�t���[���O�̈ʒu�ݒ菈��
//================================================
void CScene::SetPosOld(D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}

//================================================
//1�t���[���O�̈ʒu�擾����
//================================================
D3DXVECTOR3 CScene::GetPosOld(void)
{
	return m_posOld;
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