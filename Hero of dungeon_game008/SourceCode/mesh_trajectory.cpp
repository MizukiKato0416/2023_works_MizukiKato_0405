//================================================
//���b�V���O�Տ���
//Author:KatoMizuki
//================================================
#include "renderer.h"
#include "mesh_trajectory.h"
#include "object3D.h"
#include "manager.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CMeshTrajectory::CMeshTrajectory(int nPriority):CObject(nPriority)
{
	m_aPosPoint.clear();
	m_aColPoint.clear();
	m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_aOffset[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	m_nLine = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================

//================================================
//�f�X�g���N�^
//================================================
CMeshTrajectory::~CMeshTrajectory()
{

}

//================================================
//����������
//================================================
HRESULT CMeshTrajectory::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CObject::OBJTYPE::TRAJECTORY);

	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntMtx = 0; nCntMtx < 2; nCntMtx++)
	{
		D3DXMATRIX mtxTrans, mtx;					//�v�Z�p�}�g���b�N�X
		D3DXMatrixIdentity(&m_aMtxPoint[nCntMtx]);	//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtx);					//���[���h�}�g���b�N�X�̏�����

													//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_aOffset[nCntMtx].x, m_aOffset[nCntMtx].y, m_aOffset[nCntMtx].z);
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], &mtxTrans);

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], m_pMtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtx);
	}

	//���[�̒��_���W�ƒ��_�J���[����
	for (int nCntVtx = 0; nCntVtx < m_nLine + 1; nCntVtx++)
	{
		//���I�m��
		m_aColPoint.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aColPoint.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_aPosPoint.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_aPosPoint.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_aPosPoint[nCntVtx * 2] = D3DXVECTOR3(m_aMtxPoint[0]._41, m_aMtxPoint[0]._42, m_aMtxPoint[0]._43);
		m_aPosPoint[nCntVtx * 2 + 1] = D3DXVECTOR3(m_aMtxPoint[1]._41, m_aMtxPoint[1]._42, m_aMtxPoint[1]._43);
		m_aColPoint[nCntVtx * 2] = m_aCol[0];
		m_aColPoint[nCntVtx * 2 + 1] = m_aCol[1];
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * (m_nLine + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	int nNum = 0;
	for (int nVertical = 0; nVertical < 2; nVertical++)
	{
		for (int nLine = 0; nLine < m_nLine + 1; nLine++, nNum++)
		{
			//�ʒu
			pVtx[nNum].pos = m_aPosPoint[nNum];
			//�J���[
			pVtx[nNum].col = m_aColPoint[nNum];
			//�@��
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	nNum = 0;
	for (int nLine = 0; nLine < m_nLine + 1; nLine++)
	{
		//�e�N�X�`��
		pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / m_nLine * nLine), 0.0f);
		pVtx[nNum + 1].tex = D3DXVECTOR2(0.0f + (1.0f / m_nLine * nLine), 1.0f);
		nNum += 2;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I������
//================================================
void CMeshTrajectory::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CMeshTrajectory::Update(void)
{
	
}

//================================================
//�`�揈��
//================================================
void CMeshTrajectory::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	for (int nCntMtx = 0; nCntMtx < 2; nCntMtx++)
	{
		D3DXMATRIX mtxTrans, mtx;					//�v�Z�p�}�g���b�N�X
		D3DXMatrixIdentity(&m_aMtxPoint[nCntMtx]);	//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtx);					//���[���h�}�g���b�N�X�̏�����

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_aOffset[nCntMtx].x, m_aOffset[nCntMtx].y, m_aOffset[nCntMtx].z);
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], &mtxTrans);

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&m_aMtxPoint[nCntMtx], &m_aMtxPoint[nCntMtx], m_pMtxParent);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtx);
	}

	

	//���_���W�ƒ��_�J���[�����炷
	for (int nCntVtx = m_nLine; nCntVtx > 0; nCntVtx--)
	{
		m_aPosPoint[nCntVtx * 2] = m_aPosPoint[(nCntVtx - 1) * 2];
		m_aPosPoint[nCntVtx * 2 + 1] = m_aPosPoint[(nCntVtx - 1) * 2 + 1];
		m_aColPoint[nCntVtx * 2].a = m_aCol[0].a / (m_nLine + 1) * (m_nLine - nCntVtx);
		m_aColPoint[nCntVtx * 2 + 1].a = m_aCol[1].a / (m_nLine + 1) * (m_nLine - nCntVtx);
	}

	//���[�̒��_���W�ƒ��_�J���[����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_aPosPoint[nCnt] = D3DXVECTOR3(m_aMtxPoint[nCnt]._41, m_aMtxPoint[nCnt]._42, m_aMtxPoint[nCnt]._43);
		m_aColPoint[nCnt] = m_aCol[nCnt];
	}

	VERTEX_3D *pVtx;	// ���_���
	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < (m_nLine + 1) * 2; nCntVtx++)
	{
		pVtx[nCntVtx].pos = m_aPosPoint[nCntVtx];
		pVtx[nCntVtx].col = m_aColPoint[nCntVtx];
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �J�����O���s��Ȃ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				

	//�A���t�@�e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 50);


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);					//���_�t�H�[�}�b�g�̐ݒ�
	
	pDevice->SetTexture(0, m_pTexture);				//�e�N�X�`���̐ݒ�
	
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�J�n���钸�_�̃C���f�b�N�X
		m_nLine);									//�`�悷��v���~�e�B�u��

	//�A���t�@�e�X�g���ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// �J�����O���s��
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				
}

//================================================
//��������
//================================================
CMeshTrajectory* CMeshTrajectory::Create(int nLine, D3DXMATRIX *pMtx, D3DXVECTOR3 offset1, D3DXVECTOR3 offset2, D3DXCOLOR col1, D3DXCOLOR col2)
{
	//�C���X�^���X�̐���
	CMeshTrajectory *pMeshTrajectory = nullptr;
	if (pMeshTrajectory == nullptr)
	{
		pMeshTrajectory = new CMeshTrajectory;
		if (pMeshTrajectory != nullptr)
		{
			//�ϐ�������
			pMeshTrajectory->m_nLine = nLine;
			pMeshTrajectory->m_pMtxParent = pMtx;
			pMeshTrajectory->m_aOffset[0] = offset1;
			pMeshTrajectory->m_aOffset[1] = offset2;
			pMeshTrajectory->m_aCol[0] = col1;
			pMeshTrajectory->m_aCol[1] = col2;
			//����������
			pMeshTrajectory->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}
	return pMeshTrajectory;
}

//================================================
//�e�N�X�`�����蓖�ď���
//================================================
void CMeshTrajectory::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//================================================
//���Ɗe���_�Ƃ̏Փ˔���
//================================================
bool CMeshTrajectory::CollisionSphere(CObject *pSubjectObject, float fObjectRadius)
{
	//�Փ˂��Ă��邩�ǂ���
	bool bColl = false;
	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_TRAJECTORY);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��G��������
		if (pObject->GetObjType() == CObject::OBJTYPE::TRAJECTORY)
		{
			//���b�V���O�ՂɃL���X�g
			CMeshTrajectory *pMeshTrajectory = nullptr;
			pMeshTrajectory = (CMeshTrajectory*)pObject;

			//�I�u�W�F�N�g�̈ʒu���擾
			D3DXVECTOR3 posObj = pSubjectObject->GetPos();

			for (int nCntVtx = 0; nCntVtx < 2; nCntVtx++)
			{
				//���g����Ώۂ̃I�u�W�F�N�g�܂ł̋��������߂�
				float fRadius = sqrtf((posObj.x - pMeshTrajectory->m_aPosPoint[nCntVtx].x) * (posObj.x - pMeshTrajectory->m_aPosPoint[nCntVtx].x) +
										(posObj.z - pMeshTrajectory->m_aPosPoint[nCntVtx].z) * (posObj.z - pMeshTrajectory->m_aPosPoint[nCntVtx].z));

				//���߂������������̐��l�ȉ���������
				if (fRadius <= fObjectRadius)
				{
					//�Փ˂��Ă���
					bColl = true;
					return bColl;
				}
			}
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}
	return bColl;
}

