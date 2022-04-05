//===========================================
//�V�[������
//Author:��������
//===========================================
#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"

//================================================
//�}�N����`
//================================================

//================================================
//�N���X�̒�`
//================================================
//�N���X�̒�`
class CScene
{
public:
	typedef enum
	{
		PRIORITY_NONE = 0,			//�Ȃ�
		PRIORITY_PLAYER,			//�v���C���[
		PRIORITY_MODEL,				//���f��
		PRIORITY_UI,				//UI
		PRIORITY_PAUSE,				//�|�[�Y
		PRIORITY_FADE,				//�t�F�[�h
		PRIORITY_MAX
	} PRIORITY;

	typedef enum
	{
		OBJTYPE_NONE = 0,			//�Ȃ�
		OBJTYPE_PLAYER,				//�v���C���[
		OBJTYPE_MODEL,				//���f��
		OBJTYPE_ENEMY,				//�G
		OBJTYPE_UI,					//UI
		OBJTYPE_MAX
	} OBJTYPE;

	CScene(int nPriority = PRIORITY_NONE);			//�R���X�g���N�^
	virtual ~CScene();								//�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);

	void SetObjType(OBJTYPE objType);			//�I�u�W�F�N�g�^�C�v�ݒ菈��
	OBJTYPE GetObjType(void);					//�I�u�W�F�N�g�^�C�v�擾����
	CScene *GetObjNext(CScene *pObject);		//�����̃I�u�W�F�N�g�̎��̃I�u�W�F�N�g���擾����
	static CScene *GetTopObj(int nPriority);	//�����̃v���C�I���e�B�̐擪�I�u�W�F�N�g�擾����
	D3DXVECTOR3 GetPos(void);					//�ʒu�擾����
	void SetPos(D3DXVECTOR3 pos);				//�ʒu�ݒ菈��
	void SetPosOld(D3DXVECTOR3 posOld);			//1�t���[���O�̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void);				//1�t���[���O�̈ʒu�擾����
	D3DXVECTOR3 GetSize(void);					//�T�C�Y�擾����
	void SetSize(D3DXVECTOR3 size);				//�T�C�Y�ݒ菈��

protected:
	void Release(void);

private:
	static CScene *m_pTop[PRIORITY_MAX];	//�擪�I�u�W�F�N�g�̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];	//����(��Ԍ��)�I�u�W�F�N�g�̃|�C���^
	CScene *m_pPrev;						//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;						//���̃I�u�W�F�N�g�ւ̃|�C���^
	int m_nPriority;						//�D�揇�ʂ̔ԍ�
	OBJTYPE m_objType;						//�I�u�W�F�N�g�̎��
	D3DXVECTOR3 m_pos;						//�|���S���̈ʒu
	D3DXVECTOR3 m_posOld;					//1�t���[���O�̃|���S���̈ʒu
	D3DXVECTOR3 m_size;						//�|���S���̃T�C�Y
	bool m_bDeath;							//���S�t���O
};

#endif // !_SCENE_H_