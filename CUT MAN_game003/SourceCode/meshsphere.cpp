//=======================================================================
//���b�V���t�B�[���h(����)�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "meshsphere.h"
//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere[MESHSPHERE_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;				//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHSPHERE g_MeshSphere[MAX_MESHSPHERE];							//���b�V���t�B�[���h�\����
//=======================================================================
//����������
//=======================================================================
HRESULT InitMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		g_MeshSphere[nCntMeshSphere].fWidth = MESHSPHERE_WIDTH;
		g_MeshSphere[nCntMeshSphere].fHeight = MESHSPHERE_HEIGHT;
		g_MeshSphere[nCntMeshSphere].fDepth = MESHSPHERE_DEPTH;
		g_MeshSphere[nCntMeshSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshSphere[nCntMeshSphere].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_MeshSphere[nCntMeshSphere].pos = D3DXVECTOR3(0.0f , 0.0f, 0.0f);
	}



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/sky001.jpg",
		&g_pTextureMeshSphere[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)) * MAX_MESHSPHERE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		int nNum = 0;
		for (int nCntY = 0; nCntY < MESHSPHERE_Y + 1; nCntY++)
		{
			for (int nCntX = 0; nCntX < MESHSPHERE_X + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(cos((D3DX_PI * 2 / MESHSPHERE_X) * nCntX) * (sin(((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) +((D3DX_PI * 2 / MESHSPHERE_X) * MESHSPHERE_Y)) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f)) ,
											sin((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f),
											(sin((D3DX_PI * 2 / MESHSPHERE_X) * nCntX) * (sin(((D3DX_PI * 2 / MESHSPHERE_X) * nCntY) + ((D3DX_PI * 2 / MESHSPHERE_X) * MESHSPHERE_Y)) * (g_MeshSphere[nCntMeshSphere].fWidth / 2.0f))));


				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f / MESHSPHERE_X * nCntX), 0.0f + (1.0f / MESHSPHERE_Y * nCntY));
			}
		}
		nNum = 0;

		
		pVtx += (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1);
	}

	

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshSphere->Unlock();


	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MESHSPHERE_Y - 1) * (MESHSPHERE_X + 3) + (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)) * MAX_MESHSPHERE,
								D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED, &g_pIdxBuffMeshSphere, NULL);

	WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
	//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);


	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		for (int nCnt1 = 0; nCnt1 < MESHSPHERE_Y; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < MESHSPHERE_X + 1; nCnt2++)
			{
				//�ԍ��f�[�^�̐ݒ�
				pIdx[(nCnt2 * 2) + 0 + (MESHSPHERE_X + 2) * 2 * nCnt1] = (MESHSPHERE_X + 1) + nCnt2 + (MESHSPHERE_X + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (MESHSPHERE_X + 2) * 2 * nCnt1] = 0				  + nCnt2 + (MESHSPHERE_X + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < MESHSPHERE_Y - 1; nCnt3++)
		{
			pIdx[((MESHSPHERE_X + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = MESHSPHERE_X		 + (MESHSPHERE_X + 1) * nCnt3;
			pIdx[((MESHSPHERE_X + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = MESHSPHERE_X * 2 + 2 + (MESHSPHERE_X + 1) * nCnt3;
		}
		pIdx += ((MESHSPHERE_Y - 1) * (MESHSPHERE_X + 3) + (MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1));
	}


	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshSphere->Unlock();

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitMeshSphere(void)
{
	int nCntMeshSphere;
	for (nCntMeshSphere = 0; nCntMeshSphere < MESHSPHERE_TYPE; nCntMeshSphere++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureMeshSphere[nCntMeshSphere] != NULL)
		{
			g_pTextureMeshSphere[nCntMeshSphere]->Release();
			g_pTextureMeshSphere[nCntMeshSphere] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateMeshSphere(void)
{
	for (int nCntMeshSphere = 0; nCntMeshSphere < MESHSPHERE_TYPE; nCntMeshSphere++)
	{
		g_MeshSphere[nCntMeshSphere].rot.y += 0.00005;
		if (g_MeshSphere[nCntMeshSphere].rot.y >= D3DX_PI)
		{
			g_MeshSphere[nCntMeshSphere].rot.y = -D3DX_PI;
		}
	}

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntMeshSphere = 0; nCntMeshSphere < MAX_MESHSPHERE; nCntMeshSphere++)
	{
		D3DXMatrixIdentity(&g_MeshSphere[nCntMeshSphere].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

														//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSphere[nCntMeshSphere].rot.y, g_MeshSphere[nCntMeshSphere].rot.x, g_MeshSphere[nCntMeshSphere].rot.z);
		D3DXMatrixMultiply(&g_MeshSphere[nCntMeshSphere].mtxWorld, &g_MeshSphere[nCntMeshSphere].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_MeshSphere[nCntMeshSphere].pos.x, g_MeshSphere[nCntMeshSphere].pos.y, g_MeshSphere[nCntMeshSphere].pos.z);
		D3DXMatrixMultiply(&g_MeshSphere[nCntMeshSphere].mtxWorld, &g_MeshSphere[nCntMeshSphere].mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshSphere[nCntMeshSphere].mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));
		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshSphere);

		pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

		pDevice->SetTexture(0, g_pTextureMeshSphere[0]);	//�e�N�X�`���̐ݒ�

														//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
			0,
			0,
			((MESHSPHERE_X + 1) * (MESHSPHERE_Y + 1)),					//���_�̐�
			nCntMeshSphere * 14,											//�J�n���钸�_�̃C���f�b�N�X
			2 * MESHSPHERE_X * MESHSPHERE_Y + (MESHSPHERE_Y * 4) - 4);		//�`�悷��v���~�e�B�u��
	}
}

//=======================================================================
//�擾����
//=======================================================================
MESHSPHERE *GetMeshSphere(void)
{
	return &g_MeshSphere[0];
}

