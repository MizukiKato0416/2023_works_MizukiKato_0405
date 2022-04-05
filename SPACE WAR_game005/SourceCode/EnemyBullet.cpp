//=======================================================================
//�G�̒e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "EnemyBullet.h"
#include "shadow.h"
#include "camera.h"
#include "player.h"
#include "effect.h"
#include "modeltxt.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTextureEnemyBullet[ENEMYBULLET_TYPE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
ENEMYBULLET g_aEnemyBullet[MAX_ENEMYBULLET];								//�Ǎ\����


//=======================================================================
//����������
//=======================================================================
HRESULT InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//������
	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		g_aEnemyBullet[nCntEnemyBullet].fWidth = ENEMYBULLET_WIDTH;
		g_aEnemyBullet[nCntEnemyBullet].fHeight = ENEMYBULLET_HEIGHT;
		g_aEnemyBullet[nCntEnemyBullet].fDepth = ENEMYBULLET_DEPTH;
		g_aEnemyBullet[nCntEnemyBullet].fFarPlayer = 0.0f;
		g_aEnemyBullet[nCntEnemyBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].scale = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].bUse = false;
	}
	

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureEnemyBullet[0]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_ENEMYBULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemyBullet,
		NULL);

	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		pVtx[0].pos = D3DXVECTOR3(-g_aEnemyBullet[nCntEnemyBullet].fWidth / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fHeight / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fDepth / 2.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].fWidth / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fHeight / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fDepth / 2.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEnemyBullet[nCntEnemyBullet].fWidth / 2.0f, -g_aEnemyBullet[nCntEnemyBullet].fHeight / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fDepth / 2.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].fWidth / 2.0f, -g_aEnemyBullet[nCntEnemyBullet].fHeight / 2.0f, g_aEnemyBullet[nCntEnemyBullet].fDepth / 2.0f);

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
	g_pVtxBuffEnemyBullet->Unlock();

	return S_OK;
}

//=======================================================================
//�I������
//=======================================================================
void UninitEnemyBullet(void)
{
	int nCntEnemyBullet;
	for (nCntEnemyBullet = 0; nCntEnemyBullet < ENEMYBULLET_TYPE; nCntEnemyBullet++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureEnemyBullet[nCntEnemyBullet] != NULL)
		{
			g_pTextureEnemyBullet[nCntEnemyBullet]->Release();
			g_pTextureEnemyBullet[nCntEnemyBullet] = NULL;
		}
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnemyBullet != NULL)
	{
		g_pVtxBuffEnemyBullet->Release();
		g_pVtxBuffEnemyBullet = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateEnemyBullet(void)
{
	PLAYER *pPlayer = GetPlayer();
	Camera * pCamera;
	pCamera = GetCamera();

	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if (g_aEnemyBullet[nCntEnemyBullet].bUse == true)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos += g_aEnemyBullet[nCntEnemyBullet].move;

			if (g_aEnemyBullet[nCntEnemyBullet].pos.x >= 5000.0f || g_aEnemyBullet[nCntEnemyBullet].pos.x <= -5000.0f ||
				g_aEnemyBullet[nCntEnemyBullet].pos.z >= 5000.0f || g_aEnemyBullet[nCntEnemyBullet].pos.z <= -5000.0f)
			{
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;
			}

			if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE001)
			{
				SetEffect(D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(255, 0, 255, 255), 15, EFFEFCT_MOVETYPE_BULLET);
			}
			else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE002)
			{
				SetEffect(D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 15.0f, 15.0f, D3DXCOLOR(255, 0, 255, 255), 7, EFFEFCT_MOVETYPE_BULLET);
			}
			else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE003)
			{
				SetEffect(D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, 30.0f, D3DXCOLOR(255, 0, 255, 255), 30, EFFEFCT_MOVETYPE_BULLET);
			}
			else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_BOSS_SMALL)
			{
				SetEffect(D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, D3DXCOLOR(255, 0, 255, 255), 15, EFFEFCT_MOVETYPE_BULLET);
			}
			else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_BOSS_BIG)
			{
				SetEffect(D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 100.0f, D3DXCOLOR(255, 0, 255, 255), 10, EFFEFCT_MOVETYPE_BULLET);
			}
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	D3DXMATRIX mtxTrans;				//�ʒu�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxScale;				//�X�P�[���v�Z�p�}�g���b�N�X

	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if (g_aEnemyBullet[nCntEnemyBullet].bUse == true)
		{
			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���e�X�g
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 190);


			D3DXMatrixIdentity(&g_aEnemyBullet[nCntEnemyBullet].mtxWorld);		//���[���h�}�g���b�N�X�̏�����


			pDevice->GetTransform(D3DTS_VIEW, &g_aEnemyBullet[nCntEnemyBullet].mtxView);	//�r���[�}�g���b�N�X���擾


			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			//�t�s������߂�	
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._11 = g_aEnemyBullet[nCntEnemyBullet].mtxView._11 * g_aEnemyBullet[nCntEnemyBullet].scale.x;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._12 = g_aEnemyBullet[nCntEnemyBullet].mtxView._21 * g_aEnemyBullet[nCntEnemyBullet].scale.x;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._13 = g_aEnemyBullet[nCntEnemyBullet].mtxView._31 * g_aEnemyBullet[nCntEnemyBullet].scale.x;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._21 = g_aEnemyBullet[nCntEnemyBullet].mtxView._12 * g_aEnemyBullet[nCntEnemyBullet].scale.y;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._22 = g_aEnemyBullet[nCntEnemyBullet].mtxView._22 * g_aEnemyBullet[nCntEnemyBullet].scale.y;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._23 = g_aEnemyBullet[nCntEnemyBullet].mtxView._32 * g_aEnemyBullet[nCntEnemyBullet].scale.y;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._31 = g_aEnemyBullet[nCntEnemyBullet].mtxView._13;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._32 = g_aEnemyBullet[nCntEnemyBullet].mtxView._23;
			g_aEnemyBullet[nCntEnemyBullet].mtxWorld._33 = g_aEnemyBullet[nCntEnemyBullet].mtxView._33;
			//g_aEnemyBullet[nCntEnemyBullet].mtxWorld._41 = 0.0f;
			//g_aEnemyBullet[nCntEnemyBullet].mtxWorld._42 = 0.0f;
			//g_aEnemyBullet[nCntEnemyBullet].mtxWorld._43 = 0.0f;

			//�X�P�[���𔽉f
			//D3DXMatrixScaling(&mtxScale, g_aEnemyBullet[nCntEnemyBullet].scale.x, g_aEnemyBullet[nCntEnemyBullet].scale.y, g_aEnemyBullet[nCntEnemyBullet].scale.z);		//�X�P�[���s����쐬
			//D3DXMatrixMultiply(&g_aEnemyBullet[nCntEnemyBullet].mtxWorld, &g_aEnemyBullet[nCntEnemyBullet].mtxWorld, &mtxScale);	//�X�P�[���𔽉f

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemyBullet[nCntEnemyBullet].pos.x, g_aEnemyBullet[nCntEnemyBullet].pos.y, g_aEnemyBullet[nCntEnemyBullet].pos.z);		//�ړ��s����쐬
			D3DXMatrixMultiply(&g_aEnemyBullet[nCntEnemyBullet].mtxWorld, &g_aEnemyBullet[nCntEnemyBullet].mtxWorld, &mtxTrans);	//�ړ��𔽉f

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEnemyBullet[nCntEnemyBullet].mtxWorld);

			//Z�e�X�g
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEnemyBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);			//���_�t�H�[�}�b�g�̐ݒ�

			pDevice->SetTexture(0, g_pTextureEnemyBullet[0]);	//�e�N�X�`���̐ݒ�

															//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEnemyBullet * 4,					//�J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��

			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);

			//a�u�����f�B���O��ʏ�ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//=======================================================================
//�G�̒e�Ƃ̓����蔻��
//=======================================================================
int CollisionEnemyBullet(D3DXVECTOR3 *pPos, float fWidth)
{
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	ENEMYBULLET *pEnemyBullet = GetEnemyBullet();
	int nDamageType = 0;			//�������Ă��邩�ǂ����A���̎�ނ̒e�ɓ������Ă��邩

	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++, pEnemyBullet++)
	{
		if (pEnemyBullet->bUse == true)
		{
			g_aEnemyBullet[nCntEnemyBullet].fFarPlayer = sqrt((pPlayer->pos.x - g_aEnemyBullet[nCntEnemyBullet].pos.x) * (pPlayer->pos.x - g_aEnemyBullet[nCntEnemyBullet].pos.x) +
															(pPlayer->pos.z - g_aEnemyBullet[nCntEnemyBullet].pos.z) * (pPlayer->pos.z - g_aEnemyBullet[nCntEnemyBullet].pos.z));
			
			if (pEnemyBullet->fFarPlayer <= pEnemyBullet->scale.x - 8.0f)
			{
				if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE001)
				{
					nDamageType = 1;
					pEnemyBullet->bUse = false;
				}
				else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE002)
				{
					nDamageType = 2;
					pEnemyBullet->bUse = false;
				}
				else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_DRONE003)
				{
					nDamageType = 3;
					pEnemyBullet->bUse = false;
				}
				else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_BOSS_SMALL)
				{
					nDamageType = 4;
					pEnemyBullet->bUse = false;
				}
				else if (g_aEnemyBullet[nCntEnemyBullet].nType == ENEMYBULLET_MOVETYPE_BOSS_BIG)
				{
					nDamageType = 5;
					pEnemyBullet->bUse = false;
				}
			}
		}

		//���f���Ƃ̓����蔻��
		if (CollisionModelTxtBool(&g_aEnemyBullet[nCntEnemyBullet].pos) == true)
		{
			g_aEnemyBullet[nCntEnemyBullet].bUse = false;
		}
	}

	return nDamageType;
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight ,D3DXCOLOR col, ENEMYBULLET_MOVETYPE nType)
{
	for (int nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMYBULLET; nCntEnemyBullet++)
	{
		if (g_aEnemyBullet[nCntEnemyBullet].bUse == false)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos = pos;
			g_aEnemyBullet[nCntEnemyBullet].move = move;
			g_aEnemyBullet[nCntEnemyBullet].scale.x = fWidth;
			g_aEnemyBullet[nCntEnemyBullet].scale.y = fHeight;
			g_aEnemyBullet[nCntEnemyBullet].col = col;
			g_aEnemyBullet[nCntEnemyBullet].bUse = true;
			g_aEnemyBullet[nCntEnemyBullet].nType = nType;

			VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].col = g_aEnemyBullet[nCntEnemyBullet].col;
			pVtx[1].col = g_aEnemyBullet[nCntEnemyBullet].col;
			pVtx[2].col = g_aEnemyBullet[nCntEnemyBullet].col;
			pVtx[3].col = g_aEnemyBullet[nCntEnemyBullet].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemyBullet->Unlock();
			break;
		}
	}
}

ENEMYBULLET *GetEnemyBullet(void)
{
	return &g_aEnemyBullet[0];
}