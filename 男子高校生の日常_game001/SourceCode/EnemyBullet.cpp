//=======================================================================
//�G�̒e�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "EnemyBullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"



//========================================================
//�O���[�o���ϐ�
//========================================================

LPDIRECT3DTEXTURE9 g_pTextureEnemyBullet[MAX_ENEMY_BULLET_TYPE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemyBullet = NULL;		//���_�o�b�t�@�ւ̃|�C���^
EnemyBullet g_aEnemyBullet[MAX_ENEMY_BULLET];
int g_nCntTurn;		//�e�̒��˕Ԃ�̃J�E���g

//========================================================
//����������
//========================================================
void InitEnemyBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntEnemyBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�̏�����
	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET; nCntEnemyBullet++)
	{
		g_aEnemyBullet[nCntEnemyBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight = 0.0f;
		g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth = 0.0f;
		g_aEnemyBullet[nCntEnemyBullet].nType = 0;
		g_aEnemyBullet[nCntEnemyBullet].bUse = false;
	}
	g_nCntTurn = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//boarn.png",
		&g_pTextureEnemyBullet[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet1.png",
		&g_pTextureEnemyBullet[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet2.png",
		&g_pTextureEnemyBullet[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet3.png",
		&g_pTextureEnemyBullet[3]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet4.png",
		&g_pTextureEnemyBullet[4]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE/Enemy_Bullet5.png",
		&g_pTextureEnemyBullet[5]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet6.png",
		&g_pTextureEnemyBullet[6]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet7.png",
		&g_pTextureEnemyBullet[7]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet8.png",
		&g_pTextureEnemyBullet[8]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet9.png",
		&g_pTextureEnemyBullet[9]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet10.png",
		&g_pTextureEnemyBullet[10]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet11.png",
		&g_pTextureEnemyBullet[11]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet12.png",
		&g_pTextureEnemyBullet[12]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//Enemy_Bullet13.png",
		&g_pTextureEnemyBullet[13]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemyBullet,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET; nCntEnemyBullet++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

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
}

//========================================================
//�e�̏I������
//========================================================
void UninitEnemyBullet(void)
{
	int nCntEnemyBullet;
	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET_TYPE; nCntEnemyBullet++)
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

//========================================================
////�e�̍X�V����
//========================================================
void UpdateEnemyBullet(void)
{
	//-------------------------------------------------
	//�e�̈ړ��ʁA�g�p���g�p�̐ݒ�
	//-------------------------------------------------
	int nCntEnemyBullet;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET; nCntEnemyBullet++)
	{

		if (g_aEnemyBullet[nCntEnemyBullet].bUse == true)
		{

			g_aEnemyBullet[nCntEnemyBullet].pos -= g_aEnemyBullet[nCntEnemyBullet].move;

			if (GetMode() == MODE_STAGE3)
			{
				if (g_nCntTurn <= 1)
				{
					if (g_aEnemyBullet[nCntEnemyBullet].pos.y - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight / 2 <= 0.0f || g_aEnemyBullet[nCntEnemyBullet].pos.y + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight / 2 >= SCREEN_HEIGHT)
					{
						g_aEnemyBullet[nCntEnemyBullet].move.y *= -1;
						g_nCntTurn++;
					}
				}
				else if(g_nCntTurn > 1)
				{
					g_nCntTurn = 0;
				}
				
			}

			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);

			if (g_aEnemyBullet[nCntEnemyBullet].pos.x <=0.0f- g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth)
			{
				g_aEnemyBullet[nCntEnemyBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemyBullet->Unlock();
}

//========================================================
////�`�揈��
//========================================================
void DrawEnemyBullet(void)
{
	int nCntEnemyBullet;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemyBullet, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET; nCntEnemyBullet++)
	{
		if (g_aEnemyBullet[nCntEnemyBullet].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureEnemyBullet[g_aEnemyBullet[nCntEnemyBullet].nType]);	//�e�N�X�`���̐ݒ�
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntEnemyBullet * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//========================================================
//�e�̐ݒ菈��
//========================================================
void SetEnemyBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,int type, float EnemyBulletHeight, float EnemyBulletWidth)
{
	int nCntEnemyBullet;
	for (nCntEnemyBullet = 0; nCntEnemyBullet < MAX_ENEMY_BULLET; nCntEnemyBullet++)
	{
		if (g_aEnemyBullet[nCntEnemyBullet].bUse == false)
		{
			g_aEnemyBullet[nCntEnemyBullet].pos = pos;
			g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth = EnemyBulletWidth;
			g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight = EnemyBulletHeight;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffEnemyBullet->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntEnemyBullet * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x - g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemyBullet[nCntEnemyBullet].pos.x + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletWidth, g_aEnemyBullet[nCntEnemyBullet].pos.y + g_aEnemyBullet[nCntEnemyBullet].EnemyBulletHeight, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEnemyBullet->Unlock();
			g_aEnemyBullet[nCntEnemyBullet].nType = type;
			g_aEnemyBullet[nCntEnemyBullet].move = move;
			g_aEnemyBullet[nCntEnemyBullet].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
EnemyBullet *GetEnemyBullet(void)
{
	return &g_aEnemyBullet[0];
}