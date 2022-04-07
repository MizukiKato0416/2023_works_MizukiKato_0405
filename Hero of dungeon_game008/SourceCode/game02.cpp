//================================================
//�Q�[��02����
//Author: KatoMizuki
//================================================
#define _CRT_SECURE_NO_WARNINGS
#include "game02.h"
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
#define GAME02_RECOVERYCOUNT	(20)		//�񕜂���p�x
#define GAME02_NEXT_SCENE_COUNT	(180)		//���̃V�[���܂ł̃J�E���g
#define GAME02_GAME_OVER_SIZE_X	(914.0f)	//�Q�[���I�[�o�[�̃T�C�YX
#define GAME02_GAME_OVER_SIZE_Y	(128.0f)	//�Q�[���I�[�o�[�̃T�C�YY

//================================================
//�ÓI�����o�ϐ��錾
//================================================

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CGame02::CGame02(int nPriority):CObject(nPriority)
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
CGame02::~CGame02()
{

}

//================================================
//����������
//================================================
HRESULT CGame02::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
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

	
	//�X�e�[�W�f�[�^�̓ǂݍ���
	//���[�h����
	FILE *pFile;
	pFile = fopen("data/STAGE/stage02.csv", "r");
	int nCntX = 0, nCntZ = 0;
	char aLine[64];
	int nDepth = 7;		//�c�̐�
	int nWidth = 5;		//���̐�
	int aMapData[7][5];
	while (fgets(aLine, 64, pFile) != nullptr)
	{
		nCntX = 0;
		char *pToken = strtok(aLine, ",");
		while (pToken != nullptr)
		{
			int nNum = atoi(pToken);
			aMapData[nCntZ][nCntX] = nNum;
			pToken = strtok(nullptr, ",");
			nCntX++;
		}
		nCntZ++;
	}
	fclose(pFile);

	//�����̐���
	for (nCntZ = 0; nCntZ < nDepth ; nCntZ++)
	{
		for (nCntX = 0; nCntX < nWidth ; nCntX++)
		{
			if (aMapData[nCntZ][nCntX] == 1)
			{
				//�ǂ̕���
				CDungeonRoomDirector::Create(pDungeonWallBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//�ǂ̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WALL);
			}
			else if (aMapData[nCntZ][nCntX] == 2)
			{
				//�X�^�[�g�̕���
				CDungeonRoomDirector::Create(pDungeonStartRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//�X�^�[�g�n�_�̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::START);
			}
			else if (aMapData[nCntZ][nCntX] == 3)
			{
				//�G�����铹
				CDungeonRoomDirector::Create(pDungeonEnemyRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							                                                       0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//���̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);
			}
			else if (aMapData[nCntZ][nCntX] == 4)
			{
				//�S�[���̕���
				CDungeonRoomDirector::Create(pDungeonEndRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
																				 0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//���[�v�̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::WARP);
			}
			else if (aMapData[nCntZ][nCntX] == 5)
			{
				//�`�F�b�N�|�C���g�����铹
				CDungeonRoomDirector::Create(pDungeonCheckRoadBuilder, D3DXVECTOR3(DUNGEON_ROOM_BUILDER_SIZE * (nCntX - (nWidth - 1) / 2.0f),
							                                                       0.0f, DUNGEON_ROOM_BUILDER_SIZE * (nCntZ - (nDepth - 1) / 2.0f)));
				//���̃}�b�v�����
				CMap::Create(D3DXVECTOR3(MAP_ROOM_SIZE * (nCntX - (nWidth - 1) / 2.0f),
					                     -MAP_ROOM_SIZE * (nCntZ - (nDepth - 1) / 2.0f),
					                     0.0f),
					         D3DXVECTOR3(MAP_ROOM_SIZE, MAP_ROOM_SIZE, 0.0f), CObject::PRIORITY_MAP, CMap::TYPE::ROAD);
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
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP_FRAME"));

	//HP�����擾
	int nHp = CManager::GetInstance()->GetPlayData()->GetHitPoint();
	//HP�Q�[�W�̐���
	m_pHpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_HP_POS_X, GAUGE_HP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_HP_SIZE_X, GAUGE_HP_SIZE_Y, 0.0f), PLAYER_MAX_HP, nHp);
	m_pHpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_GAUGE"));
	//HP����ݒ�
	CManager::GetInstance()->GetPlayData()->SetHpGauge(m_pHpGauge);

	//MP�����擾
	int nMp = CManager::GetInstance()->GetPlayData()->GetMagicPoint();
	//MP�Q�[�W�̐���
	m_pMpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_MP_POS_X, GAUGE_MP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_MP_SIZE_X, GAUGE_MP_SIZE_Y, 0.0f), PLAYER_MAX_MP, nMp);
	m_pMpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_MP_GAUGE"));
	//MP����ݒ�
	CManager::GetInstance()->GetPlayData()->SetMpGauge(m_pMpGauge);

	//SP�����擾
	int nSp = CManager::GetInstance()->GetPlayData()->GetSpecialPoint();
	//SP�Q�[�W�̐���
	m_pSpGauge = CGauge::Create(D3DXVECTOR3(GAUGE_SP_POS_X, GAUGE_SP_POS_Y, 0.0f),
		                        D3DXVECTOR3(GAUGE_SP_SIZE_X, GAUGE_SP_SIZE_Y, 0.0f), PLAYER_MAX_SP, nSp);
	m_pSpGauge->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_SP_GAUGE"));
	//SP����ݒ�
	CManager::GetInstance()->GetPlayData()->SetSpGauge(m_pSpGauge);

	//UI�̐���
	pObject2D = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), CObject::PRIORITY_UI);
	pObject2D->BindTexture(CManager::GetInstance()->GetTexture()->GetTexture("TEX_TYPE_UI_HP_MP_SP"));

	//�^�C���̐���
	CTime::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, TIME_POLIGON_POSY, 0.0f), D3DXVECTOR3(TIME_POLYGON_WIDTH, TIME_POLYGON_HEIGHT, 0.0f),
		          CManager::GetInstance()->GetPlayData()->GetTime());

	//�X�R�A�̐���
	CScore *pSocre = nullptr;
	pSocre = CScore::Create(D3DXVECTOR3(0.0f + (SCORE_POLYGON_WIDTH * MAX_SCORE_POLYGON / 2.0f), SCORE_POLYGON_HEIGHT / 2.0f, 0.0f),
							D3DXVECTOR3(SCORE_POLYGON_WIDTH, SCORE_POLYGON_HEIGHT, 0.0f));
	CManager::GetInstance()->GetPlayData()->SetScorePoint(pSocre);

	//�X�R�A�̐ݒ�
	pSocre->SetScore(CManager::GetInstance()->GetPlayData()->GetScore());

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
void CGame02::Uninit(void)
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
void CGame02::Update(void)
{
	//�J�E���^�[�����Z
	m_nRecoveryCounter++;
	//����̒l�ȏ�ɂȂ�����
	if (m_nRecoveryCounter >= GAME02_RECOVERYCOUNT)
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
			pFade->SetFade(CManager::MODE::GAME03);
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
void CGame02::Draw(void)
{

}

//================================================
//�Q�[���I�[�o�[����
//================================================
void CGame02::GameOver(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//�J�E���^�[�����Z
	m_nGameCounter++;

	if (m_pObjet2DGame == nullptr)
	{
		m_pObjet2DGame = CObject2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
			                               D3DXVECTOR3(GAME02_GAME_OVER_SIZE_X, GAME02_GAME_OVER_SIZE_Y, 0.0f), CObject::PRIORITY_GAME_OVER);
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
	if (m_nGameCounter > GAME02_NEXT_SCENE_COUNT)
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
