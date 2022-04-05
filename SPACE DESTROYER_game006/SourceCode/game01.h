//===========================================
//�Q�[��01����
//Authore:��������
//===========================================
#ifndef _GAME01_H_
#define _GAME01_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "enemy.h"
#include "mover.h"

//�O���錾
class CScore;
class CNumber;
class CPolygon;
class CLife;
class CBoss;
class CPlayer;
class CUi;

//================================================
//�}�N����`
//================================================
#define STAGE01_MAX_ENEMY	(128)	//�X�e�[�W1�̓G�̍ő吔
#define STAGE01_MAX_BOSS	(1)		//�X�e�[�W1��BOSS�̍ő吔
#define MAX_PAUSE_UI		(3)		//�|�[�Y����UI�̐�

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CGame01 : public CScene
{
public:
	//�I����
	typedef enum
	{
		SELECT_GAME01_PAUSE_TYPE_NONE = 0,
		SELECT_GAME01_PAUSE_TYPE_CONTINUE,		//Coutinue
		SELECT_GAME01_PAUSE_TYPE_EXIT,			//Exit
		SELECT_GAME01_PAUSE_TYPE_MAX			//�I�����ő�l
	} SELECT_GAME01_PAUSE_TYPE;

	//�Q�[���̏��
	typedef enum
	{
		GAME_STATE_NONE = 0,
		GAME_STATE_GAME,		//�Q�[����
		GAME_STATE_CLEAR,		//�Q�[���N���A
		GAME_STATE_OVER,		//�Q�[���I�[�o�[
		GAME_STATE_MAX
	} GAME_STATE;

	CGame01();				//�R���X�g���N�^
	~CGame01();				//�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetFrame(void);
	static CScore *GetScore(void);
	static CPolygon *GetPolygon(void);
	static CLife *GetLife(void);
	static CBoss *GetBoss(void);
	static bool GetPause(void);						//�|�[�Y�擾����
	static int GetSelect(void);						//�|�[�Y���̑I�����擾����
	GAME_STATE GetState(void);						//�Q�[���̏�Ԏ擾����
	void SetState(GAME_STATE state);				//�Q�[���̏�Ԑݒ菈��
	static int GetFinishCounter(void);				//�I�����Ă���̃t���[����
	
private:
	//�����o�֐�
	void State(void);											//��Ԃɂ�鏈������

	static CScore *m_pScore;									//�X�R�A�|�C���^
	static CPolygon *m_pPolygon;								//�|���S���|�C���^
	static CLife *m_pLife;										//���C�t�|�C���^
	static CBoss *m_pBoss;										//�{�X�|�C���^
	static CUi *m_pUi[MAX_PAUSE_UI];							//UI�̃|�C���^

	static int m_nFrame;										//�Q�[�����J�n���Čo�߂����t���[����
	static int m_nFrameEnemy[STAGE01_MAX_ENEMY];				//�G���o��������t���[�����ۑ��p
	static int m_nFrameBoss[STAGE01_MAX_BOSS];					//�{�X���o��������t���[�����ۑ��p
	static D3DXVECTOR3 m_enemyPos[STAGE01_MAX_ENEMY];			//�G���o���ꏊ�ۑ��p
	static D3DXVECTOR3 m_enemyMove[STAGE01_MAX_ENEMY];			//�G�̈ړ������l�ۑ��p
	static D3DXVECTOR3 m_bossPos[STAGE01_MAX_BOSS];				//�{�X���o���ꏊ�ۑ��p
	static CEnemy::ENEMY_TYPE m_enemyType[STAGE01_MAX_ENEMY];	//�o���G�̃^�C�v�ۑ��p
	static CMover::MOVER_TYPE m_moverType[STAGE01_MAX_ENEMY];	//�o���G�̓������̃^�C�v�ۑ��p
	static int m_nSelect;										//�ǂ̑I�������I������Ă��邩
	static bool m_bPause;										//�|�[�Y�����ǂ����̃t���O
	static int m_nFinishCounter;								//�Q�[���I�����Ă����Frame�J�E���g�p		
	GAME_STATE m_state;											//�Q�[���̏��
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_GAME01_H_