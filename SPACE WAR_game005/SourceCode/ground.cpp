//=======================================================================
//���b�V���t�B�[���h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "ground.h"
//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureGround[GROUND_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGround = NULL;		//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffGround = NULL;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
GROUND g_Ground[MAX_GROUND];							//�v���C���[�\����

//=======================================================================
//����������
//=======================================================================
HRESULT InitGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		g_Ground[nCntGround].fWidth = 1.0f;
		g_Ground[nCntGround].fHeight = 1.0f;
		g_Ground[nCntGround].fDepth = 1.0f;
		g_Ground[nCntGround].nTileX = GROUND_X;	//��肠��
		g_Ground[nCntGround].nTileZ = GROUND_Z;
		g_Ground[nCntGround].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Ground[nCntGround].bUse = false;
	}


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/ground000.png",
		&g_pTextureGround[0]);

	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		//���_�o�b�t�@�̐���
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)) * MAX_GROUND,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&g_pVtxBuffGround,
			NULL);

		VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffGround->Lock(0, 0, (void**)&pVtx, 0);

		int nNum = 0;
		for (int nCntZ = 0; nCntZ < g_Ground[nCntGround].nTileZ + 1; nCntZ++)
		{
			for (int nCntX = 0; nCntX < g_Ground[nCntGround].nTileX + 1; nCntX++, nNum++)
			{
				pVtx[nNum].pos = D3DXVECTOR3(-g_Ground[nCntGround].fWidth / 2.0f + (g_Ground[nCntGround].fWidth / g_Ground[nCntGround].nTileX) * nCntX,
											g_Ground[nCntGround].pos.y,
											g_Ground[nCntGround].fDepth / 2.0f - (g_Ground[nCntGround].fDepth / g_Ground[nCntGround].nTileZ) * nCntZ);

				pVtx[nNum].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
				pVtx[nNum].col = D3DCOLOR_RGBA(255, 255, 255, 255);

				pVtx[nNum].tex = D3DXVECTOR2(0.0f + (1.0f * nCntX), 0.0f + (1.0f * nCntZ));
			}
		}
		nNum = 0;
		pVtx += (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffGround->Unlock();
	}



	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		//�C���f�b�N�X�o�b�t�@�̐���
		pDevice->CreateIndexBuffer(sizeof(WORD) * ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)) * MAX_GROUND,
			D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffGround, NULL);

		WORD *pIdx;		//�C���f�b�N�X���ւ̃|�C���^
						//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��f�[�^�ւ̃|�C���^���擾
		g_pIdxBuffGround->Lock(0, 0, (void**)&pIdx, 0);

		for (int nCnt1 = 0; nCnt1 < g_Ground[nCntGround].nTileZ; nCnt1++)
		{
			for (int nCnt2 = 0; nCnt2 < g_Ground[nCntGround].nTileX + 1; nCnt2++)
			{
				//�ԍ��f�[�^�̐ݒ�
				pIdx[(nCnt2 * 2) + 0 + (g_Ground[nCntGround].nTileX + 2) * 2 * nCnt1] = (g_Ground[nCntGround].nTileX + 1) + nCnt2 + (g_Ground[nCntGround].nTileX + 1) * nCnt1;
				pIdx[(nCnt2 * 2) + 1 + (g_Ground[nCntGround].nTileX + 2) * 2 * nCnt1] = 0				  + nCnt2 + (g_Ground[nCntGround].nTileX + 1) * nCnt1;
			}
		}
		for (int nCnt3 = 0; nCnt3 < g_Ground[nCntGround].nTileZ - 1; nCnt3++)
		{
			pIdx[((g_Ground[nCntGround].nTileX + 1) * 2 + 0) * (nCnt3 + 1) + (2 * nCnt3 )] = g_Ground[nCntGround].nTileX		 + (g_Ground[nCntGround].nTileX + 1) * nCnt3;
			pIdx[((g_Ground[nCntGround].nTileX + 1) * 2 + 1) * (nCnt3 + 1) + (1 * nCnt3 )] = g_Ground[nCntGround].nTileX * 2 + 2 + (g_Ground[nCntGround].nTileX + 1) * nCnt3;
		}
		pIdx += ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1));

		//�C���f�b�N�X�o�b�t�@���A�����b�N����
		g_pIdxBuffGround->Unlock();
	}

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitGround(void)
{
	int nCntGround;
	for (nCntGround = 0; nCntGround < GROUND_TYPE; nCntGround++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureGround[nCntGround] != NULL)
		{
			g_pTextureGround[nCntGround]->Release();
			g_pTextureGround[nCntGround] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGround != NULL)
	{
		g_pVtxBuffGround->Release();
		g_pVtxBuffGround = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuffGround != NULL)
	{
		g_pIdxBuffGround->Release();
		g_pIdxBuffGround = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateGround(void)
{
	
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawGround(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	pDevice = GetDevice();						//�f�o�C�X���擾����

	//���e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 180);

	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		if (g_Ground[nCntGround].bUse == true)
		{
			D3DXMatrixIdentity(&g_Ground[nCntGround].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

			//�X�P�[���𔽉f
			g_Ground[nCntGround].mtxWorld._11 = g_Ground[nCntGround].fWidth;
			g_Ground[nCntGround].mtxWorld._22 = g_Ground[nCntGround].fHeight;
			g_Ground[nCntGround].mtxWorld._33 = g_Ground[nCntGround].fDepth;

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Ground[nCntGround].rot.y, g_Ground[nCntGround].rot.x, g_Ground[nCntGround].rot.z);
			D3DXMatrixMultiply(&g_Ground[nCntGround].mtxWorld, &g_Ground[nCntGround].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Ground[nCntGround].pos.x, g_Ground[nCntGround].pos.y, g_Ground[nCntGround].pos.z);
			D3DXMatrixMultiply(&g_Ground[nCntGround].mtxWorld, &g_Ground[nCntGround].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Ground[nCntGround].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffGround, 0, sizeof(VERTEX_3D));
			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffGround);

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureGround[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				0,
				0,
				((g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)),					//���_�̐�
				nCntGround * ((g_Ground[nCntGround].nTileZ - 1) * (g_Ground[nCntGround].nTileX + 3) + (g_Ground[nCntGround].nTileX + 1) * (g_Ground[nCntGround].nTileZ + 1)),	//�J�n���钸�_�̃C���f�b�N�X
				2 * g_Ground[nCntGround].nTileX * g_Ground[nCntGround].nTileZ + (g_Ground[nCntGround].nTileZ * 4) - 4);		//�`�悷��v���~�e�B�u��
		}
	}
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetGround(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth, int nTileX, int nTileZ)
{
	for (int nCntGround = 0; nCntGround < MAX_GROUND; nCntGround++)
	{
		if (g_Ground[nCntGround].bUse == false)
		{
			g_Ground[nCntGround].pos = pos;
			g_Ground[nCntGround].rot = rot;
			g_Ground[nCntGround].fWidth = fWidth;
			g_Ground[nCntGround].fHeight = fHeight;
			g_Ground[nCntGround].fDepth = fDepth;
			g_Ground[nCntGround].nTileX = nTileX;
			g_Ground[nCntGround].nTileZ = nTileZ;
			g_Ground[nCntGround].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
GROUND *GetGround(void)
{
	return &g_Ground[0];
}

