//=======================================================================
//�h���[���Ɋւ��鏈��
//Aouthor: �����@����
//=======================================================================

#include "main.h"
#include "drone.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "EnemyBullet.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "billboard.h"
#include "evolutionGauge.h"
#include "enemylife.h"
#include "boss.h"
#include "score.h"
#include "sound.h"
#include "modeltxt.h"

//=======================================================================
//�O���[�o���ϐ��錾
//=======================================================================
DRONE g_aDrone[MAX_DRONE];						//�h���[���̍\����
int g_nCntDrone;
int g_nCntAllDrone;

//=======================================================================
//����������
//=======================================================================
void InitDrone(void)
{

	//������
	g_nCntAllDrone = 0;
	g_nCntDrone = 0;
	for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++)
	{
		g_aDrone[nCntDrone].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDrone[nCntDrone].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDrone[nCntDrone].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDrone[nCntDrone].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aDrone[nCntDrone].nIdxParent = 0;
		g_aDrone[nCntDrone].bUse = false;
		g_aDrone[nCntDrone].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_aDrone[nCntDrone].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_aDrone[nCntDrone].nNum = 0;
		g_aDrone[nCntDrone].bTurnDrone = false;
		g_aDrone[nCntDrone].bTurnDrone2 = false;
		g_aDrone[nCntDrone].bDamage = false;
		g_aDrone[nCntDrone].fDepth = 0.0f;
		g_aDrone[nCntDrone].fDifferRot = 0.0f;
		g_aDrone[nCntDrone].fHeight = 0.0f;
		g_aDrone[nCntDrone].fNumDrone = 0.0f;
		g_aDrone[nCntDrone].fNumTurnDrone = 0.0f;
		g_aDrone[nCntDrone].frotVecX = 0.0f;
		g_aDrone[nCntDrone].frotVecZ = 0.0f;
		g_aDrone[nCntDrone].fToPlayerR = 0.0f;
		g_aDrone[nCntDrone].fWidth = 0.0f;
		g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_STOP;
		g_aDrone[nCntDrone].nCntMoveTime = 0;
		g_aDrone[nCntDrone].nCntStop = 0;
		g_aDrone[nCntDrone].nLife = 0;
		g_aDrone[nCntDrone].nIdx = 0;
		g_aDrone[nCntDrone].nIdxLife = 0;
		for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
		{
			g_aDrone[nCntDrone].nIdxEffect[nCnt] = 0;
		}

	}

	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����
	

	//�e�̐ݒ�
}

//=======================================================================
//�I������
//=======================================================================
void UninitDrone(void)
{
	for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++)
	{
		//���b�V���̔j��
		if (g_aDrone[nCntDrone].pMesh != NULL)
		{
			g_aDrone[nCntDrone].pMesh->Release();
			g_aDrone[nCntDrone].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aDrone[nCntDrone].pBuffMat != NULL)
		{
			g_aDrone[nCntDrone].pBuffMat->Release();
			g_aDrone[nCntDrone].pBuffMat = NULL;
		}
	}
}

//=======================================================================
//�X�V����
//=======================================================================
void UpdateDrone(void)
{
	EnemyLife *pEnemyLife = GetEnemyLife();
	Camera *pCamera = GetCamera();
	PLAYER *pPlayer = GetPlayer();
	for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++, pEnemyLife++)
	{
		if (g_aDrone[nCntDrone].bUse == true && pPlayer->bUse == true)
		{
			g_aDrone[nCntDrone].posOld = g_aDrone[nCntDrone].pos;
			g_aDrone[nCntDrone].pos += g_aDrone[nCntDrone].move;
			g_aDrone[nCntDrone].frotVecX = pPlayer->pos.x - g_aDrone[nCntDrone].pos.x;
			g_aDrone[nCntDrone].frotVecZ = pPlayer->pos.z - g_aDrone[nCntDrone].pos.z;
			g_aDrone[nCntDrone].fToPlayerR = sqrt(g_aDrone[nCntDrone].frotVecX * g_aDrone[nCntDrone].frotVecX + g_aDrone[nCntDrone].frotVecZ * g_aDrone[nCntDrone].frotVecZ);

			//���b�N�I������
			if (pCamera->bRockOn == true && pCamera->nEnemyNumber == nCntDrone && pCamera->nWhoRockOn == 0)
			{
				SetBillboard(g_aDrone[nCntDrone].pos, 100.0f, 100.0f);
				SetPositionBillboard(D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y + 20.0f, g_aDrone[nCntDrone].pos.z), g_aDrone[nCntDrone].bUse);
			}


			//�h���[���̓����̏���
			MoveTypeDrone(nCntDrone);

			//��]�̊���
			if (g_aDrone[nCntDrone].fNumTurnDrone > D3DX_PI)
			{
				g_aDrone[nCntDrone].fNumTurnDrone = -D3DX_PI - (D3DX_PI - g_aDrone[nCntDrone].fNumTurnDrone);
			}
			else if (g_aDrone[nCntDrone].fNumTurnDrone < -D3DX_PI)
			{
				g_aDrone[nCntDrone].fNumTurnDrone = D3DX_PI - (-D3DX_PI - g_aDrone[nCntDrone].fNumTurnDrone);
			}

			if (g_aDrone[nCntDrone].rot.y < 0.0f && -g_aDrone[nCntDrone].rot.y + g_aDrone[nCntDrone].fNumTurnDrone > D3DX_PI)
			{
				g_aDrone[nCntDrone].fDifferRot = (-D3DX_PI - g_aDrone[nCntDrone].rot.y) + -(D3DX_PI - g_aDrone[nCntDrone].fNumTurnDrone);
			}
			else if (g_aDrone[nCntDrone].rot.y >= D3DX_PI / 2.0f && g_aDrone[nCntDrone].rot.y - g_aDrone[nCntDrone].fNumTurnDrone > D3DX_PI)
			{
				g_aDrone[nCntDrone].fDifferRot = (D3DX_PI - g_aDrone[nCntDrone].rot.y) - (-D3DX_PI - g_aDrone[nCntDrone].fNumTurnDrone);
			}
			else
			{
				g_aDrone[nCntDrone].fDifferRot = (g_aDrone[nCntDrone].fNumTurnDrone - g_aDrone[nCntDrone].rot.y);
			}

			g_aDrone[nCntDrone].rot.y += g_aDrone[nCntDrone].fDifferRot * 0.1f;
			if (g_aDrone[nCntDrone].rot.y - g_aDrone[nCntDrone].fNumTurnDrone < 0.001 && g_aDrone[nCntDrone].rot.y - g_aDrone[nCntDrone].fNumTurnDrone > -0.001)
			{
				g_aDrone[nCntDrone].bTurnDrone = false;

			}

			if (g_aDrone[nCntDrone].rot.y > D3DX_PI)
			{
				g_aDrone[nCntDrone].rot.y = -D3DX_PI;
			}
			else if (g_aDrone[nCntDrone].rot.y < -D3DX_PI)
			{
				g_aDrone[nCntDrone].rot.y = D3DX_PI;
			}

			//�h���[�����m�̓����蔻��
			CollisionDrone(&g_aDrone[nCntDrone].pos, &g_aDrone[nCntDrone].posOld, &g_aDrone[nCntDrone].move, g_aDrone[nCntDrone].fWidth, 1000.0f, g_aDrone[nCntDrone].fDepth);
			//�G�Ƃ̓����蔻��
			CollisionEnemy(&g_aDrone[nCntDrone].pos, &g_aDrone[nCntDrone].posOld, &g_aDrone[nCntDrone].move, g_aDrone[nCntDrone].fWidth, 1000.0f, g_aDrone[nCntDrone].fDepth);
			//�{�X�Ƃ̓����蔻��
			CollisionBoss(&g_aDrone[nCntDrone].pos, &g_aDrone[nCntDrone].posOld, &g_aDrone[nCntDrone].move, g_aDrone[nCntDrone].fWidth, 1000.0f, g_aDrone[nCntDrone].fDepth);
			//�v���C���[�̒e�������������̏���
			int nBulletType = CollisionBullet(&g_aDrone[nCntDrone].pos, g_aDrone[nCntDrone].fWidth);
			if (nBulletType == 1)
			{
				g_aDrone[nCntDrone].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 2)
			{
				g_aDrone[nCntDrone].nLife--;
				SetAddEvolutionGauge(1.0f);
			}
			else if (nBulletType == 3)
			{
				g_aDrone[nCntDrone].nLife -= 5;
				SetAddEvolutionGauge(5.0f);
			}

			//�v���C���[�̌��������������̏���
			if (g_aDrone[nCntDrone].bDamage == false && pPlayer->bSlash == true)
			{
				if (CollisionSword(&g_aDrone[nCntDrone].pos, g_aDrone[nCntDrone].fWidth) == true)
				{
					if (pPlayer->nType == PLAYERTYPE_SPEED)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aDrone[nCntDrone].nLife -= 3;
						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_NOMAL)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aDrone[nCntDrone].nLife -= 3;
						SetAddEvolutionGauge(3.0f);
						SetScore(300);
					}
					else if (pPlayer->nType == PLAYERTYPE_POWER)
					{
						PlaySound(SOUND_LABEL_HIT);
						g_aDrone[nCntDrone].nLife -= 6;
						SetScore(600);
					}
					g_aDrone[nCntDrone].bDamage = true;
				}
			}

			if (pPlayer->bSlash == false)
			{
				g_aDrone[nCntDrone].bDamage = false;
			}
			

			if (g_aDrone[nCntDrone].nLife <= 0)
			{
				g_nCntAllDrone--;
				g_aDrone[nCntDrone].nLife = 0;
				g_aDrone[nCntDrone].bUse = false;
				if (g_aDrone[nCntDrone].Type == DRONETYPE_001 || g_aDrone[nCntDrone].Type == DRONETYPE_002)
				{
					SetScore(1000);
				}
				else if (g_aDrone[nCntDrone].Type == DRONETYPE_003)
				{
					SetScore(4000);
				}
				if (pCamera->nEnemyNumber == nCntDrone &&pCamera->nWhoRockOn == 0)
				{
					pCamera->bRockOn = false;
				}
			}

			//�e�̐ݒ�
			SetPositionShadow(g_aDrone[nCntDrone].nIdx, g_aDrone[nCntDrone].pos, g_aDrone[nCntDrone].bUse);
			//���C�t�Q�[�W�̐ݒ�
			if (g_aDrone[nCntDrone].Type == DRONETYPE_001)
			{
				SetPositionEnemyLife(g_aDrone[nCntDrone].nIdxLife, D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y + 80.0f, g_aDrone[nCntDrone].pos.z),
					g_aDrone[nCntDrone].bUse, DRONE001_LIFE, g_aDrone[nCntDrone].nLife, 50.0f);
			}
			else if (g_aDrone[nCntDrone].Type == DRONETYPE_002)
			{
				SetPositionEnemyLife(g_aDrone[nCntDrone].nIdxLife, D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y + 80.0f, g_aDrone[nCntDrone].pos.z),
					g_aDrone[nCntDrone].bUse, DRONE002_LIFE, g_aDrone[nCntDrone].nLife, 50.0f);
			}
			else if (g_aDrone[nCntDrone].Type == DRONETYPE_003)
			{
				SetPositionEnemyLife(g_aDrone[nCntDrone].nIdxLife, D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y + 80.0f, g_aDrone[nCntDrone].pos.z),
					g_aDrone[nCntDrone].bUse, DRONE003_LIFE, g_aDrone[nCntDrone].nLife, 50.0f);
			}
			CollisionModelTxt(&g_aDrone[nCntDrone].move, &g_aDrone[nCntDrone].pos, &g_aDrone[nCntDrone].posOld, g_aDrone[nCntDrone].fWidth);
		}
	}
}

//=======================================================================
//�`�揈��
//=======================================================================
void DrawDrone(void)
{
	LPDIRECT3DDEVICE9 pDevice;					//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();						//�f�o�C�X���擾����

	for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++)
	{
		if (g_aDrone[nCntDrone].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
			D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

			D3DXMatrixIdentity(&g_aDrone[nCntDrone].mtxWorld);		//���[���h�}�g���b�N�X�̏�����

																	//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aDrone[nCntDrone].rot.y, g_aDrone[nCntDrone].rot.x, g_aDrone[nCntDrone].rot.z);
			D3DXMatrixMultiply(&g_aDrone[nCntDrone].mtxWorld, &g_aDrone[nCntDrone].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y, g_aDrone[nCntDrone].pos.z);
			D3DXMatrixMultiply(&g_aDrone[nCntDrone].mtxWorld, &g_aDrone[nCntDrone].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aDrone[nCntDrone].mtxWorld);

			//���݂̃}�e���A����ۑ�
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aDrone[nCntDrone].pBuffMat->GetBufferPointer();
			for (int nCntMat = 0; nCntMat < (int)g_aDrone[nCntDrone].nNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aDrone[nCntDrone].pTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aDrone[nCntDrone].pMesh->DrawSubset(nCntMat);
			}

			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=======================================================================
//�ݒ菈��
//=======================================================================
void SetDrone(D3DXVECTOR3 pos, D3DXVECTOR3 rot, DRONETYPE Type)
{
	if (g_aDrone[g_nCntDrone].bUse == false)
	{
		g_aDrone[g_nCntDrone].rot = rot;
		g_aDrone[g_nCntDrone].pos = pos;
		g_aDrone[g_nCntDrone].Type = Type;

		g_aDrone[g_nCntDrone].bUse = true;

		g_nCntAllDrone++;
		//�G�̗̑̓Q�[�W
		g_aDrone[g_nCntDrone].nIdxLife = SetEnemyLife(D3DXVECTOR3(g_aDrone[g_nCntDrone].pos.x, g_aDrone[g_nCntDrone].pos.y + 80.0f, g_aDrone[g_nCntDrone].pos.z), 50.0f, 5.0f);
		//�e�̐ݒ�
		g_aDrone[g_nCntDrone].nIdx = SetShadow(D3DXVECTOR3(g_aDrone[g_nCntDrone].pos.x, 0.0f, g_aDrone[g_nCntDrone].pos.z), g_aDrone[g_nCntDrone].fWidth, g_aDrone[g_nCntDrone].fDepth);


		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice;
		pDevice = GetDevice();

		//X�t�@�C���ǂݍ���
		if (g_aDrone[g_nCntDrone].Type == DRONETYPE_001)
		{
			D3DXLoadMeshFromX("data/MODEL/enemy_drone/drone001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aDrone[g_nCntDrone].pBuffMat, NULL, &g_aDrone[g_nCntDrone].nNumMat, &g_aDrone[g_nCntDrone].pMesh);

			g_aDrone[g_nCntDrone].nLife = DRONE001_LIFE;
		}
		else if (g_aDrone[g_nCntDrone].Type == DRONETYPE_002)
		{
			D3DXLoadMeshFromX("data/MODEL/enemy_drone/drone002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aDrone[g_nCntDrone].pBuffMat, NULL, &g_aDrone[g_nCntDrone].nNumMat, &g_aDrone[g_nCntDrone].pMesh);

			g_aDrone[g_nCntDrone].nLife = DRONE002_LIFE;
		}
		else if (g_aDrone[g_nCntDrone].Type == DRONETYPE_003)
		{
			D3DXLoadMeshFromX("data/MODEL/enemy_drone/drone003.x", D3DXMESH_SYSTEMMEM, pDevice, NULL,
				&g_aDrone[g_nCntDrone].pBuffMat, NULL, &g_aDrone[g_nCntDrone].nNumMat, &g_aDrone[g_nCntDrone].pMesh);

			g_aDrone[g_nCntDrone].nLife = DRONE003_LIFE;
		}

		
		//���_���̎擾
		int nNumVtx;		//���_��
		DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

							//���_�����擾
		nNumVtx = g_aDrone[g_nCntDrone].pMesh->GetNumVertices();
		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aDrone[g_nCntDrone].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		g_aDrone[g_nCntDrone].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			//�S�Ă̒��_���r���čő�l�ƍŏ���𔲂��o��
			//�ő�l
			if (vtx.x >= g_aDrone[g_nCntDrone].vtxMax.x)
			{
				g_aDrone[g_nCntDrone].vtxMax.x = vtx.x;
			}
			if (vtx.y >= g_aDrone[g_nCntDrone].vtxMax.y)
			{
				g_aDrone[g_nCntDrone].vtxMax.y = vtx.y;
			}
			if (vtx.z >= g_aDrone[g_nCntDrone].vtxMax.z)
			{
				g_aDrone[g_nCntDrone].vtxMax.z = vtx.z;
			}
			//�ŏ��l
			if (vtx.x <= g_aDrone[g_nCntDrone].vtxMin.x)
			{
				g_aDrone[g_nCntDrone].vtxMin.x = vtx.x;
			}
			if (vtx.y <= g_aDrone[g_nCntDrone].vtxMin.y)
			{
				g_aDrone[g_nCntDrone].vtxMin.y = vtx.y;
			}
			if (vtx.z <= g_aDrone[g_nCntDrone].vtxMin.z)
			{
				g_aDrone[g_nCntDrone].vtxMin.z = vtx.z;
			}

			g_aDrone[g_nCntDrone].fWidth = g_aDrone[g_nCntDrone].vtxMax.x - g_aDrone[g_nCntDrone].vtxMin.x;
			g_aDrone[g_nCntDrone].fHeight = g_aDrone[g_nCntDrone].vtxMax.y - g_aDrone[g_nCntDrone].vtxMin.y;
			g_aDrone[g_nCntDrone].fDepth = g_aDrone[g_nCntDrone].vtxMax.z - g_aDrone[g_nCntDrone].vtxMin.z;


			pVtxBuff += sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		//���_�o�b�t�@���A�����b�N
		g_aDrone[g_nCntDrone].pMesh->UnlockVertexBuffer();
	}
	g_nCntDrone++;
	if (g_nCntDrone >= MAX_DRONE)
	{
		g_nCntDrone = 0;
	}
}

//=======================================================================
//�h���[���̓������̏���
//=======================================================================
void MoveTypeDrone(int nCntDrone)
{
	//�v���C���[�̎擾
	PLAYER *pPlayer = GetPlayer();

	if (g_aDrone[nCntDrone].fToPlayerR <= DRONE_SEARCH && g_aDrone[nCntDrone].MoveType != DRONE_MOVETYPE_ATTACK)
	{
		g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_ATTACK;
	}

	if (g_aDrone[nCntDrone].MoveType == DRONE_MOVETYPE_MOVE)
	{
		g_aDrone[nCntDrone].nCntMoveTime++;
		if (g_aDrone[nCntDrone].nCntMoveTime <= rand() % 650 + 450)
		{
			g_aDrone[nCntDrone].move.z = -cosf(g_aDrone[nCntDrone].rot.y) * DRONE_SPEED;
			g_aDrone[nCntDrone].move.x = -sinf(g_aDrone[nCntDrone].rot.y) * DRONE_SPEED;
		}
		else
		{
			g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_STOP;
			g_aDrone[nCntDrone].nCntMoveTime = 0;
		}
	}
	else if (g_aDrone[nCntDrone].MoveType == DRONE_MOVETYPE_STOP)
	{
		g_aDrone[nCntDrone].move.z = 0.0f;
		g_aDrone[nCntDrone].move.x = 0.0f;

		g_aDrone[nCntDrone].nCntStop++;
		if (g_aDrone[nCntDrone].nCntStop >= DRONE_STOP_TIME)
		{
			g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_TURN;
			g_aDrone[nCntDrone].bTurnDrone2 = true;
			g_aDrone[nCntDrone].nCntStop = 0;
		}
	}
	else if (g_aDrone[nCntDrone].MoveType == DRONE_MOVETYPE_TURN)
	{
		if (g_aDrone[nCntDrone].bTurnDrone2 == true)
		{
			g_aDrone[nCntDrone].fNumTurnDrone = DRONE_RAND;
			g_aDrone[nCntDrone].bTurnDrone2 = false;
		}
		if (g_aDrone[nCntDrone].rot.y - g_aDrone[nCntDrone].fNumTurnDrone < 0.05 && g_aDrone[nCntDrone].rot.y - g_aDrone[nCntDrone].fNumTurnDrone > -0.05)
		{
			g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_MOVE;
		}
	}
	else if (g_aDrone[nCntDrone].MoveType == DRONE_MOVETYPE_ATTACK)
	{
		g_aDrone[nCntDrone].fNumTurnDrone = atan2(g_aDrone[nCntDrone].frotVecX, g_aDrone[nCntDrone].frotVecZ) - D3DX_PI;

		g_aDrone[nCntDrone].move.z = 0.0f;
		g_aDrone[nCntDrone].move.x = 0.0f;

		g_aDrone[nCntDrone].nCntStop++;

		if (g_aDrone[nCntDrone].Type == DRONETYPE_001)
		{
			if (g_aDrone[nCntDrone].nCntStop >= 100)
			{
				SetEnemyBullet(D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y, g_aDrone[nCntDrone].pos.z),
					D3DXVECTOR3(sinf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
					15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_DRONE001);
				g_aDrone[nCntDrone].nCntStop = 0;
			}
		}
		else if (g_aDrone[nCntDrone].Type == DRONETYPE_002)
		{
			if (g_aDrone[nCntDrone].nCntStop == 50)
			{
				SetEnemyBullet(D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y, g_aDrone[nCntDrone].pos.z),
					D3DXVECTOR3(sinf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
					15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_DRONE002);
			}
			else if(g_aDrone[nCntDrone].nCntStop >= 100)
			{
				SetEnemyBullet(D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y, g_aDrone[nCntDrone].pos.z),
					D3DXVECTOR3(sinf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
					15.0f, 15.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_DRONE002);
				g_aDrone[nCntDrone].nCntStop = 0;
			}
		}
		else if (g_aDrone[nCntDrone].Type == DRONETYPE_003)
		{
			if (g_aDrone[nCntDrone].nCntStop >= 100)
			{
				SetEnemyBullet(D3DXVECTOR3(g_aDrone[nCntDrone].pos.x, g_aDrone[nCntDrone].pos.y, g_aDrone[nCntDrone].pos.z),
					D3DXVECTOR3(sinf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED, 0.0f, cosf(g_aDrone[nCntDrone].rot.y + D3DX_PI) * ENEMYBULLET_SPEED),
					30.0f, 30.0f, D3DXCOLOR(255, 255, 255, 255), ENEMYBULLET_MOVETYPE_DRONE003);
				g_aDrone[nCntDrone].nCntStop = 0;
			}
		}


		if (g_aDrone[nCntDrone].fToPlayerR > DRONE_SEARCH)
		{
			g_aDrone[nCntDrone].MoveType = DRONE_MOVETYPE_STOP;
		}
	}
	

	//-------------------------------------------------
	//�G�̈ړ�����
	//-------------------------------------------------
	if (g_aDrone[nCntDrone].pos.x >= PLAYER_LIMIT)
	{
		g_aDrone[nCntDrone].pos.x = PLAYER_LIMIT;
	}
	else if (g_aDrone[nCntDrone].pos.x <= -PLAYER_LIMIT)
	{
		g_aDrone[nCntDrone].pos.x = -PLAYER_LIMIT;
	}
	if (g_aDrone[nCntDrone].pos.z >= PLAYER_LIMIT)
	{
		g_aDrone[nCntDrone].pos.z = PLAYER_LIMIT;
	}
	else if (g_aDrone[nCntDrone].pos.z <= -PLAYER_LIMIT)
	{
		g_aDrone[nCntDrone].pos.z = -PLAYER_LIMIT;
	}
}

//=======================================================================
//�h���[���Ƃ̓����蔻��
//=======================================================================
void CollisionDrone(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pBeforePos, D3DXVECTOR3 *pMove, float fWidth, float fHeight, float fDepth)
{
	DRONE *pDrone;
	pDrone = GetDrone();

	for (int nCntDrone = 0; nCntDrone < MAX_DRONE; nCntDrone++, pDrone++)
	{
		if (pDrone->bUse == true)
		{
			if (pPos->x > pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z > pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->y <= pDrone->pos.y + pDrone->fHeight &&
				pBeforePos->y >= pDrone->pos.y + pDrone->fHeight)
			{
				pPos->y = pDrone->pos.y + pDrone->fHeight;
				pMove->y = 0.0f;
			}
			else if (pPos->x > pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z > pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->y >= pDrone->pos.y - fHeight &&
					pBeforePos->y <= pDrone->pos.y - fHeight)
			{
				pPos->y = pDrone->pos.y - fHeight;
			}

			if (pPos->y < pDrone->pos.y + pDrone->fHeight &&
				pPos->y > pDrone->pos.y - fHeight &&
				pPos->z > pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f &&
				pPos->z < pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f &&
				pPos->x >= pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f &&
				pBeforePos->x <= pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f)
			{
				pPos->x = pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f;
			}
			else if (pPos->y < pDrone->pos.y + pDrone->fHeight &&
					pPos->y > pDrone->pos.y - fHeight &&
					pPos->z > pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f &&
					pPos->z < pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f &&
					pPos->x <= pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f &&
					pBeforePos->x >= pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f)
			{
				pPos->x = pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f;
			}

			if (pPos->y < pDrone->pos.y + pDrone->fHeight &&
				pPos->y > pDrone->pos.y - fHeight &&
				pPos->x > pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f &&
				pPos->x < pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f &&
				pPos->z >= pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f &&
				pBeforePos->z <= pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f)
			{
				pPos->z = pDrone->pos.z - pDrone->fDepth / 2.0f - fDepth / 2.0f;
			}
			else if (pPos->y < pDrone->pos.y + pDrone->fHeight &&
					pPos->y > pDrone->pos.y - fHeight &&
					pPos->x > pDrone->pos.x - pDrone->fWidth / 2.0f - fWidth / 2.0f &&
					pPos->x < pDrone->pos.x + pDrone->fWidth / 2.0f + fWidth / 2.0f &&
					pPos->z <= pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f &&
					pBeforePos->z >= pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f)
			{
				pPos->z = pDrone->pos.z + pDrone->fDepth / 2.0f + fDepth / 2.0f;
			}

		}
	}
}

//=======================================================================
//�擾����
//=======================================================================
DRONE *GetDrone(void)
{
	return &g_aDrone[0];
}

//=======================================================================
//�擾����
//=======================================================================
int GetAllDrone(void)
{
	return g_nCntAllDrone;
}