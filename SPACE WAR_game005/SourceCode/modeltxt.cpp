//=======================================================================
//���f���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "main.h"
#include "modeltxt.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
MODELTXT g_aModelTxt[MAX_MODELTXT];						//���f���̍\����
int g_nCntModelTxt;
int g_MaxNumModel;			//���f���̍ő��

//=======================================================================
//����������
//=======================================================================
void InitModelTxt(void)
{

	//������
	for (int nCntModelTxt = 0; nCntModelTxt < MAX_MODELTXT; nCntModelTxt++)
	{
		g_aModelTxt[nCntModelTxt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModelTxt[nCntModelTxt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aModelTxt[nCntModelTxt].nIdxModelTxtParent = 0;
		g_aModelTxt[nCntModelTxt].bUse = false;
		g_aModelTxt[nCntModelTxt].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aModelTxt[nCntModelTxt].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_aModelTxt[nCntModelTxt].nNum = 0;
		g_aModelTxt[nCntModelTxt].nType = 0;
		for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
		{
			g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		for (int nCntVec = 0; nCntVec < 4; nCntVec++)
		{
			g_aModelTxt[nCntModelTxt].Vtx.fVecX[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecX2[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecZ[nCntVec] = 0.0f;
			g_aModelTxt[nCntModelTxt].Vtx.fVecZ2[nCntVec] = 0.0f;
		}
	}
	g_MaxNumModel = 0;
	g_nCntModelTxt = 0;
	//text�t�@�C���ǂݍ���
	FILE *pfile = fopen("data/STAGE/stage2.txt", "r");

	//���f���̎�ނ��擾
	char string[5][128];
	char cFileName[15][128];
	int nCntFileName = 0;
	int nCntModelTxt = 0;
	char NUM_MODEL[] = "NUM_MODEL";
	char MODEL_FILENAME[] = "MODEL_FILENAME";
	char MODELSET[] = "MODELSET";

	while (fgets(string[0], 255, pfile) != NULL)
	{
		fscanf(pfile, "%s", string[0]);
		if (strncmp(NUM_MODEL, string[0], 8) == 0)
		{
			fscanf(pfile, "%s%d", string[1], &g_MaxNumModel);
			break;
		}
	}
	while (fgets(string[0], 255, pfile) != NULL)
	{
		fscanf(pfile, "%s", string[0]);
		if (strncmp(MODEL_FILENAME, string[0], 13) == 0)
		{
			fscanf(pfile, "%s%s", string[1], cFileName[nCntFileName]);
			nCntFileName++;
			if (nCntFileName >= g_MaxNumModel)
			{
				break;
			}
		}
	}
	while (fgets(string[0], 255, pfile) != NULL)
	{
		if (strncmp(MODELSET, string[0], 7) == 0)
		{
			fscanf(pfile, "%s%s%d", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].nType);
			fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].pos.x, &g_aModelTxt[g_nCntModelTxt].pos.y, &g_aModelTxt[g_nCntModelTxt].pos.z);
			fscanf(pfile, "%s%s%f%f%f", string[1], string[2], &g_aModelTxt[g_nCntModelTxt].rot.x, &g_aModelTxt[g_nCntModelTxt].rot.y, &g_aModelTxt[g_nCntModelTxt].rot.z);
			fscanf(pfile, "%s", string[3]);
			g_aModelTxt[g_nCntModelTxt].rot.x *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.x;
			g_aModelTxt[g_nCntModelTxt].rot.y *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.y;
			g_aModelTxt[g_nCntModelTxt].rot.z *= D3DX_PI * 2.0f / 360.0f * g_aModelTxt[g_nCntModelTxt].rot.z;
			g_aModelTxt[g_nCntModelTxt].bUse = true;
			g_nCntModelTxt++;
		}
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//X�t�@�C���ǂݍ���
	for (int nCntModel = 0; nCntModel < g_nCntModelTxt; nCntModel++)
	{
		D3DXLoadMeshFromX(cFileName[g_aModelTxt[nCntModel].nType], D3DXMESH_SYSTEMMEM, pDevice, NULL,
			&g_aModelTxt[nCntModel].pBuffMat, NULL, &g_aModelTxt[nCntModel].nNumMat, &g_aModelTxt[nCntModel].pMesh);

		//�e�N�X�`���f�[�^�̎擾
		D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL *)g_aModelTxt[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aModelTxt[nCntModel].nNumMat; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_aModelTxt[nCntModel].pTexture[nCntMat]);
			}
		}
		//���_���̎擾
		int nNumVtx;		//���_��
		DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

		//���_�����擾
		nNumVtx = g_aModelTxt[nCntModel].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aModelTxt[nCntModel].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_aModelTxt[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

															//�S�Ă̒��_���r���čő�l�ƍŏ���𔲂��o��
															//�ő�l
			if (vtx.x >= g_aModelTxt[nCntModel].vtxMax.x)
			{
				g_aModelTxt[nCntModel].vtxMax.x = vtx.x;
			}
			if (vtx.y >= g_aModelTxt[nCntModel].vtxMax.y)
			{
				g_aModelTxt[nCntModel].vtxMax.y = vtx.y;
			}
			if (vtx.z >= g_aModelTxt[nCntModel].vtxMax.z)
			{
				g_aModelTxt[nCntModel].vtxMax.z = vtx.z;
			}
			//�ŏ��l
			if (vtx.x <= g_aModelTxt[nCntModel].vtxMin.x)
			{
				g_aModelTxt[nCntModel].vtxMin.x = vtx.x;
			}
			if (vtx.y <= g_aModelTxt[nCntModel].vtxMin.y)
			{
				g_aModelTxt[nCntModel].vtxMin.y = vtx.y;
			}
			if (vtx.z <= g_aModelTxt[nCntModel].vtxMin.z)
			{
				g_aModelTxt[nCntModel].vtxMin.z = vtx.z;
			}

			g_aModelTxt[nCntModel].fWidth = g_aModelTxt[nCntModel].vtxMax.x - g_aModelTxt[nCntModel].vtxMin.x;
			g_aModelTxt[nCntModel].fHeight = g_aModelTxt[nCntModel].vtxMax.y - g_aModelTxt[nCntModel].vtxMin.y;
			g_aModelTxt[nCntModel].fDepth = g_aModelTxt[nCntModel].vtxMax.z - g_aModelTxt[nCntModel].vtxMin.z;
			pVtxBuff += sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		g_aModelTxt[nCntModel].Vtx.pos[0].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[0].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[0].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[1].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[1].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[1].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[2].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[2].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[2].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[3].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[3].z = g_aModelTxt[nCntModel].vtxMax.z;
		g_aModelTxt[nCntModel].Vtx.pos[3].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[4].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[4].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[4].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[5].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[5].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[5].y = g_aModelTxt[nCntModel].vtxMax.y;
		g_aModelTxt[nCntModel].Vtx.pos[6].x = g_aModelTxt[nCntModel].vtxMin.x;
		g_aModelTxt[nCntModel].Vtx.pos[6].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[6].y = g_aModelTxt[nCntModel].vtxMin.y;
		g_aModelTxt[nCntModel].Vtx.pos[7].x = g_aModelTxt[nCntModel].vtxMax.x;
		g_aModelTxt[nCntModel].Vtx.pos[7].z = g_aModelTxt[nCntModel].vtxMin.z;
		g_aModelTxt[nCntModel].Vtx.pos[7].y = g_aModelTxt[nCntModel].vtxMin.y;
		//���_�o�b�t�@���A�����b�N
		g_aModelTxt[nCntModel].pMesh->UnlockVertexBuffer();
	}
}

//=======================================================================
//�I������
//=======================================================================
void UninitModelTxt(void)
{
	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		//���b�V���̔j��
		if (g_aModelTxt[nCntModelTxt].pMesh != NULL)
		{
			g_aModelTxt[nCntModelTxt].pMesh->Release();
			g_aModelTxt[nCntModelTxt].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aModelTxt[nCntModelTxt].pBuffMat != NULL)
		{
			g_aModelTxt[nCntModelTxt].pBuffMat->Release();
			g_aModelTxt[nCntModelTxt].pBuffMat = NULL;
		}

		//�e�N�X�`���̔j��
		for (int nCntTex = 0; nCntTex < MODELTXT_MAX_TEXTURE; nCntTex++)
		{
			if (g_aModelTxt[nCntModelTxt].pTexture[nCntTex] != NULL)
			{
				g_aModelTxt[nCntModelTxt].pTexture[nCntTex]->Release();
				g_aModelTxt[nCntModelTxt].pTexture[nCntTex] = NULL;
			}
		}
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateModelTxt(void)
{
	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		if (g_aModelTxt[nCntModelTxt].bUse == true)
		{

		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawModelTxt(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++)
	{
		if (g_aModelTxt[nCntModelTxt].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

			D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

																	//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].rot.y, g_aModelTxt[nCntModelTxt].rot.x, g_aModelTxt[nCntModelTxt].rot.z);
			D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].mtxWorld, &g_aModelTxt[nCntModelTxt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].pos.x, g_aModelTxt[nCntModelTxt].pos.y, g_aModelTxt[nCntModelTxt].pos.z);
			D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].mtxWorld, &g_aModelTxt[nCntModelTxt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].mtxWorld);

			//���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModelTxt[nCntModelTxt].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aModelTxt[nCntModelTxt].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aModelTxt[nCntModelTxt].pTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aModelTxt[nCntModelTxt].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);

			//8���_�̐ݒ�
			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxTrans);

				D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X
				mtxParent = g_aModelTxt[nCntModelTxt].mtxWorld;

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxParent);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);
			}
		}
	}
}

//=======================================================================
//���f���Ƃ̓����蔻��
//=======================================================================
void CollisionModelTxt(D3DXVECTOR3 *pMove, D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, float fWidth)
{
	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	float fVecX[4];					//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecZ[4];					//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecX2[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecZ2[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecXOld[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecZOld[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecXOld2[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecZOld2[4];				//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecAsk[4];				//�O�όv�Z���ʕۑ��p�ϐ�
	float fVecAsk2[4];				//�O�όv�Z���ʕۑ��p�ϐ�
	float fVecAskOld[4];			//�O�όv�Z���ʕۑ��p�ϐ�
	float fVecAskOld2[4];			//�O�όv�Z���ʕۑ��p�ϐ�
	float fRadius[4];				//�ΏۂƂ̋����v�Z���ʕۑ��p�ϐ�

	D3DXVECTOR3 nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�@���x�N�g��
	D3DXVECTOR3 norR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�p�ۂ̖@���x�N�g��
	D3DXVECTOR3 norRNomal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�ۂ̖@���x�N�g���𐳋K�������x�N�g��
	D3DXVECTOR3 norAsk = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�@���x�N�g�������߂邽�߂̃x�N�g��
	D3DXVECTOR3 norAsk2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�@���x�N�g�������߂邽�߂̃x�N�g��
	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�Ώۂ̃��[�u�x�N�g��
	D3DXVECTOR3 posVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�Ώۂ̉����o��������߂�x�N�g��
	D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�@����Ώۂ̑O�̈ʒu�܂ŐL�΂����x�N�g��
	D3DXVECTOR3 norVecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�ۖ@����Ώۂ̑O�̈ʒu�܂ŐL�΂����x�N�g��
	D3DXVECTOR3 posnorVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�@���̕����ɑΏۂ������߂��ʒu�����߂�x�N�g��
	D3DXVECTOR3 posnorVecR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�@���̕����ɑΏۂ������߂��ʒu�����߂�x�N�g��
	float VecNor = 0.0f;									//�Ώۂ̃��[�u�x�N�g���Ɩ@���̓���
	float VecNorR = 0.0f;									//�Ώۂ̃��[�u�x�N�g���Ɗp�ۖ@���̓���

	//������
	for (int nCntVec = 0; nCntVec < 4; nCntVec++)
	{
		fVecX[nCntVec] = 0.0f;
		fVecZ[nCntVec] = 0.0f;
		fVecX2[nCntVec] = 0.0f;
		fVecZ2[nCntVec] = 0.0f;
		fVecXOld[nCntVec] = 0.0f;
		fVecZOld[nCntVec] = 0.0f;
		fVecXOld2[nCntVec] = 0.0f;
		fVecZOld2[nCntVec] = 0.0f;
		fRadius[nCntVec] = 0.0f;
		fVecAsk[nCntVec] = 0.0f;
		fVecAsk2[nCntVec] = 0.0f;
		fVecAskOld[nCntVec] = 0.0f;
		fVecAskOld2[nCntVec] = 0.0f;
	}

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			//�p�ۂ̓����蔻��
			fRadius[0] = sqrt((pModelTxt->Vtx.mtxWorld[2]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[2]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[2]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[2]._43 - pPos->z));
			fRadius[1] = sqrt((pModelTxt->Vtx.mtxWorld[3]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[3]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[3]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[3]._43 - pPos->z));
			fRadius[2] = sqrt((pModelTxt->Vtx.mtxWorld[7]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[7]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[7]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[7]._43 - pPos->z));
			fRadius[3] = sqrt((pModelTxt->Vtx.mtxWorld[6]._41 - pPos->x) * (pModelTxt->Vtx.mtxWorld[6]._41 - pPos->x) +
				(pModelTxt->Vtx.mtxWorld[6]._43 - pPos->z) * (pModelTxt->Vtx.mtxWorld[6]._43 - pPos->z));

			//�p�ۂ̖@�������߂�
			if (fRadius[0] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[2]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[2]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[2]._43);
			}
			else if (fRadius[1] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[3]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[3]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[3]._43);
			}
			else if (fRadius[2] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[7]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[7]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[7]._43);
			}
			else if (fRadius[3] <= fWidth / 2.0f)
			{
				norR = D3DXVECTOR3(pPosOld->x - pModelTxt->Vtx.mtxWorld[6]._41,
									pPosOld->y - pModelTxt->Vtx.mtxWorld[6]._42,
									pPosOld->z - pModelTxt->Vtx.mtxWorld[6]._43);
			}
			D3DXVec3Normalize(&norRNomal, &norR);			//���K������(�x�N�g���̑傫����1�ɂ���)

			//�Ώۂ̕��̕��傫������
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].z -= fWidth / 2.0f;

			//�}�g���b�N�X�ɔ��f������
			LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
			pDevice = GetDevice();						//�f�o�C�X���擾����
			D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
														//8���_�̐ݒ�
			for (int nCntVtx = 0; nCntVtx < 8; nCntVtx++)
			{
				D3DXMatrixIdentity(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);		//���[���h�}�g���b�N�X�̏�����

																							//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.rot[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].x, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].y, g_aModelTxt[nCntModelTxt].Vtx.pos[nCntVtx].z);
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxTrans);

				D3DXMATRIX mtxParent;						//�e�̃}�g���b�N�X
				mtxParent = g_aModelTxt[nCntModelTxt].mtxWorld;

				//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃��[���h�}�g���b�N�X���|�����킹��
				D3DXMatrixMultiply(&g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx], &mtxParent);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aModelTxt[nCntModelTxt].Vtx.mtxWorld[nCntVtx]);
			}

			//�x�N�g�����o��
			pModelTxt->Vtx.fVecX[0] = pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[2]._41;
			pModelTxt->Vtx.fVecZ[0] = pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[2]._43;
			pModelTxt->Vtx.fVecX[1] = pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[3]._41;
			pModelTxt->Vtx.fVecZ[1] = pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[3]._43;
			pModelTxt->Vtx.fVecX[2] = pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[7]._41;
			pModelTxt->Vtx.fVecZ[2] = pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[7]._43;
			pModelTxt->Vtx.fVecX[3] = pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[6]._41;
			pModelTxt->Vtx.fVecZ[3] = pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[6]._43;

			//�Ώۂ̃x�N�g�����o��
			fVecX[0] = pPos->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZ[0] = pPos->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecX[1] = pPos->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZ[1] = pPos->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecX[2] = pPos->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZ[2] = pPos->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecX[3] = pPos->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZ[3] = pPos->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//�Ώۂ�1�t���[���O�̃x�N�g�����o��
			fVecXOld[0] = pPosOld->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZOld[0] = pPosOld->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecXOld[1] = pPosOld->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZOld[1] = pPosOld->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecXOld[2] = pPosOld->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZOld[2] = pPosOld->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecXOld[3] = pPosOld->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZOld[3] = pPosOld->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//�O�ς̌v�Z
			fVecAsk[0] = (pModelTxt->Vtx.fVecX[0] * fVecZ[0]) - (fVecX[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAsk[1] = (pModelTxt->Vtx.fVecX[1] * fVecZ[1]) - (fVecX[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAsk[2] = (pModelTxt->Vtx.fVecX[2] * fVecZ[2]) - (fVecX[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAsk[3] = (pModelTxt->Vtx.fVecX[3] * fVecZ[3]) - (fVecX[3] * pModelTxt->Vtx.fVecZ[3]);

			//1�t���[���O�̊O�ς̌v�Z
			fVecAskOld[0] = (pModelTxt->Vtx.fVecX[0] * fVecZOld[0]) - (fVecXOld[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAskOld[1] = (pModelTxt->Vtx.fVecX[1] * fVecZOld[1]) - (fVecXOld[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAskOld[2] = (pModelTxt->Vtx.fVecX[2] * fVecZOld[2]) - (fVecXOld[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAskOld[3] = (pModelTxt->Vtx.fVecX[3] * fVecZOld[3]) - (fVecXOld[3] * pModelTxt->Vtx.fVecZ[3]);

			//�ǂ̕ǂɂԂ����Ă��邩
			if (fVecAskOld[1] >= 0.0f && fVecAsk[1] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[5]._41 - pModelTxt->Vtx.mtxWorld[7]._41,
					pModelTxt->Vtx.mtxWorld[5]._42 - pModelTxt->Vtx.mtxWorld[7]._42,
					pModelTxt->Vtx.mtxWorld[5]._43 - pModelTxt->Vtx.mtxWorld[7]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[7]._41,
					pModelTxt->Vtx.mtxWorld[3]._42 - pModelTxt->Vtx.mtxWorld[7]._42,
					pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[7]._43);
			}
			else if (fVecAskOld[3] >= 0.0f && fVecAsk[3] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[0]._41 - pModelTxt->Vtx.mtxWorld[2]._41,
					pModelTxt->Vtx.mtxWorld[0]._42 - pModelTxt->Vtx.mtxWorld[2]._42,
					pModelTxt->Vtx.mtxWorld[0]._43 - pModelTxt->Vtx.mtxWorld[2]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[2]._41,
					pModelTxt->Vtx.mtxWorld[6]._42 - pModelTxt->Vtx.mtxWorld[2]._42,
					pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[2]._43);
			}
			else if (fVecAskOld[2] >= 0.0f && fVecAsk[2] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[4]._41 - pModelTxt->Vtx.mtxWorld[6]._41,
					pModelTxt->Vtx.mtxWorld[4]._42 - pModelTxt->Vtx.mtxWorld[6]._42,
					pModelTxt->Vtx.mtxWorld[4]._43 - pModelTxt->Vtx.mtxWorld[6]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[6]._41,
					pModelTxt->Vtx.mtxWorld[7]._42 - pModelTxt->Vtx.mtxWorld[6]._42,
					pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[6]._43);
			}
			else if (fVecAskOld[0] >= 0.0f && fVecAsk[0] < 0.0f)
			{
				norAsk = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[1]._41 - pModelTxt->Vtx.mtxWorld[3]._41,
					pModelTxt->Vtx.mtxWorld[1]._42 - pModelTxt->Vtx.mtxWorld[3]._42,
					pModelTxt->Vtx.mtxWorld[1]._43 - pModelTxt->Vtx.mtxWorld[3]._43);
				norAsk2 = D3DXVECTOR3(pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[3]._41,
					pModelTxt->Vtx.mtxWorld[2]._42 - pModelTxt->Vtx.mtxWorld[3]._42,
					pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[3]._43);
			}
			
			
			

			//���̑傫���ɖ߂�
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].z -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].z += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].z += fWidth / 2.0f;

			//���̑傫���ɖ߂�
			g_aModelTxt[nCntModelTxt].Vtx.pos[0].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[1].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[2].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[3].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[4].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[5].x -= fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[6].x += fWidth / 2.0f;
			g_aModelTxt[nCntModelTxt].Vtx.pos[7].x -= fWidth / 2.0f;

			
			//�@���x�N�g�������߂�
			D3DXVec3Cross(&nor, &norAsk, &norAsk2);
			D3DXVec3Normalize(&nor, &nor);			//���K������(�x�N�g���̑傫����1�ɂ���)

			//���[�u�x�N�g�������߂�
			moveVec = D3DXVECTOR3(pPos->x - pPosOld->x, pPos->y - pPosOld->y, pPos->z - pPosOld->z);

			//���[�u�x�N�g���Ɩ@���̓��ς����߂�
			VecNor = (-moveVec.x * nor.x) + (-moveVec.y * nor.y) + (-moveVec.z * nor.z);
			//VecNorR = (-moveVec.x * norR.x) + (-moveVec.y * norR.y) + (-moveVec.z * norR.z);

			//�@���̕����ɓ��ϕ��L�΂����x�N�g�������߂�
			norVec = D3DXVECTOR3(nor.x * VecNor, nor.y * VecNor, nor.z * VecNor);
			//norVecR = D3DXVECTOR3(norR.x * VecNorR, norR.y * VecNorR, norR.z * VecNorR);

			//�Ώۂ������߂��ʒu�̃x�N�g�������߂�
			posnorVec = D3DXVECTOR3(nor.x * fWidth / 2.0f, nor.y * fWidth / 2.0f, nor.z * fWidth / 2.0f);


			posnorVecR = D3DXVECTOR3(norRNomal.x * fWidth / 2.0f, norRNomal.y * fWidth / 2.0f, norRNomal.z * fWidth / 2.0f);

			//�����蔻��
			if (((fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f) &&
				(fVecAskOld[0] >= 0.0f || fVecAskOld[1] >= 0.0f || fVecAskOld[2] >= 0.0f || fVecAskOld[3] >= 0.0f)))
			{
				//�Ώۂ̉��o������߂�
				posVec.x = (moveVec.x + norVec.x);
				posVec.y = (moveVec.y + norVec.y);
				posVec.z = (moveVec.z + norVec.z);

				//�������Ă�
				pPos->x = pPosOld->x;
				pPos->z = pPosOld->z;
				pPos->x += posVec.x;
				pPos->z += posVec.z;
			}
		}
	}
}

//=======================================================================
//���f���Ƃ̓����蔻��false�ɂ���n
//=======================================================================
bool CollisionModelTxtBool(D3DXVECTOR3 *pPos)
{
	bool bColl = false;

	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	float fVecX[4];					//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecZ[4];					//�����蔻��̑Ώۂ̃x�N�g���ۑ��ϐ�
	float fVecAsk[4];				//�O�όv�Z���ʕۑ��p�ϐ�

									//������
	for (int nCntVec = 0; nCntVec < 4; nCntVec++)
	{
		fVecX[nCntVec] = 0.0f;
		fVecZ[nCntVec] = 0.0f;
		fVecAsk[nCntVec] = 0.0f;
	}

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			//�x�N�g�����o��
			pModelTxt->Vtx.fVecX[0] = pModelTxt->Vtx.mtxWorld[3]._41 - pModelTxt->Vtx.mtxWorld[2]._41;
			pModelTxt->Vtx.fVecZ[0] = pModelTxt->Vtx.mtxWorld[3]._43 - pModelTxt->Vtx.mtxWorld[2]._43;
			pModelTxt->Vtx.fVecX[1] = pModelTxt->Vtx.mtxWorld[7]._41 - pModelTxt->Vtx.mtxWorld[3]._41;
			pModelTxt->Vtx.fVecZ[1] = pModelTxt->Vtx.mtxWorld[7]._43 - pModelTxt->Vtx.mtxWorld[3]._43;
			pModelTxt->Vtx.fVecX[2] = pModelTxt->Vtx.mtxWorld[6]._41 - pModelTxt->Vtx.mtxWorld[7]._41;
			pModelTxt->Vtx.fVecZ[2] = pModelTxt->Vtx.mtxWorld[6]._43 - pModelTxt->Vtx.mtxWorld[7]._43;
			pModelTxt->Vtx.fVecX[3] = pModelTxt->Vtx.mtxWorld[2]._41 - pModelTxt->Vtx.mtxWorld[6]._41;
			pModelTxt->Vtx.fVecZ[3] = pModelTxt->Vtx.mtxWorld[2]._43 - pModelTxt->Vtx.mtxWorld[6]._43;

			//�Ώۂ̃x�N�g�����o��
			fVecX[0] = pPos->x - pModelTxt->Vtx.mtxWorld[2]._41;
			fVecZ[0] = pPos->z - pModelTxt->Vtx.mtxWorld[2]._43;
			fVecX[1] = pPos->x - pModelTxt->Vtx.mtxWorld[3]._41;
			fVecZ[1] = pPos->z - pModelTxt->Vtx.mtxWorld[3]._43;
			fVecX[2] = pPos->x - pModelTxt->Vtx.mtxWorld[7]._41;
			fVecZ[2] = pPos->z - pModelTxt->Vtx.mtxWorld[7]._43;
			fVecX[3] = pPos->x - pModelTxt->Vtx.mtxWorld[6]._41;
			fVecZ[3] = pPos->z - pModelTxt->Vtx.mtxWorld[6]._43;

			//�O�ς̌v�Z
			fVecAsk[0] = (pModelTxt->Vtx.fVecX[0] * fVecZ[0]) - (fVecX[0] * pModelTxt->Vtx.fVecZ[0]);
			fVecAsk[1] = (pModelTxt->Vtx.fVecX[1] * fVecZ[1]) - (fVecX[1] * pModelTxt->Vtx.fVecZ[1]);
			fVecAsk[2] = (pModelTxt->Vtx.fVecX[2] * fVecZ[2]) - (fVecX[2] * pModelTxt->Vtx.fVecZ[2]);
			fVecAsk[3] = (pModelTxt->Vtx.fVecX[3] * fVecZ[3]) - (fVecX[3] * pModelTxt->Vtx.fVecZ[3]);

			//�����蔻��
			if (fVecAsk[0] < 0.0f && fVecAsk[1] < 0.0f && fVecAsk[2] < 0.0f && fVecAsk[3] < 0.0f)
			{
				//�������Ă�
				bColl = true;
			}
		}
	}
	return bColl;
}


//=======================================================================
//���f���Ƃ̓����蔻��
//=======================================================================
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{

	bool bLand = false;				//���n���Ă��邩�ǂ���
	MODELTXT *pModelTxt;
	pModelTxt = GetModelTxt();

	for (int nCntModelTxt = 0; nCntModelTxt < g_nCntModelTxt; nCntModelTxt++, pModelTxt++)
	{
		if (pModelTxt->bUse == true)
		{
			if (pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pModelTxt->pos.y + pModelTxt->fHeight &&
				pBeforePos->y >= pModelTxt->pos.y + pModelTxt->fHeight)
			{
				pPos->y = pModelTxt->pos.y + pModelTxt->fHeight;
				pMove->y = 0.0f;
				bLand = true;
			}
			else if (pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y >= pModelTxt->pos.y - fHeight &&
				pBeforePos->y <= pModelTxt->pos.y - fHeight)
			{
				pPos->y = pModelTxt->pos.y - fHeight;
			}

			if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->z > pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x <= pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pBeforePos->x >= pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pModelTxt->pos.z - pModelTxt->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pModelTxt->pos.y + pModelTxt->fHeight &&
				pPos->y > pModelTxt->pos.y - fHeight &&
				pPos->x > pModelTxt->pos.x - pModelTxt->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pModelTxt->pos.x + pModelTxt->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z <= pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f &&
				pBeforePos->z >= pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pModelTxt->pos.z + pModelTxt->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
	return bLand;
}


//=======================================================================
//�擾����
//=======================================================================
MODELTXT *GetModelTxt(void)
{
	return &g_aModelTxt[0];
}