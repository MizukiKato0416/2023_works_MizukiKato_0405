//================================================
//�G����
//Authore:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "input_keyboard.h"
#include "enemy.h"
#include "enemy_Item_power.h"
#include "bullet.h"
#include "bullet_player.h"
#include "renderer.h"
#include "sound.h"
#include "scene.h"
#include "texture.h"
#include "mover.h"
#include "score.h"
#include "game01.h"
#include "explosion.h"
#include "sound.h"
#include "item.h"
#include "effect.h"
#include "tutorial.h"
#include "ui_move.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;				//���L�e�N�X�`���̃|�C���^

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CEnemy::CEnemy(int nPriority) :CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntFrame = 0;
	m_pMover = NULL;
	m_moverType = CMover::MOVER_TYPE_NONE;
	m_nLife = 0;
	m_nBulletCounter = 0;
	m_state = ENEMY_STATE_NONE;
	m_type = ENEMY_TYPE_NONE;
	m_nDamageCounter = 0;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CEnemy::~CEnemy()
{

}

//================================================
//����������
//================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	m_size = size;
	m_pos = pos;
	m_move = move;
	m_nCntFrame = 0;
	m_state = ENEMY_STATE_NORMAL;
	m_nDamageCounter = 0;

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_ENEMY);

	CScene2D::Init(pos, size);
	return S_OK;
}

//================================================
//�I������
//================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CEnemy::Update(void)
{
	//��Ԃɂ��F�̕ω�����
	StateColor();
	//�����蔻��
	if (Collision() == true)
	{
		return;
	}
}

//================================================
//�`�揈��
//================================================
void CEnemy::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move)
{
	//�C���X�^���X�̐���
	CEnemy *pEnemy = NULL;
	if (pEnemy == NULL)
	{
		pEnemy = new CEnemy;
		if (pEnemy != NULL)
		{
			pEnemy->Init(pos, size, move);
		}
	}
	return pEnemy;
}

//================================================
//��Ԃɉ������F�ɕω������鏈��
//================================================
void CEnemy::StateColor(void)
{
	switch (m_state)
	{
	case ENEMY_STATE_NORMAL:
		break;
	case ENEMY_STATE_DAMAGE:
		//�J�E���^�[�����Z
		m_nDamageCounter++;
		if (m_nDamageCounter >= ENEMY_DAMAGE_COUNT)
		{
			//�J�E���^�[��0�ɂ���
			m_nDamageCounter = 0;
			//��Ԃ�NORMAL�ɖ߂�
			m_state = ENEMY_STATE_NORMAL;
			//�F�����ɖ߂�
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			//�Ԃ�����
			SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		break;
	default:
		break;
	}
}

//================================================
//�����蔻�菈��
//================================================
bool CEnemy::Collision(void)
{
	//�ʒu�擾
	m_pos = GetPos();

	//�X�R�A�̃|�C���^�擾
	CScore *pScore;
	pScore = CGame01::GetScore();

	bool bCol = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
		{
			//�V�[����nCnt�Ԗڂ̃|�C���^�擾
			CScene *pScene;
			pScene = CScene::GetScene(nCntScene, nCntPriority);

			if (pScene != NULL)
			{
				CScene::OBJTYPE objType;
				objType = pScene->GetObjType();

				if (objType == CScene::OBJTYPE_BULLET_PLAYER)
				{
					//�e�̃T�C�Y�ƈʒu�擾
					D3DXVECTOR3 BulletPlayerPos = pScene->GetPos();
					D3DXVECTOR3 BulletPlayerSize = pScene->GetSize();
					//�e�̌����擾
					CBulletPlayer *pBulletPlayer = (CBulletPlayer*)pScene;
					float fBulletPlayerRot = pBulletPlayer->GetRot();
					//�T�C�Y��e�̌����ɂ���Ē���
					D3DXVECTOR3 BulletSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					if (fBulletPlayerRot == 0.0f)
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.x, BulletPlayerSize.y, 0.0f);
					}
					else
					{
						BulletSize = D3DXVECTOR3(BulletPlayerSize.y, BulletPlayerSize.x, 0.0f);
					}

					if (m_pos.x + m_size.x / 2.0f >= BulletPlayerPos.x - BulletSize.x / 2.0f && m_pos.x - m_size.x / 2.0f <= BulletPlayerPos.x + BulletSize.x / 2.0f &&
						m_pos.y + m_size.y / 2.0f >= BulletPlayerPos.y - BulletSize.y / 2.0f && m_pos.y - m_size.y / 2.0f <= BulletPlayerPos.y + BulletSize.y / 2.0f)
					{
						//�T�E���h�擾����
						CSound *pSound;
						pSound = CManager::GetSound();
						//������������
						bCol = true;
						//�����̐���
						CExplosion::Create(BulletPlayerPos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
						//�T�E���h�̍Đ�
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);	
						//�G�̏�Ԃ��_���[�W�ɂ���
						m_state = ENEMY_STATE_DAMAGE;
						//�e�̔j��
						pScene->Uninit();
						//�G�̃��C�t�����炷
						m_nLife--;
						if (m_nLife <= 0)
						{
							m_nLife = 0;

							//�G�̎�ނɂ���ď�������
							switch (m_type)
							{
							case ENEMY_TYPE_FIGHTER:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									CTutorial::SetEnemyKill(true);
								}
								else
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�A�C�e���̐���
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
									//�X�R�A�̃|���S������
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							case ENEMY_TYPE_SPHERE:
								//�X�R�A���Z
								pScore->AddScore(400);
								//�A�C�e���̐���
								CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
								//�X�R�A�̃|���S������
								CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
												D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_400);
								break;
							case ENEMY_TYPE_UFO:
								//�X�R�A���Z
								pScore->AddScore(200);
								//�A�C�e���̐���
								CItem::Create(m_pos, D3DXVECTOR3(ITEM_SCORE_WIDTH, ITEM_SCORE_HEIGHT, 0.0f), CItem::ITEM_TYPE_SCORE);
								//�X�R�A�̃|���S������
								CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
												D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_200);
								break;
							case ENEMY_TYPE_ITEM_POWER:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									//�A�C�e���̐���
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_POWER);
								}
								else
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�A�C�e���̐���
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_POWER);
									//�X�R�A�̃|���S������
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f),
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							case ENEMY_TYPE_ITEM_SPEED:
								if (CManager::GetMode() == CManager::MODE_TUTORIAL)
								{
									//�A�C�e���̐���
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_SPEED);
								}
								else
								{
									//�X�R�A���Z
									pScore->AddScore(100);
									//�A�C�e���̐���
									CItem::Create(m_pos, D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0.0f), CItem::ITEM_TYPE_SPEED);
									//�X�R�A�̃|���S������
									CUiMove::Create(m_pos, D3DXVECTOR3(UI_ENEMY_KILL_SCORE_WIDTH, UI_ENEMY_KILL_SCORE_HEIGHT, 0.0f), 
													D3DXVECTOR3(0.0f, 0.0f, 0.0f), CUiMove::UI_MOVE_TYPE_ENEMY_KILL_SCORE_100);
								}
								break;
							default:
								break;
							}
							//�G�t�F�N�g�̐���
							for (int nCntEffect = 0; nCntEffect < ENEMY_DELETE_EFFECT_IN_MAX; nCntEffect++)
							{
								CEffect::Create(m_pos, D3DXVECTOR3(ENEMY_DELETE_EFFECT_IN_SIZE, ENEMY_DELETE_EFFECT_IN_SIZE, 0.0f),
												D3DXVECTOR3(ENEMY_DELETE_EFFECT_IN_MOVE * cosf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_IN_MAX) * nCntEffect),
															ENEMY_DELETE_EFFECT_IN_MOVE * sinf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_IN_MAX) * nCntEffect), 0.0f),
												D3DXCOLOR(255.0f, 255.0f, 0.0f, 255.0f), CEffect::EFFECT_TYPE_NORMAL);
							}
							for (int nCntEffect = 0; nCntEffect < ENEMY_DELETE_EFFECT_OUT_MAX; nCntEffect++)
							{
								CEffect::Create(m_pos, D3DXVECTOR3(ENEMY_DELETE_EFFECT_OUT_SIZE, ENEMY_DELETE_EFFECT_OUT_SIZE, 0.0f),
												D3DXVECTOR3(ENEMY_DELETE_EFFECT_OUT_MOVE * cosf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_OUT_MAX) * nCntEffect),
															ENEMY_DELETE_EFFECT_OUT_MOVE * sinf(((D3DX_PI * 2.0f) / ENEMY_DELETE_EFFECT_OUT_MAX) * nCntEffect), 0.0f),
												D3DXCOLOR(0.0f, 120.0f, 255.0f, 255.0f), CEffect::EFFECT_TYPE_NORMAL);
							}
							//�G�̔j��
							Uninit();
						}
						break;
					}
				}
			}
		}
	}
	return bCol;
}