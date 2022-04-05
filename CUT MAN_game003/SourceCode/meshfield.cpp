//=======================================================================
//���b�V���t�B�[���h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "meshfield.h"
//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshField[MESHFIELD_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHFIELD g_MeshField[MAX_MESHFIELD];							//���b�V���t�B�[���h�\����
D3DXVECTOR3 g_rotMeshField;										//����

//=======================================================================
//����������
//=======================================================================
HRESULT InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		g_MeshField[nCntMeshField].fWidth = MESHFIELD_WIDTH;
		g_MeshField[nCntMeshField].fHeight = MESHFIELD_HEIGHT;
		g_MeshField[nCntMeshField].fDepth = MESHFIELD_DEPTH;
		g_MeshField[nCntMeshField].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshField[nCntMeshField].pos = D3DXVECTOR3(800.0f * (nCntMeshField + 1), 0.0f, 0.0f);
	}

	g_rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/road000.jpg",
		&g_pTextureMeshField[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MESHFIELD_X + 1) * (MESHFIELD_Z + 1)) * MAX_MESHFIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		int nNum = 0;
		for (int nCntZ = 0; nCntZ < MESHFIELD_Z + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < MESHFIELD_X + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(-g_MeshField[nCntMeshField].fWidth / 2.0f + (g_MeshField[nCntMeshField].fWidth / MESHFIELD_X) * nCntX,
											g_MeshField[nCntMeshField].pos.y,
											g_MeshField[nCntMeshField].fDepth / 2.0f - (g_MeshField[nCntMeshField].fDepth / MESHFIELD_Z) * nCntZ);

				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
				//pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (0.0f * (1.0f * nCntZ)));
			}
		}
		nNum = 0;

		/*pVtx[0].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z + g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[4].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[5].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z);
		pVtx[6].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) - g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[7].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1), g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);
		pVtx[8].pos = D3DXVECTOR3(g_MeshField[nCntMeshField].pos.x * (nCntMeshField + 1) + g_MeshField[nCntMeshField].fWidth / 2.0f, g_MeshField[nCntMeshField].pos.y + g_MeshField[nCntMeshField].fHeight / 2.0f, g_MeshField[nCntMeshField].pos.z - g_MeshField[nCntMeshField].fDepth / 2.0f);



		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);


		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);

		pVtx += 9;*/
		pVtx += (MESHFIELD_X + 1) * (MESHFIELD_Z + 1);
	}

	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshField->Unlock();


	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESHFIELD_Z - 1) * (MESHFIELD_X + 3) + (MESHFIELD_X + 1) * (MESHFIELD_Z + 1)) * MAX_MESHFIELD,
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIdxBuffMeshField, NULL);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		for (int nCnt1 = 0; nCnt1 < MESHFIELD_Z; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < MESHFIELD_X + 1; nCnt2++)
			{
				//�ԍ��f�[�^�̐ݒ�
				pIdx[(nCnt2 * 2) + 0 + (MESHFIELD_X + 2) * 2 * nCnt1] = (MESHFIELD_X + 1) + nCnt2 + (MESHFIELD_X + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (MESHFIELD_X + 2) * 2 * nCnt1] = 0				  + nCnt2 + (MESHFIELD_X + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < MESHFIELD_Z - 1; nCnt3++)
		{
			pIdx[((MESHFIELD_X + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = MESHFIELD_X		 + (MESHFIELD_X + 1) * nCnt3;
			pIdx[((MESHFIELD_X + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = MESHFIELD_X * 2 + 2 + (MESHFIELD_X + 1) * nCnt3;
		}
		pIdx += ((MESHFIELD_Z - 1) * (MESHFIELD_X + 3) + (MESHFIELD_X + 1) * (MESHFIELD_Z + 1));
	}


	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshField->Unlock();

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitMeshField(void)
{
	int nCntMeshField;
	for (nCntMeshField = 0; nCntMeshField < MESHFIELD_TYPE; nCntMeshField++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMeshField[nCntMeshField] != NULL)
		{
			g_pTextureMeshField[nCntMeshField]->Release();
			g_pTextureMeshField[nCntMeshField] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateMeshField(void)
{
	
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntMeshField = 0; nCntMeshField < MAX_MESHFIELD; nCntMeshField++)
	{
		D3DXMatrixIdentity(&g_MeshField[nCntMeshField].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

														//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshField.y, g_rotMeshField.x, g_rotMeshField.z);
		D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_MeshField[nCntMeshField].pos.x, g_MeshField[nCntMeshField].pos.y, g_MeshField[nCntMeshField].pos.z);
		D3DXMatrixMultiply(&g_MeshField[nCntMeshField].mtxWorld, &g_MeshField[nCntMeshField].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshField[nCntMeshField].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));
		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshField);

		pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

		pDevice->SetTexture(0, g_pTextureMeshField[0]);	//�e�N�X�`���̐ݒ�

														//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,
			0,
			((MESHFIELD_X + 1) * (MESHFIELD_Z + 1)),					//���_�̐�
			nCntMeshField * 14,											//�J�n���钸�_�̃C���f�b�N�X
			2 * MESHFIELD_X * MESHFIELD_Z + (MESHFIELD_Z * 4) - 4);		//�`�悷��v���~�e�B�u��
	}
}

//=======================================================================
//�擾����
//=======================================================================
MESHFIELD *GetMeshField(void)
{
	return &g_MeshField[0];
}

