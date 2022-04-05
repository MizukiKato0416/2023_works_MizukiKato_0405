//=======================================================================
//�v���C���[�Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "Polygon.h"
#include "input.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "enemy.h"
#include "boss.h"
#include "explosion.h"
#include "item.h"
#include "life.h"
#include "special.h"
#include "sound.h"


//�}�N����`
#define POLYGON_WIDTH (65.0f*1.2)		//�v���C���[�̕�
#define POLYGON_HEIGHT (100.0f*1.2)		//�v���C���[�̍���
#define POLYGON_SPEED (2.0f)			//�v���C���[�̑���
#define POLYGON_TYPE (3)				//�v���C���[�̎��
#define PLAYER_HIT (0.0f)				//�v���C���[�̓����蔻��̃}�C�i�X

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
LPDIRECT3DTEXTURE9 g_pTexturePolygon[POLYGON_TYPE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;			//�A�j���[�V�����J�E���^
int g_nCntEnemyAnim;		//�G�̃A�j���[�V�����J�E���^
int g_nPatternAnim;			//�A�j���[�V�����p�^�[��No
int g_nPatternBullet;			//�A�j���[�V�����p�^�[��No
bool g_bItem;					//�K�E�Z�̎g�p�\�s�\
D3DXVECTOR3 g_posPolygon;		//�|���S���̈ʒu
D3DXVECTOR3 g_movePolygon;		//�|���S���̈ړ���

//=======================================================================
//����������
//=======================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//boy1.png",
		&g_pTexturePolygon[0]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//sleep_cry_man.png",
		&g_pTexturePolygon[1]);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data//TEXTURE//school_sleep.png",
		&g_pTexturePolygon[2]);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounterAnim = 0;		//�J�E���^�[��������
	g_nCntEnemyAnim = 0;		//�G�̃A�j���[�V�����J�E���^��������
	g_nPatternAnim = 0;		//�p�^�[��No��������
	g_nPatternBullet = 0;
	g_bItem = false;
	srand((unsigned int)time(NULL));


	g_posPolygon = D3DXVECTOR3(100, SCREEN_HEIGHT/2, 0.0f);
	g_movePolygon = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	pVtx[0].pos = D3DXVECTOR3(100 - POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(100 + POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100 - POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 + POLYGON_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(100 + POLYGON_WIDTH / 2, SCREEN_HEIGHT / 2 + POLYGON_HEIGHT / 2, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//=======================================================================
//�I������
//=======================================================================
void UninitPolygon(void)
{
	int nCntPolygon;
	for (nCntPolygon = 0; nCntPolygon < POLYGON_TYPE; nCntPolygon++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePolygon[nCntPolygon] != NULL)
		{
			g_pTexturePolygon[nCntPolygon]->Release();
			g_pTexturePolygon[nCntPolygon] = NULL;
		}
	}
	

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdatePolygon(void)
{
	g_nCounterAnim++;
	if (g_nCounterAnim == 90)
	{
		g_nCounterAnim = 0;		//�J�E���^�[�������n�ɖ߂�
		g_nPatternAnim++;		//�p�^�[��No���X�V
		if (g_nPatternAnim > 1)
		{
			g_nPatternAnim = 0;
		}

		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f + 0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(g_nPatternAnim * 0.5f + 0.5f, 1.0f);


		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}

	//�C�ӂ̃L�[�������ꂽ���ǂ���
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_posPolygon.x -= POLYGON_SPEED;
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.75f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.75f)*POLYGON_SPEED;
			
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.25f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.25f)*POLYGON_SPEED;
			
		}
		else
		{
			g_posPolygon.x += sinf(-D3DX_PI*0.5f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(-D3DX_PI*0.5f)*POLYGON_SPEED;
			
		}

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH/2, g_posPolygon.y - POLYGON_HEIGHT/2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_posPolygon.x += POLYGON_SPEED;
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardPress(DIK_W) == true)
		{
			g_posPolygon.x += sinf(D3DX_PI*0.75f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.75f)*POLYGON_SPEED;
			
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_posPolygon.x += sinf(D3DX_PI*0.25f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.25f)*POLYGON_SPEED;
			
		}
		else
		{
			g_posPolygon.x += sinf(D3DX_PI*0.5f)*POLYGON_SPEED;
			g_posPolygon.y += cosf(D3DX_PI*0.5f)*POLYGON_SPEED;
		}

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_posPolygon.y += POLYGON_SPEED;
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

		g_posPolygon.x += sinf(D3DX_PI*0.0f)*POLYGON_SPEED;
		g_posPolygon.y += cosf(D3DX_PI*0.0f)*POLYGON_SPEED;
		

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_posPolygon.y -= POLYGON_SPEED;
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
								//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
		g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	

		g_posPolygon.x += sinf(D3DX_PI*1.0f)*POLYGON_SPEED;
		g_posPolygon.y += cosf(D3DX_PI*1.0f)*POLYGON_SPEED;

		pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPolygon->Unlock();
	}


	//�X�y�[�X�L�[���������Ƃ��̏���
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		g_nPatternBullet++;
		if (g_nPatternBullet >= 40)
		{
			if (GetMode() == MODE_GAME)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 0, 15.0f, 15.0f);
			}
			else if (GetMode() == MODE_STAGE1)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 1, 20.0f, 20.0f);
			}
			else if (GetMode() == MODE_STAGE3)
			{
				PlaySound(SOUND_LABEL_shot000);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, -1.3f, 0.0f), 3, 15.0f, 15.0f);
				//SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, -0.7f, 0.0f), 3, 15.0f, 15.0f);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 3, 15.0f, 15.0f);
				//SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.7f, 0.0f), 3, 15.0f, 15.0f);
				SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 1.3f, 0.0f), 3, 15.0f, 15.0f);
			}
			g_nPatternBullet = 0;
		}
		
	}

	//�R���g���[���L�[���������Ƃ��̏���(�K�E�Z����)
	Special *pSpecial;
	//�A�C�e���̎擾
	pSpecial = GetSpecial();
	if (g_bItem == true)
	{
		if (GetKeyboardTrigger(DIK_LCONTROL) == true)
		{

			PlaySound(SOUND_LABEL_shotSP000);
			SetBullet(D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y, g_posPolygon.z), D3DXVECTOR3(6.0f, 0.0f, 0.0f), 2, 200.0f, 400.0f);
			g_bItem = false;
			pSpecial->bUse = false;
		}
	}

	//�{�X�̎����ړ�
	if (GetMode() == MODE_GAME)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f), 0, D3DXVECTOR3(0.5f, 0.0f, 0.0f), 60);
	}
	else if (GetMode() == MODE_STAGE1)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f),1, D3DXVECTOR3(0.5f, 0.0f, 0.0f), 60);
	}
	else if (GetMode() == MODE_STAGE3)
	{
		SetBoss(D3DXVECTOR3(SCREEN_WIDTH + BOSS_WIDTH, SCREEN_HEIGHT / 2.0f, 0.0f), 2, D3DXVECTOR3(1.0f, 0.0f, 0.0f), 200);
	}

	g_nCntEnemyAnim++;		//�G�̃A�j���[�V�����J�E���^

	//�G�̎����ړ�
	Enemy *pEnemy;
	//�G�̎擾
	pEnemy = GetEnemy();
	if (GetMode() == MODE_GAME)
	{
		if (g_nCntEnemyAnim >= rand() % 200 + 200)
		{
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 120 + 80, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 300, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 500, 0.0f), 0, D3DXVECTOR3(1.2f, 0.0f, 0.0f), 2, 70.0f,70.0f);
			g_nCntEnemyAnim = 0;
		}
	}
	else if (GetMode() == MODE_STAGE1)
	{
		if (g_nCntEnemyAnim >= rand() % 350 + 300)
		{
			SetEnemy(D3DXVECTOR3(g_posPolygon.x, 0 - pEnemy->fEnemyHeight / 2, 0.0f), 1, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(rand() % 100 + (300 + pEnemy->fEnemyWidth / 2), 0 - pEnemy->fEnemyHeight / 2, 0.0f), 2, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			SetEnemy(D3DXVECTOR3(rand() % 100 + (550 + pEnemy->fEnemyWidth / 2), 0 - pEnemy->fEnemyHeight / 2, 0.0f), 1, D3DXVECTOR3(0.0f, -1.0f, 0.0f), 1, 70.0f, 70.0f);
			g_nCntEnemyAnim = 0;
		}
	}
	else if (GetMode() == MODE_STAGE3)
	{
		if (g_nCntEnemyAnim >= rand() % 350 + 300)
		{
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 120 + 80, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, g_posPolygon.y, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + pEnemy->fEnemyWidth, rand() % 100 + 500, 0.0f), 3, D3DXVECTOR3(2.2f, 0.0f, 0.0f), 2, 100.0f, 30.0f);
			g_nCntEnemyAnim = 0;
		}
	}


	//�G���v���C���[�ɂ������������̏���
	
	int nCntEnemy;
	//Enemy *pEnemy;

	//�G�̎擾
	//pEnemy = GetEnemy();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (g_posPolygon.x <= pEnemy->pos.x + pEnemy->fEnemyWidth / 2.0f + POLYGON_WIDTH/2.0f- PLAYER_HIT &&
				g_posPolygon.x >= pEnemy->pos.x - pEnemy->fEnemyWidth / 2.0f - POLYGON_WIDTH / 2.0f + PLAYER_HIT &&
				g_posPolygon.y <= pEnemy->pos.y + pEnemy->fEnemyHeight / 2.0f + POLYGON_HEIGHT / 2.0f - PLAYER_HIT &&
				g_posPolygon.y >= pEnemy->pos.y - pEnemy->fEnemyHeight / 2.0f - POLYGON_HEIGHT / 2.0f + PLAYER_HIT)
			{
				SetExplosion(g_posPolygon, (1.0f, 0.0f, 0.0f, 0.0f));
				PlaySound(SOUND_LABEL_DAMAGE000);
				pEnemy->bUse = false;
				SetLife(0.5f);
			}
		}
	}


	

	
	//-------------------------------------------------
	//�v���C���[�ƒe�̓����蔻��
	//-------------------------------------------------
	EnemyBullet*pEnemyBullet;
	int EnemyBulletnCnt;

	//�e�̎擾
	pEnemyBullet = GetEnemyBullet();
	for (EnemyBulletnCnt = 0; EnemyBulletnCnt < MAX_ENEMY_BULLET; EnemyBulletnCnt++, pEnemyBullet++)
	{
		if (pEnemyBullet->bUse == true)
		{


			if (g_posPolygon.x <= pEnemyBullet->pos.x + pEnemyBullet->EnemyBulletWidth / 2.0f + POLYGON_WIDTH / 2.0f - PLAYER_HIT &&
				g_posPolygon.x >= pEnemyBullet->pos.x - pEnemyBullet->EnemyBulletWidth / 2.0f - POLYGON_WIDTH / 2.0f + PLAYER_HIT &&
				g_posPolygon.y <= pEnemyBullet->pos.y + pEnemyBullet->EnemyBulletHeight / 2.0f + POLYGON_HEIGHT / 2.0f - PLAYER_HIT &&
				g_posPolygon.y >= pEnemyBullet->pos.y - pEnemyBullet->EnemyBulletHeight / 2.0f - POLYGON_HEIGHT / 2.0f + PLAYER_HIT)
			{

				SetExplosion(g_posPolygon, (1.0f, 0.0f, 0.0f, 0.0f));
				PlaySound(SOUND_LABEL_DAMAGE000);
				pEnemyBullet->bUse = false;
				SetLife(0.5f);
			}
		}
	}

	//-------------------------------------------------
	//�v���C���[�ƃA�C�e���̓����蔻��
	//-------------------------------------------------
	Item *pItem;
	int nCntItem;

	//�A�C�e���̎擾
	pItem = GetItem();
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{


			if (g_posPolygon.x <= pItem->pos.x + ITEM_WIDTH / 2.0f + POLYGON_WIDTH / 2.0f &&
				g_posPolygon.x >= pItem->pos.x - ITEM_WIDTH / 2.0f - POLYGON_WIDTH / 2.0f &&
				g_posPolygon.y <= pItem->pos.y + ITEM_HEIGHT / 2.0f + POLYGON_HEIGHT / 2.0f &&
				g_posPolygon.y >= pItem->pos.y - ITEM_HEIGHT / 2.0f - POLYGON_HEIGHT / 2.0f)
			{
				if (pItem->nType == 0)
				{
					PlaySound(SOUND_LABEL_CURE000);
					pItem->bUse = false;
					SetLife(-1.0f);
				}
				else if (pItem->nType == 1)
				{
					PlaySound(SOUND_LABEL_CURE000);
					pItem->bUse = false;
					if (g_bItem == false)
					{
						pSpecial->bUse = true;
						g_bItem = true;
					}
				}
			}
		}
	}

	//-------------------------------------------------
	//�v���C���[�̈ړ�����
	//-------------------------------------------------


	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_�o�b�t�@�����b�N���A���_�f�[�^�̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);



	if (g_posPolygon.x <= 0.0f + POLYGON_WIDTH / 2.0f)
	{
		g_posPolygon.x = 0.0f + POLYGON_WIDTH / 2.0f;		//�ʒu�̍X�V
	}

	else if (g_posPolygon.x >= 700)
	{
		g_posPolygon.x = 700;	//�ʒu�̍X�V
	}

	if (g_posPolygon.y <= 0.0f + POLYGON_HEIGHT / 2.0f)
	{
		g_posPolygon.y = 0.0f + POLYGON_HEIGHT / 2.0f;		//�ʒu�̍X�V
	}

	else if (g_posPolygon.y >= SCREEN_HEIGHT - POLYGON_HEIGHT / 2.0f)
	{
		g_posPolygon.y = SCREEN_HEIGHT - POLYGON_HEIGHT / 2.0f;		//�ʒu�̍X�V
	}


	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y - POLYGON_HEIGHT / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_WIDTH / 2, g_posPolygon.y + POLYGON_HEIGHT / 2, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();

}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����
												//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_2D));
	pDevice->SetFVF(FVF_VERTEX_2D);			//���_�t�H�[�}�b�g�̐ݒ�

	if (GetMode() == MODE_GAME)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[0]);	//�e�N�X�`���̐ݒ�
	}
	else if (GetMode() == MODE_STAGE1)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[1]);	//�e�N�X�`���̐ݒ�
	}
	else if (GetMode() == MODE_STAGE3)
	{
		pDevice->SetTexture(0, g_pTexturePolygon[2]);	//�e�N�X�`���̐ݒ�
	}
	
												//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
		0,					//�J�n���钸�_�̃C���f�b�N�X
		2);					//�`�悷��v���~�e�B�u��
}