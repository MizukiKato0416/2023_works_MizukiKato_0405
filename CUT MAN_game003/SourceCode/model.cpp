//=======================================================================
//���f���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
MODEL g_aModel[MAX_MODEL];						//���f���̍\����
int g_nCntModel;

//=======================================================================
//����������
//=======================================================================
void InitModel(void)
{

	//������
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		g_aModel[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModel[nCntModel].nIdxModelParent = 0;
		g_aModel[nCntModel].bUse = false;
		g_aModel[nCntModel].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModel[nCntModel].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_aModel[nCntModel].nNum = 0;
	}

	
	

	//�e�̐ݒ�
}

//=======================================================================
//�I������
//=======================================================================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//���b�V���̔j��
		if (g_aModel[nCntModel].pMesh != NULL)
		{
			g_aModel[nCntModel].pMesh->Release();
			g_aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aModel[nCntModel].pBuffMat != NULL)
		{
			g_aModel[nCntModel].pBuffMat->Release();
			g_aModel[nCntModel].pBuffMat = NULL;
		}

		//�e�N�X�`���̔j��
		for (int nCntTex = 0; nCntTex < MODEL_MAX_TEXTURE; nCntTex++)
		{
			if (g_aModel[nCntModel].pTexture[nCntTex] != NULL)
			{
				g_aModel[nCntModel].pTexture[nCntTex]->Release();
				g_aModel[nCntModel].pTexture[nCntTex] = NULL;
			}
		}
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateModel(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{

		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (g_aModel[nCntModel].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

			D3DXMatrixIdentity(&g_aModel[nCntModel].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

																	//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCntModel].rot.y, g_aModel[nCntModel].rot.x, g_aModel[nCntModel].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCntModel].pos.x, g_aModel[nCntModel].pos.y, g_aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCntModel].mtxWorld, &g_aModel[nCntModel].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCntModel].mtxWorld);

			//���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[nCntModel].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCntModel].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aModel[nCntModel].pTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aModel[nCntModel].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE Type)
{
	if (g_aModel[g_nCntModel].bUse == false)
	{
		g_aModel[g_nCntModel].rot = rot;
		g_aModel[g_nCntModel].pos = pos;

		g_aModel[g_nCntModel].Type = Type;

		g_aModel[g_nCntModel].bUse = true;

		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		//X�t�@�C���ǂݍ���
		if (g_aModel[g_nCntModel].Type == BUILDING_HIGH)
		{
			D3DXLoadMeshFromX("data/MODEL/building002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_HIGH_02)
		{
			D3DXLoadMeshFromX("data/MODEL/building003.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_LOW)
		{
			D3DXLoadMeshFromX("data/MODEL/building001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == BUILDING_LOW_02)
		{
			D3DXLoadMeshFromX("data/MODEL/building004.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}
		else if (g_aModel[g_nCntModel].Type == CAR)
		{
			D3DXLoadMeshFromX("data/MODEL/car000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aModel[g_nCntModel].pBuffMat, NULL, &g_aModel[g_nCntModel].nNumMat, &g_aModel[g_nCntModel].pMesh);
		}

		//�e�N�X�`���f�[�^�̎擾
		D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

								//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL *)g_aModel[g_nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModel[g_nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModel[g_nCntModel].pTexture[nCntMat]);
			}
		}
		//���_���̎擾
		int nNumVtx;		//���_��
		DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

							//���_�����擾
		nNumVtx = g_aModel[g_nCntModel].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModel[g_nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_aModel[g_nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			//�S�Ă̒��_���r���čő�l�ƍŏ���𔲂��o��
			//�ő�l
			if (vtx.x >= g_aModel[g_nCntModel].vtxMax.x)
			{
				g_aModel[g_nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.y >= g_aModel[g_nCntModel].vtxMax.y)
			{
				g_aModel[g_nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.z >= g_aModel[g_nCntModel].vtxMax.z)
			{
				g_aModel[g_nCntModel].vtxMax.z = vtx.z;
			}
			//�ŏ��l
			if (vtx.x <= g_aModel[g_nCntModel].vtxMin.x)
			{
				g_aModel[g_nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y <= g_aModel[g_nCntModel].vtxMin.y)
			{
				g_aModel[g_nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z <= g_aModel[g_nCntModel].vtxMin.z)
			{
				g_aModel[g_nCntModel].vtxMin.z = vtx.z;
			}

			g_aModel[g_nCntModel].fWidth = g_aModel[g_nCntModel].vtxMax.x - g_aModel[g_nCntModel].vtxMin.x;
			g_aModel[g_nCntModel].fHeight = g_aModel[g_nCntModel].vtxMax.y - g_aModel[g_nCntModel].vtxMin.y;
			g_aModel[g_nCntModel].fDepth = g_aModel[g_nCntModel].vtxMax.z - g_aModel[g_nCntModel].vtxMin.z;


			pVtxBuff += sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aModel[g_nCntModel].pMesh->UnlockVertexBuffer();
	}
	g_nCntModel++;
	if (g_nCntModel >= MAX_MODEL)
	{
		g_nCntModel = 0;
	}
}

//=======================================================================
//���f���Ƃ̓����蔻��
//=======================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	
	bool bLand = false;			//���n���Ă��邩�ǂ���
	MODEL *pModel;
	pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++, pModel++)
	{
		if (pModel->bUse == true)
		{
			if (pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pModel->pos.y + pModel->fHeight &&
				pBeforePos->y >= pModel->pos.y + pModel->fHeight)
			{
				pPos->y = pModel->pos.y + pModel->fHeight;
				pMove->y = 0.0f;
				bLand = true;
			}
			else if (pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->y >= pModel->pos.y - fHeight &&
					pBeforePos->y <= pModel->pos.y - fHeight)
			{
				pPos->y = pModel->pos.y - fHeight;
			}

			if (pPos->y < pModel->pos.y + pModel->fHeight &&
				pPos->y > pModel->pos.y - fHeight &&
				pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pModel->pos.y + pModel->fHeight &&
					pPos->y > pModel->pos.y - fHeight &&
					pPos->z > pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->x <= pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pBeforePos->x >= pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pModel->pos.y + pModel->fHeight &&
				pPos->y > pModel->pos.y - fHeight &&
				pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pModel->pos.z - pModel->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pModel->pos.y + pModel->fHeight &&
					pPos->y > pModel->pos.y - fHeight &&
					pPos->x > pModel->pos.x - pModel->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pModel->pos.x + pModel->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z <= pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f &&
					pBeforePos->z >= pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pModel->pos.z + pModel->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
	return bLand;
}

//=======================================================================
//�擾����
//=======================================================================
MODEL *GetModel(void)
{
	return &g_aModel[0];
}
