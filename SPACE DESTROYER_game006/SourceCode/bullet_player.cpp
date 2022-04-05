//================================================
//�v���C���[�̒e����
//Authore:��������
//================================================
#include "scene2D.h"
#include "scene.h"
#include "manager.h"
#include "bullet_player.h"
#include "renderer.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "game01.h"
#include "texture.h"
#include "item.h"

#ifndef _DEBUG
//#define NDEBUG
#endif // !_DEBUG
#include <assert.h>

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CBulletPlayer::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CBulletPlayer::CBulletPlayer(int nPriority) :CBullet(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bHoming = false;
	m_nType = BULLET_TYPE_NONE;
	m_nEfectCounter = 0;
	m_fRot = 0.0f;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CBulletPlayer::~CBulletPlayer()
{

}

//================================================
//����������
//================================================
HRESULT CBulletPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, float fRot)
{
	m_pos = pos;
	m_size = size;
	m_move = move;
	m_nEfectCounter = 0;
	m_bHoming = true;
	m_fRot = fRot;

	CBullet::Init(pos, size, m_move);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET_PLAYER);

	return S_OK;
}

//================================================
//�I������
//================================================
void CBulletPlayer::Uninit(void)
{
	CBullet::Uninit();
}

//================================================
//�X�V����
//================================================
void CBulletPlayer::Update(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�ʒu�擾
	m_pos = GetPos();

	m_pos += m_move;		//�ړ��ʔ��f

	//�G�t�F�N�g�̃J�E���^�[�����Z
	m_nEfectCounter++;
	if (m_nEfectCounter >= BULLET_PLAYER_EFFECT_INTERVAL)
	{
		//�G�t�F�N�g�̐���
		CEffect::Create(m_pos, D3DXVECTOR3(30.0f , 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(255.0f, 165.0f, 0.0f, 255.0f),
						CEffect::EFFECT_TYPE_NORMAL);
		m_nEfectCounter = 0;
	}

	//�ʒu���f
	CScene2D::SetPos(m_pos, m_size, m_fRot);


	//��ʊO�ɏo����
	if (m_pos.x + m_size.x / 2.0f < 0.0f || m_pos.x - m_size.x / 2.0f > SCREEN_WIDTH ||
		m_pos.y + m_size.y / 2.0f < 0.0f || m_pos.y - m_size.y / 2.0f > SCREEN_HEIGHT)
	{
		Uninit();
		return;
	}

	//�Q�[���̏�Ԃ��擾
	if (CManager::GetMode() == CManager::MODE_GAME01)
	{
		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
		{
			Uninit();
			return;
		}
	}

	//�ړ��̐ݒ�
	MoveType();
}

//================================================
//�`�揈��
//================================================
void CBulletPlayer::Draw(void)
{
	CBullet::Draw();
}

//================================================
//��������
//================================================
CBulletPlayer *CBulletPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, CBulletPlayer::BULLET_TYPE type, float fRot)
{
	//�C���X�^���X�̐���
	CBulletPlayer *pBulletPlayer = NULL;
	if (pBulletPlayer == NULL)
	{
		pBulletPlayer = new CBulletPlayer;
		if (pBulletPlayer != NULL)
		{
			pBulletPlayer->Init(pos, size, move, fRot);
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_BULLET_PLAYER_NORMAL);
			pBulletPlayer->BindTexture(m_pTexture);
			pBulletPlayer->m_nType = type;
		}
	}
	return pBulletPlayer;
}

//================================================
//�����蔻�菈��
//================================================
float CBulletPlayer::GetRot(void)
{
	return m_fRot;
}

//================================================
//�ړ��ʊǗ�����
//================================================
void CBulletPlayer::MoveType(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	//�G�ƒe�̊p�x�v�Z�p
	float fTanR = 0.0f;
	//�G�̃|�C���^�[
	CEnemy *pEnemy = NULL;
	//�v���C���[�̈ʒu�ۑ��p
	D3DXVECTOR3 posEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�G�ƒe�Ƃ̋���
	float fDiffer = 0;

	switch (m_nType)
	{
	case BULLET_TYPE_STRAIGHT:
		break;

	case BULLET_TYPE_DIFFUSION:

		break;
	case BULLET_TYPE_HOMING:

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

					if (objType == CScene::OBJTYPE_ENEMY)
					{
						//�V�[���̃|�C���^��G�̌^�ɃL���X�g
						pEnemy = (CEnemy*)pScene;

						if (pEnemy != NULL)
						{
							//�G�̂̈ʒu���擾
							posEnemy = pEnemy->GetPos();

							fDiffer = sqrtf(((posEnemy.x - m_pos.x) * (posEnemy.x - m_pos.x)) + ((posEnemy.y - m_pos.y) * (posEnemy.y - m_pos.y)));
							if (fDiffer >= BULLET_PLAYER_FINISH_HOMING)
							{
								if (m_bHoming == true)
								{
									//�v���C���[�̒e�ƓG�̊p�x���v�Z
									fTanR = atan2f(posEnemy.y - m_pos.y, posEnemy.x - m_pos.x);
									//�G�Ɍ������čs���悤�ړ��ʂ��v�Z
									m_move = D3DXVECTOR3(cosf(fTanR) * -BULLET_PLAYER_SPEED, sinf(fTanR) * -BULLET_PLAYER_SPEED, 0.0f);
								}
							}
							else
							{
								m_bHoming = false;
							}
							break;
						}
					}
				}
			}
		}
		break;
	default:
		assert(false);
		break;
	}
}