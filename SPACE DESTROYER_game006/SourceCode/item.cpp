//================================================
//�A�C�e������
//Authore:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "item.h"
#include "renderer.h"
#include "texture.h"
#include "player.h"
#include "game01.h"
#include "effect.h"
#include "score.h"
#include "tutorial.h"
#include "sound.h"
#include "ui_move.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CItem::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CItem::CItem(int nPriority) :CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scrollSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = ITEM_TYPE_NONE;
	m_nEfectCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CItem::~CItem()
{

}

//================================================
//����������
//================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D::Init(pos, size);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�`���[�g���A���̏ꍇ
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		m_scrollSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		m_scrollSpeed = D3DXVECTOR3(0.0f, ITEM_SCROLL_SPEED, 0.0f);
	}
	m_size = size;
	m_nEfectCounter = 0;

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	switch (m_type)
	{
	case ITEM_TYPE_SPEED:
		SetObjType(CScene::OBJTYPE_ITEM_SPEED);
		break;
	case ITEM_TYPE_POWER:
		SetObjType(CScene::OBJTYPE_ITEM_POWER);
		break;
	case ITEM_TYPE_SCORE:
		SetObjType(CScene::OBJTYPE_ITEM_SCORE);
		break;
	default:
		break;
	}

	return S_OK;
}

//================================================
//�I������
//================================================
void CItem::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CItem::Update(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos = GetPos();
	pos += m_scrollSpeed;
	pos += m_move;		//�ړ��ʔ��f

	//�����̏���
	Move();

	//�����蔻��
	if (Collision() == true)
	{
		return;
	}

	//�ʒu��ݒ�
	SetPos(pos, m_size);
}

//================================================
//�`�揈��
//================================================
void CItem::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CItem::ITEM_TYPE type)
{
	//�C���X�^���X�̐���
	CItem *pItem = NULL;
	if (pItem == NULL)
	{
		pItem = new CItem;
		if (pItem != NULL)
		{
			pItem->m_type = type;

			switch (type)
			{
			case ITEM_TYPE_SPEED:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_SPEED);
				break;
			case ITEM_TYPE_POWER:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_POWER);
				break;
			case ITEM_TYPE_SCORE:
				m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_ITEM_SCORE);
				break;
			default:
				break;
			}
			pItem->Init(pos, size);
			pItem->BindTexture(m_pTexture);
		}
	}
	return pItem;
}

//================================================
//�����蔻�菈��
//================================================
bool CItem::Collision(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//����̃t���O
	bool bCol = false;

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�I�u�W�F�N�g����
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//�V�[����nCnt�Ԗڂ̃|�C���^�擾
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				//�I�u�W�F�N�g�̃^�C�v���擾
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_PLAYER)		//�I�u�W�F�N�g�̃^�C�v��PLAYER�̎�
				{
					//�擾�����I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾
					D3DXVECTOR3 playerPos = pScene->GetPos();
					D3DXVECTOR3 Itemsize = pScene->GetSize();

					//�����蔻��
					if (pos.x + m_size.x / 2.0f >= playerPos.x - Itemsize.x / 2.0f && pos.x - m_size.x / 2.0f <= playerPos.x + Itemsize.x / 2.0f &&
						pos.y + m_size.y / 2.0f >= playerPos.y - Itemsize.y / 2.0f && pos.y - m_size.y / 2.0f <= playerPos.y + Itemsize.y / 2.0f)
					{
						//�v���C���[���擾
						CPlayer *pPlayer = (CPlayer*)pScene;

						//�A�C�e���̃^�C�v�ɂ���ď����𕪂���
						switch (m_type)
						{
						case ITEM_TYPE_SPEED:
							//BGM�̍Đ�
							pSound->Play(CSound::SOUND_LABEL_ITEM_SPEED_SE);
							//�T�E���h�̉��ʒ���
							pSound->ControllVoice(CSound::SOUND_LABEL_ITEM_SPEED_SE, 1.7f);

							//�`���[�g���A���̏ꍇ
							if (CManager::GetMode() == CManager::MODE_TUTORIAL)
							{
								CTutorial::SetSpeedUp(true);
							}

							//�v���C���[�̎��̒e�����܂ł̊Ԋu�̃��x�����擾�����x���ɂ���ď����𕪂���
							switch (pPlayer->GetBulletSpeedLevel())
							{
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_1:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_2);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_2:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_3);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_3:
								pPlayer->SetBulletSpeedLevel(CPlayer::PLAYER_BULLET_SPEED_LEVEL_3);
								break;
							default:
								break;
							}
							break;
						case ITEM_TYPE_POWER:
							//BGM�̍Đ�
							pSound->Play(CSound::SOUND_LABEL_ITEM_POWER_SE);
							//�T�E���h�̉��ʒ���
							pSound->ControllVoice(CSound::SOUND_LABEL_ITEM_POWER_SE, 1.7f);

							//�`���[�g���A���̏ꍇ
							if (CManager::GetMode() == CManager::MODE_TUTORIAL)
							{
								CTutorial::SetPowerUp(true);
							}

							//�v���C���[�̒e�̃��x�����擾�����x���ɂ���ď����𕪂���
							switch (pPlayer->GetBulletPowerLevel())
							{
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_1:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_2);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_2:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_3);
								break;
							case CPlayer::PLAYER_BULLET_SPEED_LEVEL_3:
								pPlayer->SetBulletPowerLevel(CPlayer::PLAYER_BULLET_POWER_LEVEL_3);
								break;
							default:
								break;
							}
							break;
						case ITEM_TYPE_SCORE:
							//�X�R�A�̃|�C���^�擾
							CScore *pScore;
							pScore = CGame01::GetScore();
							//�X�R�A���Z
							pScore->AddScore(100);
							//�X�R�A�̃|���S������
							CUiMove::Create(D3DXVECTOR3(playerPos.x + 20.0f, playerPos.y - 20.0f, 0.0f), D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
											D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
							break;
						default:
							break;
						}
						//������������
						bCol = true;
						//�A�C�e���̔j��
						Uninit();
						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//�����̏���
//================================================
void CItem::Move(void)
{
	//�ʒu���擾
	D3DXVECTOR3 pos = GetPos();

	if (m_type == CItem::ITEM_TYPE_SCORE)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
			{
				//�V�[����nCnt�Ԗڂ̃|�C���^�擾
				CScene *pScene;
				pScene = CScene::GetScene(nCntScene, nCntPriority);

				if (pScene != NULL)
				{
					//�I�u�W�F�N�g�^�C�v�擾
					CScene::OBJTYPE objType;
					objType = pScene->GetObjType();

					if (objType == CScene::OBJTYPE_PLAYER)
					{
						//�V�[���̃|�C���^��G�̌^�ɃL���X�g
						CPlayer *pPlayer = (CPlayer*)pScene;

						//�v���C���[�̈ʒu���擾
						D3DXVECTOR3 posPlayer = pPlayer->GetPos();
						//�v���C���[�ƃA�C�e���̊p�x���v�Z
						float fTanR = atan2f(posPlayer.y - pos.y, posPlayer.x - pos.x);
						//�v���C���[�Ɍ������čs���悤�ړ��ʂ��v�Z
						m_move = D3DXVECTOR3(cosf(fTanR) * ITEM_COLECT_SPEED, sinf(fTanR) * ITEM_COLECT_SPEED, 0.0f);

						//�G�t�F�N�g�̃J�E���^�[�����Z
						m_nEfectCounter++;
						if (m_nEfectCounter >= ITEM_EFFECT_INTERVAL)
						{
							//�G�t�F�N�g�̐���
							CEffect::Create(pos, m_size, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f),
											CEffect::EFFECT_TYPE_NORMAL);
							m_nEfectCounter = 0;
						}
					}
				}
			}
		}
	}
}