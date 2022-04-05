//=======================================================================
//�J�����Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#include "main.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "play_data.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CCamera::CCamera()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̃J�����̌���
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�@��
	m_rotDiffer = 0.0f;								//�ړI�ƌ����̍�
	m_viewport.X = (DWORD)0.0f;						//�`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)0.0f;						//�`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;							//�`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 0.0f;							//�`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)0.0f;					//�`�悷���ʂ̕�
	m_viewport.Height = (DWORD)0.0f;				//�`�悷���ʂ̍���
	m_bTurn = false;								//�J��������]���Ă��邩�ǂ���
	m_nNum = 0;										//camera�̌̎��ʔԍ�
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CCamera::~CCamera()
{

}

//================================================
//����������
//================================================
HRESULT CCamera::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight)
{
	m_rot = rot;																	//�J�����̌���
	m_rotAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ړI�̃J�����̌���
	m_posV = pos;																	//���݂̎��_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ړI�̎��_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);											//���݂̒����_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);											//�@��
	m_rotDiffer = 0.0f;																//�ړI�ƌ����̍�
	m_viewport.X = (DWORD)viewportX;												//�`�悷���ʂ̍���X���W
	m_viewport.Y = (DWORD)viewportY;												//�`�悷���ʂ̍���Y���W
	m_viewport.MinZ = 0.0f;															//�`�悷��z���W�͈̔͂̍ŏ��l
	m_viewport.MaxZ = 1.0f;															//�`�悷��z���W�͈̔͂̍ő�l
	m_viewport.Width = (DWORD)viewportWidth;										//�`�悷���ʂ̕�
	m_viewport.Height = (DWORD)viewporHeight;										//�`�悷���ʂ̍���
	m_bTurn = false;																//�J��������]���Ă��邩�ǂ���


	return S_OK;
}

//================================================
//�I������
//================================================
void CCamera::Uninit(void)
{
	
}

//================================================
//�X�V����
//================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�I�u�W�F�N�g��������|�C���^
	CScene *pObject = NULL;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CScene *pSaveObject = NULL;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CScene::PRIORITY_MODEL);
	while (pObject != NULL)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;
		if (pObject->GetObjType() == CScene::OBJTYPE_PLAYER)
		{
			//�v���C���[�̃N���X�ɃL���X�g
			CPlayer *pPlayer = NULL;
			pPlayer = (CPlayer*)pObject;

			if (CManager::GetResult() != NULL)
			{
				if (pPlayer->GetNum() == CManager::GetPlayData()->GetWinNum())
				{
					//�v���C���[�̈ʒu�擾
					D3DXVECTOR3 pos = pPlayer->GetPos();
					m_posR = D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z);
				}
			}
			else
			{
				//�v���C���[�ɒǏ]������
				D3DXVECTOR3 pos = pPlayer->GetPos();
				//�̎��ʔԍ�����v���Ă�����
				if (m_nNum == pPlayer->GetNum())
				{
					m_posR = pos;
					//�v���C���[�̈ړ��ʂ����Z
					D3DXVECTOR3 move = pPlayer->GetMove();
					m_posV.y += move.y;

					//================================================
					//�E�X�e�B�b�N����
					//================================================
					if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_LEFT, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_LEFT) == true && m_nNum == 0))
					{
						m_rot.y -= CAMERA_R_SPEED;
						m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
						m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;

					}
					else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_RIGHT, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_RIGHT) == true && m_nNum == 0))
					{
						m_rot.y += CAMERA_R_SPEED;
						m_posV.x = m_posR.x + sinf(m_rot.y) * CAMERA_DISTANCE;
						m_posV.z = m_posR.z + cosf(m_rot.y) * CAMERA_DISTANCE;
					}
					if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_UP, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_UP) == true && m_nNum == 0))
					{
						m_posV.y += CAMERA_VR_SPEED;
						if (m_posV.y >= CAMERA_V_MAX_POS_Y)
						{
							m_posV.y = CAMERA_V_MAX_POS_Y;
						}
					}
					else if (pInputPadX->GetRightStick(CInputPadX::STICKTYPE_DOWN, m_nNum) == true && m_bTurn == false ||
						(pInputKeyboard->GetPress(DIK_DOWN) == true && m_nNum == 0))
					{
						m_posV.y -= CAMERA_VR_SPEED;
						if (m_posV.y <= CAMERA_V_MIN_POS_Y)
						{
							m_posV.y = CAMERA_V_MIN_POS_Y;
						}
					}
				}
			}
		}
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//���_�̏ꏊ�𒍎��_�����Ɉړ�
	float fDistance = CAMERA_DISTANCE;

	if (CManager::GetResult() != NULL)
	{
		fDistance = CAMERA_RESULT_DISTANCE;
	}
	m_posV.x = m_posR.x + sinf(m_rot.y) * fDistance;
	m_posV.z = m_posR.z + cosf(m_rot.y) * fDistance;

	if (m_bTurn == true)
	{
		if (m_rotAsk.y > D3DX_PI)
		{
			m_rotAsk.y = -D3DX_PI - (D3DX_PI - m_rotAsk.y);
		}
		else if (m_rotAsk.y < -D3DX_PI)
		{
			m_rotAsk.y = D3DX_PI - (-D3DX_PI - m_rotAsk.y);
		}

		if (m_rot.y < 0.0f && -m_rot.y + m_rotAsk.y > D3DX_PI)
		{
			m_rotDiffer = (-D3DX_PI - m_rot.y) + -(D3DX_PI - m_rotAsk.y);
		}
		else if (m_rot.y >= D3DX_PI / 2.0f && m_rot.y - m_rotAsk.y > D3DX_PI)
		{
			m_rotDiffer = (D3DX_PI - m_rot.y) - (-D3DX_PI - m_rotAsk.y);
		}
		else
		{
			m_rotDiffer = (m_rotAsk.y - m_rot.y);
		}

		m_rot.y += m_rotDiffer * 0.1f;
	}

	if (m_rot.y >= D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	else if (m_rot.y <= -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//================================================
//��������
//================================================
CCamera *CCamera::Create(D3DXVECTOR3 m_pos, D3DXVECTOR3 rot, float viewportX, float viewportY, float viewportWidth, float viewporHeight)
{
	//�C���X�^���X�̐���
	CCamera *pCamera = NULL;
	if (pCamera == NULL)
	{
		pCamera = new CCamera;
		if (pCamera != NULL)
		{
			pCamera->Init(m_pos, rot, viewportX, viewportY,viewportWidth, viewporHeight);
		}
	}
	return pCamera;
}


//=======================================================================
//�ݒ菈��
//=======================================================================
void CCamera::Set(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetRenderer()->GetDevice();

	

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								D3DXToRadian(50.0f),									//��p
								(float)m_viewport.Width / (float)m_viewport.Height,		//�䗦
								CAMERA_MIN_RENDERER,									//Z�����̕`��͈�
								CAMERA_MAX_RENDERER);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=======================================================================
//���_�擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//=======================================================================
//�����_�擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetPosR(void)
{
	return m_posR;
}

//=======================================================================
//���_�ݒ菈��
//=======================================================================
void CCamera::SetPosV(D3DXVECTOR3 pos)
{
	m_posV = pos;
}

//=======================================================================
//�����_�ݒ菈��
//=======================================================================
void CCamera::SetPosR(D3DXVECTOR3 pos)
{
	m_posR = pos;
}


//=======================================================================
//���_�̌����擾����
//=======================================================================
D3DXVECTOR3 CCamera::GetRotV(void)
{
	return m_rot;
}

//=======================================================================
//���_�̌����ݒ菈��
//=======================================================================
void CCamera::SetRotV(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=======================================================================
//camera�̌̎��ʔԍ��ݒ菈��
//=======================================================================
void CCamera::SetNum(int nNum)
{
	m_nNum = nNum;
}

//=======================================================================
//camera�̌̎��ʔԍ��擾����
//=======================================================================
int CCamera::GetNum(void)
{
	return m_nNum;
}