//=======================================================================
//�{�X�Ɋւ��鏈��
//Aouthor:�@�����@����
//=======================================================================

#include "main.h"
#include "boss.h"
#include "EnemyBullet.h"
#include "sound.h"
#include "fade.h"


//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================

LPDIRECT3DTEXTURE9 g_apTextureBoss[4] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Boss g_aBoss[MAX_BOSS];							//�G
int  g_EnemyBulletCnt;							//�e�̊Ԋu
int  g_EnemyBulletTypeCnt;							//�e�̊Ԋu


//=======================================================================
//����������
//=======================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�ŃA�C�X�̃|�C���^
	int nCntBoss;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏�����
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].nCounterAnim = 0;
		g_aBoss[nCntBoss].nPatternAnim = 0;
		g_aBoss[nCntBoss].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//dog.png",
		&g_apTextureBoss[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//face_angry_woman5.png",
		&g_apTextureBoss[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//teachar.png",
		&g_apTextureBoss[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//enemy003.png",
		&g_apTextureBoss[3]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
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
	g_pVtxBuffBoss->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitBoss(void)
{
	int nCntBoss;
	for (nCntBoss = 0; nCntBoss < 4; nCntBoss++)
	{
		//�e�N�X�`���̔j��
		if (g_apTextureBoss[nCntBoss] != NULL)
		{
			g_apTextureBoss[nCntBoss]->Release();
			g_apTextureBoss[nCntBoss] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateBoss(void)
{
	//========================================================
	//�{�X�̓���
	//========================================================
	int nCntBoss;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{

		if (g_aBoss[nCntBoss].bUse == true)
		{
			g_aBoss[nCntBoss].nCounterAnim++;
			if (g_aBoss[nCntBoss].nCounterAnim == 200)
			{
				g_aBoss[nCntBoss].nCounterAnim = 0;		//�J�E���^�[�������n�ɖ߂�
				g_aBoss[nCntBoss].nPatternAnim++;		//�p�^�[��No���X�V
				if (g_aBoss[nCntBoss].nPatternAnim > 1)
				{
					g_aBoss[nCntBoss].nPatternAnim = 0;
				}
				pVtx[0].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f + 0.5f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBoss[nCntBoss].nPatternAnim * 0.5f + 0.5f, 1.0f);
			}
			
			if (g_aBoss[nCntBoss].pos.x != SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
			{
				g_aBoss[nCntBoss].pos -= g_aBoss[nCntBoss].move;

			}

			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);

			if (g_aBoss[nCntBoss].pos.x == SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f)
			{
				g_aBoss[nCntBoss].pos.x = SCREEN_WIDTH - (BOSS_WIDTH / 2) - 50.0f;

				g_EnemyBulletCnt++;
				if (g_EnemyBulletCnt == 150)
				{
					if (g_aBoss[nCntBoss].nLife <= 40)
					{
						if (g_EnemyBulletTypeCnt == 1)
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 0,15.0f,45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 6, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.5f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f),7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.5f, 0.0f), 8, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 9, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.5f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.5f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt = 0;

						}
						else
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.9f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.9f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.9f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.9f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 13, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.6f, 0.0f), 12, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.8f, 0.0f), 11, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.6f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.8f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt++;


						}
						
					}

					else if (g_aBoss[nCntBoss].nLife > 40)
					{
						if (g_EnemyBulletTypeCnt == 1)
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 1.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.5f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -1.0f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.5f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 1.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.5f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -1.0f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.2f, 0.0f), 9, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.8f, 0.0f), 5, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.5f, 0.0f), 4, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.2f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.8f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.5f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							g_EnemyBulletTypeCnt = 0;
						}
						else
						{
							if (GetMode() == MODE_GAME)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.4f, 0.0f), 0, 15.0f, 45.0f);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.4f, 0.0f), 0, 15.0f, 45.0f);
							}
							else if (GetMode() == MODE_STAGE1)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.0f, 0.0f), 2, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, 0.4f, 0.0f), 1, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(3.0f, -0.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							else if (GetMode() == MODE_STAGE3)
							{
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.0f, 0.0f), 13, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 0.6f, 0.0f), 12, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.4f, 0.0f), 7, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, 1.8f, 0.0f), 11, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -0.6f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.4f, 0.0f), 3, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
								SetEnemyBullet(D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + 50.0f, g_aBoss[nCntBoss].pos.y, g_aBoss[nCntBoss].pos.z), D3DXVECTOR3(2.0f, -1.8f, 0.0f), 10, ENEMY_BULLET_WIDTH_HEIGHT, ENEMY_BULLET_WIDTH_HEIGHT);
							}
							
							g_EnemyBulletTypeCnt++;
						}
						
					}

					
					g_EnemyBulletCnt = 0;
				}
				
			}


			if (g_aBoss[nCntBoss].pos.x <= 0 - BOSS_WIDTH)
			{
				g_aBoss[nCntBoss].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
			}

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawBoss(void)
{
	int nCntBoss;

	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//�e�N�X�`��
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
				nCntBoss * 4,					//�`����J�n���钸�_�̃C���f�b�N�X
				2);					//�`�悷��v���~�e�B�u��
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetBoss(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move,int nLife)
{
	int nCntBoss;
	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)
		{
			g_aBoss[nCntBoss].pos = pos;
			//���_���W�̐ݒ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += (nCntBoss * 4);


			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y - BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_WIDTH / 2.0f, g_aBoss[nCntBoss].pos.y + BOSS_HEIGHT / 2.0f, 0.0f);

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBoss->Unlock();

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].nLife = nLife;
			g_aBoss[nCntBoss].move = move;
			g_aBoss[nCntBoss].bUse = true;
			break;
		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
Boss *GetBoss(void)
{
	return &g_aBoss[0];
}

