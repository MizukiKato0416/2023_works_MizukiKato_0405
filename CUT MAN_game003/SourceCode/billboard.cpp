//=======================================================================
//�r���{�[�h�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "billboard.h"
#include "shadow.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureBillboard[BILLBOARD_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;			//���_�o�b�t�@�ւ̃|�C���^
BILLBOARD g_aBillboard[MAX_BILLBOARD];									//�Ǎ\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		g_aBillboard[nCntBillboard].fWidth = BILLBOARD_WIDTH;
		g_aBillboard[nCntBillboard].fHeight = BILLBOARD_HEIGHT;
		g_aBillboard[nCntBillboard].fDepth = BILLBOARD_DEPTH;
		g_aBillboard[nCntBillboard].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aBillboard[nCntBillboard].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBillboard[nCntBillboard].bUse = false;
		g_aBillboard[nCntBillboard].nShadow = 0;

	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tree001.png",
		&g_pTextureBillboard[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_BILLBOARD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth / 2.0f, g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth / 2.0f, g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aBillboard[nCntBillboard].fWidth / 2.0f, -g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBillboard[nCntBillboard].fWidth / 2.0f, -g_aBillboard[nCntBillboard].fHeight / 2.0f, g_aBillboard[nCntBillboard].fDepth / 2.0f);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBillboard->Unlock();

	/*for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		SetShadow(D3DXVECTOR3(g_aBillboard[nCntBillboard].pos.x,0.0f, g_aBillboard[nCntBillboard].pos.z), 50.0f, 50.0f);

	}

*/


	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitBillboard(void)
{
	int nCntBillboard;
	for (nCntBillboard = 0; nCntBillboard < BILLBOARD_TYPE; nCntBillboard++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBillboard[nCntBillboard] != NULL)
		{
			g_pTextureBillboard[nCntBillboard]->Release();
			g_pTextureBillboard[nCntBillboard] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateBillboard(void)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			
		}
	}

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxTrans;				//�ʒu�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale;				//�X�P�[���v�Z�p�}�g���b�N�X

	//Z�e�X�g
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);


	//���C�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);


	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == true)
		{
			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aBillboard[nCntBillboard].mtxWorld);		//���[���h�}�g���b�N�X�̏�����


			pDevice->GetTransform(D3DTS_VIEW, &g_aBillboard[nCntBillboard].mtxView);	//�r���[�}�g���b�N�X���擾


			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�	
			g_aBillboard[nCntBillboard].mtxWorld._11 = g_aBillboard[nCntBillboard].mtxView._11 * g_aBillboard[nCntBillboard].scale.x;
			g_aBillboard[nCntBillboard].mtxWorld._12 = g_aBillboard[nCntBillboard].mtxView._21 * g_aBillboard[nCntBillboard].scale.x;
			g_aBillboard[nCntBillboard].mtxWorld._13 = g_aBillboard[nCntBillboard].mtxView._31 * g_aBillboard[nCntBillboard].scale.x;
			//g_aBillboard[nCntBillboard].mtxWorld._21 = g_aBillboard[nCntBillboard].mtxView._12 * g_aBillboard[nCntBillboard].scale.y;
			g_aBillboard[nCntBillboard].mtxWorld._22 = g_aBillboard[nCntBillboard].mtxView._22 * g_aBillboard[nCntBillboard].scale.y;
			//g_aBillboard[nCntBillboard].mtxWorld._23 = g_aBillboard[nCntBillboard].mtxView._32 * g_aBillboard[nCntBillboard].scale.y;
			g_aBillboard[nCntBillboard].mtxWorld._31 = g_aBillboard[nCntBillboard].mtxView._13;
			g_aBillboard[nCntBillboard].mtxWorld._32 = g_aBillboard[nCntBillboard].mtxView._23;
			g_aBillboard[nCntBillboard].mtxWorld._33 = g_aBillboard[nCntBillboard].mtxView._33;
			//g_aBillboard[nCntBillboard].mtxWorld._41 = 0.0f;
			//g_aBillboard[nCntBillboard].mtxWorld._42 = 0.0f;
			//g_aBillboard[nCntBillboard].mtxWorld._43 = 0.0f;

			//�X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, g_aBillboard[nCntBillboard].scale.x, g_aBillboard[nCntBillboard].scale.y, g_aBillboard[nCntBillboard].scale.z);		//�X�P�[���s����쐬
			//D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxScale);	//�X�P�[���𔽉f

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBillboard[nCntBillboard].pos.x, g_aBillboard[nCntBillboard].pos.y, g_aBillboard[nCntBillboard].pos.z);		//�ړ��s����쐬
			D3DXMatrixMultiply(&g_aBillboard[nCntBillboard].mtxWorld, &g_aBillboard[nCntBillboard].mtxWorld, &mtxTrans);	//�ړ��𔽉f

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBillboard[nCntBillboard].mtxWorld);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureBillboard[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntBillboard * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��

			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void SetBillboard(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	for (int nCntBillboard = 0; nCntBillboard < MAX_BILLBOARD; nCntBillboard++)
	{
		if (g_aBillboard[nCntBillboard].bUse == false)
		{
			g_aBillboard[nCntBillboard].pos = pos;
			g_aBillboard[nCntBillboard].scale.x = fWidth;
			g_aBillboard[nCntBillboard].scale.y = fHeight;

			g_aBillboard[nCntBillboard].bUse = true;

			break;
		}
	}
}

BILLBOARD *GetBillboard(void)
{
	return &g_aBillboard[0];
}