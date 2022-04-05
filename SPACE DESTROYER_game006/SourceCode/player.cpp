//================================================
//�v���C���[����
//Authore:��������
//================================================
#include "scene2D.h"
#include "manager.h"
#include "game01.h"
#include "input_keyboard.h"
#include "input_pad_x.h"
#include "player.h"
#include "bullet_player.h"
#include "renderer.h"
#include "sound.h"
#include "life.h"
#include "texture.h"
#include "item.h"
#include "score.h"
#include "ui_rest.h"
#include "explosion.h"

//================================================
//�ÓI�����o�ϐ��錾
//================================================
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//================================================
//�f�t�H���g�R���X�g���N�^
//================================================
CPlayer::CPlayer(int nPriority):CScene2D(nPriority)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = 0;
	m_nCounterShoot = 0;
	m_nCounterNotShoot = 0;
	m_nNextShoot = 0;
	m_bulletPowerLevel = PLAYER_BULLET_POWER_LEVEL_NONE;
	m_bulletSpeedLevel = PLAYER_BULLET_SPEED_LEVEL_NONE;
	m_state = PLAYER_STATE_NONE;
	m_nDamageCounter = 0;
	m_nBlinkCounter = 0;
	m_bBlink = false;
	m_pUi = NULL;
}

//================================================
//�I�[�o�[���[�h���ꂽ�R���X�g���N�^
//================================================


//================================================
//�f�X�g���N�^
//================================================
CPlayer::~CPlayer()
{

}

//================================================
//����������
//================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	m_size = size;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngle = 0.0f;
	m_nLife = MAX_PLAYER_INIT_LIFE;
	m_nCounterShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
	m_nCounterNotShoot = 0;
	m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
	m_bulletPowerLevel = PLAYER_BULLET_POWER_LEVEL_1;
	m_bulletSpeedLevel = PLAYER_BULLET_SPEED_LEVEL_1;
	m_state = PLAYER_STATE_NORMAL;
	m_nDamageCounter = 0;
	m_nBlinkCounter = 0;
	m_bBlink = false;


	CScene2D::Init(pos, size);

	//�e�N�X�`�����f
	CScene2D::SetTex(TEXPATTERN_SENTER, TEXPATTERN_MAX);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);
	return S_OK;
}

//================================================
//�I������
//================================================
void CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//================================================
//�X�V����
//================================================
void CPlayer::Update(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();
	pos += m_move;		//�ړ��ʔ��f

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		//�ړ�����
		Move(pInputKeyboard, pInputPadX);

		//�ˌ�����
		Shoot();
	}
	else if (CManager::GetMode() == CManager::MODE_GAME01)
	{
		//�Q�[���̏�Ԏ擾
		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_GAME)
		{
			//�ړ�����
			Move(pInputKeyboard, pInputPadX);

			//�ˌ�����
			Shoot();
		}
		else if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_CLEAR)
		{
			m_nDamageCounter = PLAYER_DAMAGE_COUNT;
			//�ړ��ʂ�0�ɂ���
			m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		if (CManager::GetGame01()->GetState() == CGame01::GAME_STATE_OVER)
		{
			//�Q�[���I�[�o�[���̏���
			if (GameOver() == true)
			{
				return;
			}
		}
		//���C�t��0�ɂȂ�����Q�[���I�[�o�[�ɂ���
		if (m_nLife <= 0)
		{
			CManager::GetGame01()->SetState(CGame01::GAME_STATE_OVER);
		}
	}


	//�ړ�����
	pos = MoveLimit(pos);

	//��Ԃɂ��F�̕ω�����
	StateColor();

	//�ʒu���f
	CScene2D::SetPos(pos, m_size);

	//�`���[�g���A���ł͓����蔻����s��Ȃ�
	if (CManager::GetMode() != CManager::MODE_TUTORIAL)
	{
		//�v���C���[�̏�Ԃ��_���[�W���󂯂Ă����ԂłȂ���Γ����蔻����s��
		if (m_state != PLAYER_STATE_DAMAGE)
		{
			//�����蔻��
			if (Collision(pos, pSound) == true)
			{
				return;
			}
		}
	}
}

//================================================
//�`�揈��
//================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//================================================
//��������
//================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�C���X�^���X�̐���
	CPlayer *pPlayer = NULL;
	if (pPlayer == NULL)
	{
		pPlayer = new CPlayer;
		if (pPlayer != NULL)
		{
			m_pTexture = CManager::GetTexture()->GetTexture(CTexture::TYPE_PLAYER);
			pPlayer->Init(pos, size);
			pPlayer->BindTexture(m_pTexture);
		}
	}
	return pPlayer;
}

//================================================
//�v���C���[�ړ���������
//================================================
D3DXVECTOR3 CPlayer::MoveLimit(D3DXVECTOR3 pos)
{
	if (pos.x - m_size.x / 2.0f <= 0.0f)
	{
		pos.x = 0.0f + m_size.x / 2.0f;
	}
	else if (pos.x + m_size.x / 2.0f >= SCREEN_WIDTH)
	{
		pos.x = SCREEN_WIDTH - m_size.x / 2.0f;
	}
	if (pos.y - m_size.y / 2.0f <= 0.0f)
	{
		pos.y = 0.0f + m_size.y / 2.0f;
	}
	else if (pos.y + m_size.y / 2.0f >= SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - m_size.y / 2.0f;
	}

	return pos;
}

//================================================
//�����蔻�菈��
//================================================
bool CPlayer::Collision(D3DXVECTOR3 pos, CSound *pSound)
{
	//���C�t�̃|�C���^�擾
	CLife *pLife;
	pLife = CGame01::GetLife();

	//����̃t���O
	bool bCol = false;

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

				if (objType == CScene::OBJTYPE_ENEMY)		//�I�u�W�F�N�g�̃^�C�v��ENEMY�̎�
				{
					//�擾�����I�u�W�F�N�g�̈ʒu�ƃT�C�Y���擾
					D3DXVECTOR3 EnemyPos = pScene->GetPos();
					D3DXVECTOR3 Enemysize = pScene->GetSize();

					//�����蔻��
					if (pos.x + m_size.x / 2.0f - PLAYER_COLLISION_ADJUST >= EnemyPos.x - Enemysize.x / 2.0f &&
						pos.x - m_size.x / 2.0f + PLAYER_COLLISION_ADJUST <= EnemyPos.x + Enemysize.x / 2.0f &&
						pos.y + m_size.y / 2.0f - PLAYER_COLLISION_ADJUST >= EnemyPos.y - Enemysize.y / 2.0f &&
						pos.y - m_size.y / 2.0f + PLAYER_COLLISION_ADJUST <= EnemyPos.y + Enemysize.y / 2.0f)
					{
						//������������
						bCol = true;
						//�T�E���h�̍Đ�
						pSound->Play(CSound::SOUND_LABEL_EXPLOSION_SE);
						//�G�̔j��
						pScene->Uninit();
						//���C�t�����炷
						m_nLife--;
						//���C�t��ݒ�
						pLife->SubtractLife(1);
						//�v���C���[�̏�Ԃ��_���[�W�ɂ���
						m_state = PLAYER_STATE_DAMAGE;

						break;
					}
				}
			}
		}
	}
	return bCol;
}

//================================================
//�ړ�����
//================================================
void CPlayer::Move(CInputKeyboard *pInputKeyboard, CInputPadX *pInputPadX)
{
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();
	
	//�e�N�X�`�����f
	CScene2D::SetTex(TEXPATTERN_SENTER, TEXPATTERN_MAX);

	//-----------------------------------------
	//�{�^�������������Ă���Ƃ��̏���
	//-----------------------------------------
	if (pInputKeyboard->GetPress(DIK_A) == true ||							//A�L�[���������Ƃ��̏���
		pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_LEFT) == true)		//���X�e�B�b�N�����ɓ|�����Ƃ��̏���
	{
		m_move.x = -PLAYER_MOVE;
		//�e�N�X�`�����f
		CScene2D::SetTex(TEXPATTERN_LEFT, TEXPATTERN_MAX);

		if (pInputKeyboard->GetPress(DIK_W) == true ||						//W�L�[���������Ƃ��̏���
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//���X�e�B�b�N����ɓ|�����Ƃ��̏���
		{
			if (pos.y - m_size.y / 2.0f != 0.0f)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true ||						//S�L�[���������Ƃ��̏���
				pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//���X�e�B�b�N�����ɓ|�����Ƃ��̏���
		{
			if (pos.y + m_size.y / 2.0f != SCREEN_HEIGHT)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * PLAYER_MOVE;
			}
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||							//D�L�[���������Ƃ��̏���
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_RIGHT) == true)		//���X�e�B�b�N���E�ɓ|�����Ƃ��̏���
	{
		m_move.x = PLAYER_MOVE;
		//�e�N�X�`�����f
		CScene2D::SetTex(TEXPATTERN_RIGHT, TEXPATTERN_MAX);

		if (pInputKeyboard->GetPress(DIK_W) == true ||						//W�L�[���������Ƃ��̏���
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//���X�e�B�b�N����ɓ|�����Ƃ��̏���
		{
			if (pos.y - m_size.y / 2.0f != 0.0f)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * -PLAYER_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true ||						//S�L�[���������Ƃ��̏���
				pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//���X�e�B�b�N�����ɓ|�����Ƃ��̏���
		{
			if (pos.y + m_size.y / 2.0f != SCREEN_HEIGHT)
			{
				m_move.x = cosf(D3DX_PI / 4.0f) * PLAYER_MOVE;
				m_move.y = sinf(D3DX_PI / 4.0f) * PLAYER_MOVE;
			}
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true ||						//W�L�[���������Ƃ��̏���
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_UP) == true)		//���X�e�B�b�N����ɓ|�����Ƃ��̏���
	{
		m_move.y = -PLAYER_MOVE;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true ||						//S�L�[���������Ƃ��̏���
			pInputPadX->GetLeftStick(CInputPadX::STICKTYPE_DOWN) == true)	//���X�e�B�b�N�����ɓ|�����Ƃ��̏���
	{
		m_move.y = PLAYER_MOVE;
	}

	//-----------------------------------------
	////�{�^���𗣂����u�Ԃ̏���
	//-----------------------------------------
	if (pInputKeyboard->GetRelease(DIK_A) == true ||							//A�L�[�𗣂����Ƃ��̏���
		pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
	{
		m_move.x = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//D�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//�E�ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.y = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//A�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.y = 0.0f;
		}
	}
	else if (pInputKeyboard->GetRelease(DIK_D) == true ||							//D�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//�E�ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
	{
		m_move.x = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//D�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//�E�ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.y = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//A�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.y = 0.0f;
		}
	}
	if (pInputKeyboard->GetRelease(DIK_W) == true ||							//W�L�[�𗣂����Ƃ��̏���
		pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_UP) == true)		//��ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
	{
		m_move.y = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//D�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//�E�ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.x = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//A�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.x = 0.0f;
		}
	}
	else if (pInputKeyboard->GetRelease(DIK_S) == true ||							//S�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_DOWN) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
	{
		m_move.y = 0.0f;

		if (pInputKeyboard->GetPress(DIK_D) == true ||								//D�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_RIGHT) == true)	//�E�ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.x = 0.0f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true ||							//A�L�[�𗣂����Ƃ��̏���
			pInputPadX->GetLeftStickRelease(CInputPadX::STICKTYPE_LEFT) == true)	//���ɓ|�������X�e�B�b�N��߂����Ƃ��̏���
		{
			m_move.x = 0.0f;
		}
	}
}

//================================================
//�ˌ�����
//================================================
void CPlayer::Shoot(void)
{
	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	//�L�[�{�[�h�擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�v���C���[�̒e�̃��x���ɉ����Ď��̒e���o��܂ł̊Ԋu��ύX
	switch (m_bulletSpeedLevel)
	{
	case PLAYER_BULLET_SPEED_LEVEL_1:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_1;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_2:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_2;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_3:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_3;
		break;
	case PLAYER_BULLET_SPEED_LEVEL_4:
		m_nNextShoot = PLAYER_BULLET_NEXT_SHOOT_LEVEL_4;
		break;
	default:
		break;
	}

	//�����Ă��Ȃ��Ƃ��J�E���^�[�𑝂₷
	m_nCounterNotShoot++;

	if (pInputKeyboard->GetPress(DIK_SPACE) == true ||			//�X�y�[�X�L�[�������ꂽ��
		pInputPadX->GetButtonPress(XINPUT_GAMEPAD_A) == true)		//A�{�^���������ꂽ��
	{
		//�����Ă�Ƃ��J�E���^�[�𑝂₷
		m_nCounterShoot++;

		switch (m_bulletPowerLevel)
		{
		case PLAYER_BULLET_POWER_LEVEL_1:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//�����Ă��Ȃ��J�E���^�[�����Z�b�g
				m_nCounterNotShoot = 0;
				//�����Ă鎞�̃J�E���^�[�����Z�b�g
				m_nCounterShoot = 0;
				//�e�̐���
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);

				//�T�E���h�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_2:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//�����Ă��Ȃ��J�E���^�[�����Z�b�g
				m_nCounterNotShoot = 0;
				//�����Ă鎞�̃J�E���^�[�����Z�b�g
				m_nCounterShoot = 0;
				//�e�̐���
				CBulletPlayer::Create(D3DXVECTOR3(pos.x + PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z), 
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//�e�̐���
				CBulletPlayer::Create(D3DXVECTOR3(pos.x - PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z),
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//�T�E���h�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_3:
			if (m_nCounterShoot >= m_nNextShoot || m_nCounterNotShoot >= m_nNextShoot)
			{
				//�����Ă��Ȃ��J�E���^�[�����Z�b�g
				m_nCounterNotShoot = 0;
				//�����Ă鎞�̃J�E���^�[�����Z�b�g
				m_nCounterShoot = 0;
				//�e�̐���
				CBulletPlayer::Create(D3DXVECTOR3(pos.x + PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z), 
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//�e�̐���
				CBulletPlayer::Create(D3DXVECTOR3(pos.x - PLAYER_BULLET_POWER_LEVEL_2_POS_X, pos.y, pos.z),
										D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(0.0f, BULLET_PLAYER_SPEED, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, 0.0f);
				//�e�̐���
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(20.0f, 0.0f, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, -D3DX_PI / 2.0f);
				//�e�̐���
				CBulletPlayer::Create(pos, D3DXVECTOR3(BULLET_PLAYER_WIDTH, BULLET_PLAYER_HEIGHT, 0.0f),
										D3DXVECTOR3(-20.0f, 0.0f, 0.0f), CBulletPlayer::BULLET_TYPE_STRAIGHT, D3DX_PI / 2.0f);
				//�T�E���h�̍Đ�
				pSound->Play(CSound::SOUND_LABEL_BULLET_SE);
				//�T�E���h�̉��ʒ���
				pSound->ControllVoice(CSound::SOUND_LABEL_BULLET_SE, 0.2f);
			}
			break;
		case PLAYER_BULLET_POWER_LEVEL_4:

			break;
		default:
			break;
		}
	}
}

//================================================
//�e�̃��x���ݒ菈��
//================================================
void CPlayer::SetBulletPowerLevel(PLAYER_BULLET_POWER_LEVEL bulletPowerLevel)
{
	m_bulletPowerLevel = bulletPowerLevel;
}

//================================================
//�e�̃��x���擾����
//================================================
CPlayer::PLAYER_BULLET_POWER_LEVEL CPlayer::GetBulletPowerLevel(void)
{
	return m_bulletPowerLevel;
}

//================================================
//���̒e�����܂ł̑����̃��x���ݒ菈��
//================================================
void CPlayer::SetBulletSpeedLevel(PLAYER_BULLET_SPEED_LEVEL bulletSpeedLevel)
{
	m_bulletSpeedLevel = bulletSpeedLevel;
}

//================================================
//���̒e�����܂ł̑����̃��x���擾����
//================================================
CPlayer::PLAYER_BULLET_SPEED_LEVEL CPlayer::GetBulletSpeedLevel(void)
{
	return m_bulletSpeedLevel;
}

//================================================
//��Ԃɉ������F�ɕω������鏈��
//================================================
void CPlayer::StateColor(void)
{
	//�p�b�h�擾����
	CInputPadX *pInputPadX;
	pInputPadX = CManager::GetInputPadX();

	switch (m_state)
	{
	case PLAYER_STATE_NORMAL:
		break;
	case PLAYER_STATE_DAMAGE:
		//�J�E���^�[�����Z
		m_nDamageCounter++;
		m_nBlinkCounter++;
		//�_���[�W���󂯂��u�ԃ}�X�N�𐶐�
		if (m_nDamageCounter == 1)
		{
			//�o�C�u���[�V�����ݒ�
			pInputPadX->SetVibration(60000, 60000, 30);

			m_pUi = CUiRest::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f),
									D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),
									CUiRest::UI_REST_TYPE_DAMAGE_MASK);
		}

		if (m_nBlinkCounter >= PLAYER_BLINK_COUNT)
		{
			m_nBlinkCounter = 0;
			if (m_bBlink == false)
			{
				//��������
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));
				m_bBlink = true;
			}
			else
			{
				//���ɖ߂�
				SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_bBlink = false;
			}
		}

		if (m_nDamageCounter >= PLAYER_DAMAGE_COUNT)
		{
			//�}�X�N��j��
			m_pUi->Uninit();
			m_pUi = NULL;
			//�J�E���^�[��0�ɂ���
			m_nDamageCounter = 0;
			//��Ԃ�NORMAL�ɖ߂�
			m_state = PLAYER_STATE_NORMAL;
			//���ɖ߂�
			SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_bBlink = false;
		}
		break;
	default:
		break;
	}
}

//================================================
//�v���C���[�̏�Ԏ擾����
//================================================
CPlayer::PLAYER_STATE CPlayer::GetPlayerState(void)
{
	return m_state;
}

//================================================
//�v���C���[�̏�Ԑݒ菈��
//================================================
void CPlayer::SetPlayerState(CPlayer::PLAYER_STATE state)
{
	m_state = state;
}

//================================================
//�v���C���[�̃��C�t�擾����
//================================================
int CPlayer::GetLife(void)
{
	return m_nLife;
}

//================================================
//�v���C���[�̃��C�t�ݒ菈��
//================================================
void CPlayer::SetLife(int nLife)
{
	m_nLife += nLife;
}

//================================================
//�Q�[���I�[�o�[���̏���
//================================================
bool CPlayer::GameOver(void)
{
	//�T�E���h�擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	//�ʒu�擾
	D3DXVECTOR3 pos = GetPos();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�t���[�����擾
	int nClearCounter = CGame01::GetFinishCounter();

	if (nClearCounter == PLAYER_OVER_UNINIT_COUNT)
	{
		//�{�X��j��
		Uninit();
		return true;
	}
	else
	{
		if (nClearCounter % PLAYER_OVER_EXPLOSION_COUNT == 0)
		{
			//�T�E���h�̍Đ�
			pSound->Play(CSound::SOUND_LABEL_DIE_EXPLOSION_SE);
			//�T�E���h�̉��ʒ���
			pSound->ControllVoice(CSound::SOUND_LABEL_BOSS_BULLET_SE, 1.6f);

			//�����̐���
			CExplosion::Create(pos, D3DXVECTOR3(EXPLOSION_WIDTH, EXPLOSION_HEIGHT, 0.0f));
		}
	}
	return false;
}