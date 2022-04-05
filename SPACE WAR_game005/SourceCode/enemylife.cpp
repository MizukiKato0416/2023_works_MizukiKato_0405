//=======================================================================
//�Q�[�W�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "enemylife.h"
#include "enemy.h"
#include "shadow.h"
#include "drone.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureEnemyLife[ENEMYLIFE_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyLife = NULL;			//���_�o�b�t�@�ւ̃|�C���^
EnemyLife g_aEnemyLife[MAX_ENEMYLIFE];									//�Q�[�W�\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitEnemyLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		g_aEnemyLife[nCntEnemyLife].fWidth = ENEMYLIFE_WIDTH;
		g_aEnemyLife[nCntEnemyLife].fHeight = ENEMYLIFE_HEIGHT;
		g_aEnemyLife[nCntEnemyLife].fDepth = ENEMYLIFE_DEPTH;
		g_aEnemyLife[nCntEnemyLife].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyLife[nCntEnemyLife].bUse = false;
		g_aEnemyLife[nCntEnemyLife].nShadow = 0;

	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/EnemyLife.png",
		&g_pTextureEnemyLife[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_ENEMYLIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemyLife,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemyLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, -g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyLife[nCntEnemyLife].fWidth / 2.0f, -g_aEnemyLife[nCntEnemyLife].fHeight / 2.0f, g_aEnemyLife[nCntEnemyLife].fDepth / 2.0f);

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
	g_pVtxBuffEnemyLife->Unlock();
	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitEnemyLife(void)
{
	int nCntEnemyLife;
	for (nCntEnemyLife = 0; nCntEnemyLife < ENEMYLIFE_TYPE; nCntEnemyLife++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemyLife[nCntEnemyLife] != NULL)
		{
			g_pTextureEnemyLife[nCntEnemyLife]->Release();
			g_pTextureEnemyLife[nCntEnemyLife] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemyLife != NULL)
	{
		g_pVtxBuffEnemyLife->Release();
		g_pVtxBuffEnemyLife = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEnemyLife(void)
{
	DRONE *pDrone = GetDrone();
	ENEMY *pEnemy = GetEnemy();
	int nEnemy = GetUseEnemy();

	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == true)
		{
			
		}
		
	}

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEnemyLife(void)
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


	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == true)
		{
			//���e�X�g
			//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			//pDevice->SetRenderState(D3DRS_ALPHAREF, 190);

			D3DXMatrixIdentity(&g_aEnemyLife[nCntEnemyLife].mtxWorld);		//���[���h�}�g���b�N�X�̏�����


			pDevice->GetTransform(D3DTS_VIEW, &g_aEnemyLife[nCntEnemyLife].mtxView);	//�r���[�}�g���b�N�X���擾


			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�	
			g_aEnemyLife[nCntEnemyLife].mtxWorld._11 = g_aEnemyLife[nCntEnemyLife].mtxView._11 * g_aEnemyLife[nCntEnemyLife].scale.x;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._12 = g_aEnemyLife[nCntEnemyLife].mtxView._21 * g_aEnemyLife[nCntEnemyLife].scale.x;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._13 = g_aEnemyLife[nCntEnemyLife].mtxView._31 * g_aEnemyLife[nCntEnemyLife].scale.x;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._21 = g_aEnemyLife[nCntEnemyLife].mtxView._12 * g_aEnemyLife[nCntEnemyLife].scale.y;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._22 = g_aEnemyLife[nCntEnemyLife].mtxView._22 * g_aEnemyLife[nCntEnemyLife].scale.y;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._23 = g_aEnemyLife[nCntEnemyLife].mtxView._32 * g_aEnemyLife[nCntEnemyLife].scale.y;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._31 = g_aEnemyLife[nCntEnemyLife].mtxView._13;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._32 = g_aEnemyLife[nCntEnemyLife].mtxView._23;
			g_aEnemyLife[nCntEnemyLife].mtxWorld._33 = g_aEnemyLife[nCntEnemyLife].mtxView._33;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._41 = 0.0f;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._42 = 0.0f;
			//g_aEnemyLife[nCntEnemyLife].mtxWorld._43 = 0.0f;

			//�X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, g_aEnemyLife[nCntEnemyLife].scale.x, g_aEnemyLife[nCntEnemyLife].scale.y, g_aEnemyLife[nCntEnemyLife].scale.z);		//�X�P�[���s����쐬
			//D3DXMatrixMultiply(&g_aEnemyLife[nCntEnemyLife].mtxWorld, &g_aEnemyLife[nCntEnemyLife].mtxWorld, &mtxScale);	//�X�P�[���𔽉f

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyLife[nCntEnemyLife].pos.x, g_aEnemyLife[nCntEnemyLife].pos.y, g_aEnemyLife[nCntEnemyLife].pos.z);		//�ړ��s����쐬
			D3DXMatrixMultiply(&g_aEnemyLife[nCntEnemyLife].mtxWorld, &g_aEnemyLife[nCntEnemyLife].mtxWorld, &mtxTrans);	//�ړ��𔽉f

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyLife[nCntEnemyLife].mtxWorld);


			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyLife, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureEnemyLife[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEnemyLife * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��

			//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
		}
	}
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}


//===========================================
//�ݒ菈��
//===========================================
int SetEnemyLife(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	int nIdx = -1;
	for (int nCntEnemyLife = 0; nCntEnemyLife < MAX_ENEMYLIFE; nCntEnemyLife++)
	{
		if (g_aEnemyLife[nCntEnemyLife].bUse == false)
		{
			g_aEnemyLife[nCntEnemyLife].pos = pos;
			g_aEnemyLife[nCntEnemyLife].scale.x = fWidth;
			g_aEnemyLife[nCntEnemyLife].scale.y = fHeight;

			g_aEnemyLife[nCntEnemyLife].bUse = true;
			nIdx = nCntEnemyLife;
			break;
		}
	}
	return nIdx;
}

//===========================================
//�ʒu�X�V����
//===========================================
void SetPositionEnemyLife(int nIdx, D3DXVECTOR3 pos, bool bUse, int nMaxlife, int nLife, float fWidth)
{
	if (g_aEnemyLife[nIdx].bUse == true)
	{
		g_aEnemyLife[nIdx].pos.x = pos.x;
		g_aEnemyLife[nIdx].pos.y = pos.y;
		g_aEnemyLife[nIdx].pos.z = pos.z;

		g_aEnemyLife[nIdx].scale.x = fWidth / nMaxlife * nLife;

		if (bUse == false)
		{
			g_aEnemyLife[nIdx].bUse = false;
		}
	}
}

EnemyLife *GetEnemyLife(void)
{
	return &g_aEnemyLife[0];
}