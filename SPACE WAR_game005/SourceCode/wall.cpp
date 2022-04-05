//=======================================================================
//�ǂɊւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "wall.h"
#include "shadow.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureWall[WALL_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//���_�o�b�t�@�ւ̃|�C���^
WALL g_aWall[MAX_WALL];									//�Ǎ\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].fWidth = WALL_WIDTH;
		g_aWall[nCntWall].fHeight = WALL_HEIGHT;
		g_aWall[nCntWall].fDepth = WALL_DEPTH;
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
		g_aWall[nCntWall].nNum = 0;

	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/wall_building000.png",
		&g_pTextureWall[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		pVtx[0].pos = D3DXVECTOR3(-0.5f, 0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(0.5f, 0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-0.5f, -0.5f, g_aWall[nCntWall].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(0.5f, -0.5f, g_aWall[nCntWall].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(3.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(3.0f, 1.0f);

		pVtx += 4;
	}
	
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitWall(void)
{
	int nCntWall;
	for (nCntWall = 0; nCntWall < WALL_TYPE; nCntWall++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureWall[nCntWall] != NULL)
		{
			g_pTextureWall[nCntWall]->Release();
			g_pTextureWall[nCntWall] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateWall(void)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//SetPositionShadow(g_aWall[nCntWall].nNum, g_aWall[nCntWall].pos);
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;				//�v�Z�p�}�g���b�N�X
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

			//�X�P�[���𔽉f
			g_aWall[nCntWall].mtxWorld._11 = g_aWall[nCntWall].scale.x;
			g_aWall[nCntWall].mtxWorld._22 = g_aWall[nCntWall].scale.y;

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureWall[0]);	//�e�N�X�`���̐ݒ�

														//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntWall * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}		
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].scale = scale;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].pos = pos;

			g_aWall[nCntWall].bUse = true;





			break;
		}
	}
}