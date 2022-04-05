//================================================
//�Q�[��01����
//Author: KatoMizuki
//================================================
#include "game01.h"
#include "manager.h"
#include "input_keyboard.h"
#include "player.h"
#include "meshsphere.h"
#include "meshfield.h"
#include "texture.h"
#include "object3D.h"
#include "fade.h"
#include "model_single.h"
#include "dungeon_room_director.h"
#include "dungeon_road_builder.h"
#include "dungeon_wall_builder.h"
#include "dungeon_check_road_builder.h"
#include "dungeon_enemy_road_builder.h"
#include "dungeon_start_road_builder.h"
#include "dungeon_end_road_builder.h"
#include "magic_circle.h"
#include "gauge.h"
#include "play_data.h"
#include "map.h"
#include "ui.h"
#include "pause.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//================================================
//�}�N����`
//================================================
#define GAME01_RECOVERYCOUNT	(20)		//�񕜂���p�x
#define GAME01_STAGE_SIZE		(7)			//�X�e�[�W�̃T�C�Y
#define GAME01_NEXT_SCENE_COUNT	(180)		//���̃V�[���܂ł̃J�E���g
#define GAME01_GAME_OVER_SIZE_X	(914.0f)	//�Q�[���I�[�o�[�̃T�C�YX
#define GAME01_GAME_OVER_SIZE_Y	(128.0f)	//�Q�[���I�[�o�[�̃T�C�YY

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CGame01::CGame01(int nPriority):CObject(nPriority)
{
	m_pHpGauge = nullptr;
	m_pMpGauge = nullptr;
	m_pSpGauge = nullptr;
	m_nRecoveryCounter = 0;
	m_nGameCounter = 0;
	m_pObjet2DGame = nullptr;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CGame01::~CGame01()
{
	
}

//================================================
//����������
//================================================
HRESULT CGame01::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Play(CSound::SOUND_LABEL_GAME_BGM);

	//�T�E���h�̉��ʒ���
	pSound->ControllVoice(CSound::SOUND_LABEL_GAME_BGM, 0.3f);

	//�ϐ�������
	m_nRecoveryCounter = 0;
	m_nGameCounter = 0;
	m_pObjet2DGame = nullptr;

	//�_���W�������\�z���镔�������ꂼ�ꐶ��
	//�������̕���
	CDungeonRoadBuilder *pDungeonRoadBuilder = nullptr;
	pDungeonRoadBuilder = CDungeonRoadBuilder::Create();
	//�ǂɂȂ镔��
	CDungeonWallBuilder *pDungeonWallBuilder = nullptr;
	pDungeonWallBuilder = CDungeonWallBuilder::Create();
	//�`�F�b�N�|�C���g�����镔��
	CDungeonCheckRoadBuilder *pDungeonCheckRoadBuilder = nullptr;
	pDungeonCheckRoadBuilder = CDungeonCheckRoadBuilder::Create();
	//�G�����镔��
	CDungeonEnemyRoadBuilder *pDungeonEnemyRoadBuilder = nullptr;
	pDungeonEnemyRoadBuilder = CDungeonEnemyRoadBuilder::Create();
	//�X�^�[�g���̕���
	CDungeonStartRoadBuilder *pDungeonStartRoadBuilder = nullptr;
	pDungeonStartRoadBuilder = CDungeonStartRoadBuilder::Create();
	//�I�_�̕���
	CDungeonEndRoadBuilder *pDungeonEndRoadBuilder = nullptr;
	pDungeonEndRoadBuilder = CDungeonEndRoadBuilder::Create();
	
	// �_�|���@�ɂ��_���W�����̐���
	// 5�����̃T�C�Y�ł͐����ł��Ȃ�
	int nDepth = GAME01_STAGE_SIZE;		//�c�̐�
	int nWidth = GAME01_STAGE_SIZE;		//���̐�
	int nWall = 1;		//��(����͌�)
	int nPath = 0;		//�ʂ�铹

	// �w��T�C�Y�Ő������O����ǂɂ���
	int maze[GAME01_STAGE_SIZE][GAME01_STAGE_SIZE];
	for (int nCntZ = 0; nCntZ < nDepth; nCntZ++)
	{
		for (int nCntX = 0; nCntX < nWidth; nCntX++)
		{
			if (nCntX == 0 || nCntZ == 0 || nCntX == nWidth - 1 || nCntZ == nDepth - 1)
			{
				if ((nCntX == 1 && nCntZ == 0) || nCntX == nWidth - 2 && nCntZ == nDepth - 1)
				{//�����̓X�^�[�g�n�_�ƃS�[���ɂ���̂œ������
					maze[nCntZ][nCntX] = nPath;
				}
				else
				{//����ȊO
					maze[nCntZ][nCntX] = nWall; // �O���͂��ׂĕ�
				}
			}
			else
			{
				maze[nCntZ][nCntX] = nPath;  // �O���ȊO�͒ʘH
			}
		}
	}

	// �_�𗧂āA�|��
	for (int nCntZ = 2; nCntZ < nDepth - 1; nCntZ += 2)
	{
		for (int nCntX = 2; nCntX < nWidth - 1; nCntX += 2)
		{
			maze[nCntZ][nCntX] = nWall; // �_�𗧂Ă�

			// �|����܂ŌJ��Ԃ�
			while (true)
			{
				// 1�s�ڂ̂ݏ�ɓ|����
				int nDirection = 0;
				if (nCntZ == 2)
				{
					nDirection = rand() % 4;
				}
				else
				{
					nDirection = rand() % 3;
				}

				// �_��|�����������߂�
				int nWallX = nCntX;
				int nWallZ = nCntZ;
				switch (nDirection)
				{
				case 0: // �E
					nWallX++;
					break;
				case 1: // ��
					nWallZ++;
					break;
				case 2: // ��
					nWallX--;
					break;
				case 3: // ��
					nWallZ--;
					break;
				}
				// �ǂ���Ȃ��ꍇ�̂ݓ|���ďI��
				if (maze[nWallZ][nWallX] != nWall ||
					(maze[nCntZ][nCntX - 1] == nWall && maze[nCntZ][nCntX + 1] == nWall && maze[nCntZ + 1][nCntX] == nWall))
				{
					maze[nWallZ][nWallX] = nWall;
					break;
				}
			}
		}
	}

	//�������铹�̎�ނ����߂邽�߂̕ϐ�
	int nNumRoad = 0;
	//�����̐���
	for (int nCntZ = 0; nCntZ < nDepth ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < nWidth ; nCntX++)
		{
			//�ǂ�������
			if (maze[nCntZ][nCntX] == nWall)
			{
				//�ǂ̕��������
				CDungeonRoomDirector::Create(pDungeonWallBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//�ǂ̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WALL);
			}
			else if (maze[nCntZ][nCntX] == nPath)
			{//����������
				
				if (nCntZ == 0 && nCntX == 1)
				{//���������̓X�^�[�g�̕����ɂ���
					CDungeonRoomDirector::Create(pDungeonStartRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));

					//�X�^�[�g�n�_�̃}�b�v�����
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::START);

				}
				else if (nCntX == nWidth - 2 && nCntZ == nDepth - 1)
				{//���������̓S�[���̕����ɂ���
					CDungeonRoomDirector::Create(pDungeonEndRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));

					//���[�v�̃}�b�v�����
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WARP);
				}
				else
				{
					//���̃}�b�v�����
					CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
						                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
						                     0.0f),
						         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);

					//3��ނ̓��̒����珇�Ԃɐ�������
					switch (nNumRoad)
					{
					case 0:
						//������
						CDungeonRoomDirector::Create(pDungeonRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					case 1:
						//�`�F�b�N�|�C���g�����铹
						CDungeonRoomDirector::Create(pDungeonCheckRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					case 2:
						//�G�����铹
						CDungeonRoomDirector::Create(pDungeonEnemyRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
						break;
					default:
						break;
					}
					//���̕����ɂȂ�悤���Z
					nNumRoad++;
					if (nNumRoad >= 3)
					{
						nNumRoad = 0;
					}
				}
			}
		}
	}

	//�I�u�W�F�N�g��������|�C���^
	CObject *pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	CObject *pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_CHECK_CIRCLE);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��`�F�b�N�|�C���g��������
		if (pObject->GetObjType() == CObject::OBJTYPE::CHECK_CIRCLE)
		{
			//�`�F�b�N�|�C���g�̃}�b�v�����
			CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				         D3DXVECTOR3(MAP_CHECK_SIZE, MAP_CHECK_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::CHECK);
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�I�u�W�F�N�g��������|�C���^
	pObject = nullptr;
	//�I�u�W�F�N�g����ۑ�����|�C���^�ϐ�
	pSaveObject = nullptr;

	//�擪�̃|�C���^����
	pObject = pObject->GetTopObj(CObject::PRIORITY_ENEMY);

	while (pObject != nullptr)
	{
		//���݂̃I�u�W�F�N�g�̃|�C���^��ۑ�
		pSaveObject = pObject;

		//�I�u�W�F�N�g�̎�ނ��G��������
		if (pObject->GetObjType() == CObject::OBJTYPE::ENEMY_BEE || pObject->GetObjType() == CObject::OBJTYPE::ENEMY_FAT)
		{
			//�G�̃}�b�v�����
			CMap::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				         D3DXVECTOR3(MAP_ENEMY_SIZE, MAP_ENEMY_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ENEMY);
		}
		//���̃I�u�W�F�N�g�ɐi�߂�
		pObject = pSaveObject->GetObjNext(pSaveObject);
	}

	//�`�F�b�N�|�C���g�̃}�b�v�̃|�C���^�ƈʒu�ݒ�
	CMap::SetCheckPointa();

	//�G�̃}�b�v�̃|�C���^�ƈʒu�ݒ�
	CMap::SetEnemyPointa();

	//�}�b�v�̈ʒu�ݒ�
	CMap::SetStartRoomPos();

	//�v���C���[�̃}�b�v�����
	CMap::Create(D3DXVECTOR3(MAP_POS_X, MAP_POS_Y, 0.0f),
		         D3DXVECTOR3(MAP_PLAYER_SIZE, MAP_PLAYER_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::PLAYER);

	//UI�̐���
	CObject2D *pObject2D = nullptr;
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                          D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP_FRAME"));

	//HP�Q�[�W�̐���
	m_pHpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_HP_POS_X, GAUGE_HP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_HP_SIZE_X, GAUGE_HP_SIZE_Y, 0.0f), PLAYER_MAX_HP, PLAYER_MAX_HP);
	m_pHpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetHpGauge(m_pHpGauge);

	//MP�Q�[�W�̐���
	m_pMpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_MP_SIZE_X, GAUGE_MP_SIZE_Y, 0.0f), PLAYER_MAX_MP, PLAYER_MAX_MP);
	m_pMpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_MP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetMpGauge(m_pMpGauge);

	//SP�Q�[�W�̐���
	m_pSpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_SP_SIZE_X, GAUGE_SP_SIZE_Y, 0.0f), PLAYER_MAX_SP, 0);
	m_pSpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_SP_GAUGE"));
	CManager::GetInstance()->GetPlayData()->SetSpGauge(m_pSpGauge);

	//UI�̐���
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
		                          D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP"));

	//�^�C���̐���
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f), 0);

	//�X�R�A�̐���
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//���b�Z�[�WUI�̍쐬
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
		        CObject::PRIORITY_UI, CUi::TYPE::MESSAGE_01);

	//�|�[�Y�̐���
	CPause::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================================================
//�I������
//================================================
void CGame01::Uninit(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�Đ�
	pSound->Stop(CSound::SOUND_LABEL_GAME_BGM);

	//�Q�[���I�[�o�[��Ԃ�������
	CManager::GetInstance()->GetPlayData()->SetGameOver(false);
	CManager::GetInstance()->GetPlayData()->SetGameClear(false);

	//���݂�HP�AMP�ASP��ۑ�
	CManager::GetInstance()->GetPlayData()->SetHitPoint(m_pHpGauge->GetGauge());
	CManager::GetInstance()->GetPlayData()->SetMagicPoint(m_pMpGauge->GetGauge());
	CManager::GetInstance()->GetPlayData()->SetSpecialPoint(m_pSpGauge->GetGauge());

	//�X�R�A��ۑ�
	CManager::GetInstance()->GetPlayData()->SetScore(CManager::GetInstance()->GetPlayData()->GetScorePoint()->GetScore());
	
	//�I�u�W�F�N�g�̔j��
	Release();
}

//================================================
//�X�V����
//================================================
void CGame01::Update(void)
{
	//�J�E���^�[�����Z
	m_nRecoveryCounter++;
	//����̒l�ȏ�ɂȂ�����
	if (m_nRecoveryCounter >= GAME01_RECOVERYCOUNT)
	{
		//0�ɂ���
		m_nRecoveryCounter = 0;
		//HP��MP���񕜂�����
		m_pHpGauge->AddGauge(1);
		m_pMpGauge->AddGauge(1);
	}
	
	//�Q�[���I�[�o�[�̎�
	if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true ||
		CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
	{
		GameOver();
	}

#ifdef DEBUG

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//Enter�L�[�A�X�^�[�g�{�^������������
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE::GAME02);
		}
	}

	if (pInputKeyboard->GetPress(DIK_UP) == true)
	{
		m_pMpGauge->AddGauge(10);
	}
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_pMpGauge->AddGauge(-10);
	}
	if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_pSpGauge->AddGauge(-10);
	}
	else if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_pSpGauge->AddGauge(10);
	}

#endif // DEBUG
}

//================================================
//�`�揈��
//================================================
void CGame01::Draw(void)
{

}

//================================================
//�Q�[���I�[�o�[����
//================================================
void CGame01::GameOver(void)
{
	//�J�E���^�[�����Z
	m_nGameCounter++;

	if (m_pObjet2DGame == nullptr)
	{
		//�T�E���h�擾����
		CSound *pSound;
		pSound = CManager::GetInstance()->GetSound();

		m_pObjet2DGame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                               D3DXVECTOR3(GAME01_GAME_OVER_SIZE_X, GAME01_GAME_OVER_SIZE_Y, 0.0f), CObject::PRIORITY_GAME_OVER);
		//�Q�[���I�[�o�[�̎�
		if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true)
		{
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_GAMEOVER_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_GAMEOVER_SE, 1.8f);

			m_pObjet2DGame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_GAME_OVER"));
		}
		else if (CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
		{//�Q�[���N���A�̎�
			//SE�Đ�
			pSound->Play(CSound::SOUND_LABEL_GAMECLEAR_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_GAMECLEAR_SE, 1.8f);

			m_pObjet2DGame->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_GAME_CLEAR"));
		}
	}

	//����̒l�����傫���Ȃ�����
	if (m_nGameCounter > GAME01_NEXT_SCENE_COUNT)
	{
		//�t�F�[�h�擾����
		CFade *pFade;
		pFade = CManager::GetInstance()->GetFade();

		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			//�Q�[���I�[�o�[�̎�
			if (CManager::GetInstance()->GetPlayData()->GetGameOver() == true)
			{
				pFade->SetFade(CManager::MODE::MENU);
			}
			else if (CManager::GetInstance()->GetPlayData()->GetGameClear() == true)
			{//�Q�[���N���A�̎�
				pFade->SetFade(CManager::MODE::RESULT);
			}
		}
	}
}
