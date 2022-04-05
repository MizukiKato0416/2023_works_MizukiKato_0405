//===========================================
//���U���g����
//Author:��ˌ�
//===========================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "player.h"

//================================================
//�O���錾
//================================================
class CRanking;
class CScene2D;
class CMeshField;
class CMeshSphere;
class CModelSingle;
class CUi;

//================================================
//�}�N����`
//================================================
#define RESULT_TO_TITLE_COUNT			(900)				//�^�C�g���ɍs���܂ł̊Ԋu
#define RESULT_RANKING_POSY				(60.0f)				//�����L���O��posY
#define RESULT_MAX_MODEL				(60)				//���U���g�̃��f���ő吔
#define RESULT_MAX_UI					(2)					//���U���g��UI�ő吔
#define RESULT_PLAYERNUMBER_SIZE_X		(360.0f * 1.6f)		//�v���C���[�i���o�[�̃T�C�YX
#define RESULT_PLAYERNUMBER_SIZE_Y		(300.0f * 1.6f)		//�v���C���[�i���o�[�̃T�C�YY
#define RESULT_PLAYERNUMBER_POS_X		(450.0f)			//�v���C���[�i���o�[�̈ʒuX
#define RESULT_PLAYERNUMBER_POS_Y		(200.0f)			//�v���C���[�i���o�[�̈ʒuY
#define RESULT_WIN_SIZE_X				(1637.0f * 0.6f)	//WINUI�̃T�C�YX
#define RESULT_WIN_SIZE_Y				(415.0f * 0.6f)		//WINUI�̃T�C�YY
#define RESULT_WIN_POS_X				(800.0f)			//WINUI�̈ʒuX
#define RESULT_WIN_POS_Y				(200.0f)			//WINUI�̈ʒuY
#define RESULT_WORLD_SIZE				(20000.0f)			//���E�̑傫��

//========================================================
//�\���̂̒�`
//========================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CResult : public CScene
{
public:
	CResult();				//�R���X�g���N�^
	~CResult();				//�f�X�g���N�^

							//�����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nTitleCounter;								//�^�C�g���ɍs���܂ł̃J�E���^�[
	CRanking *m_pRanking;								//�����L���O�̃|�C���^
	CMeshField *m_pMeshField;							//���b�V���t�B�[���h�̃|�C���^
	CMeshSphere *m_pMeshSphere;							//���b�V���X�t�B�A�̃|�C���^
	CPlayer *m_apPlayer[MAX_PLAYER];					//�v���C���[�̃|�C���^
	CModelSingle *m_apModelSingle[RESULT_MAX_MODEL];	//���f���̃|�C���^
	CScene2D *m_pScene2D;								//Scene2D�̃|�C���^
	CUi *m_apUi[RESULT_MAX_UI];							//UI�̃|�C���^
};

//================================================
//�v���g�^�C�v�錾
//================================================
#endif // !_RESULT_H_