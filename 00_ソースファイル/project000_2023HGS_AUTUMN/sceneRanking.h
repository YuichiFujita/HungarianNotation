//============================================================
//
//	�����L���O��ʃw�b�_�[ [sceneRanking.h]
//	Author�F����������
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _SCENE_RANKING_H_
#define _SCENE_RANKING_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "scene.h"

//************************************************************
//	�O���錾
//************************************************************
class CRankingManager;	// �����L���O�}�l�[�W���[�N���X
class CBg;				// �w�i�N���X

//************************************************************
//	�N���X��`
//************************************************************
// �����L���O��ʃN���X
class CSceneRanking : public CScene
{
public:
	// �R���X�g���N�^
	CSceneRanking(const MODE mode);

	// �f�X�g���N�^
	~CSceneRanking();

	// �I�[�o�[���C�h�֐�
	HRESULT Init(void) override;	// ������
	HRESULT Uninit(void) override;	// �I��
	void Update(void) override;		// �X�V
	void Draw(void) override;		// �`��

	// �ÓI�����o�֐�
	static CRankingManager *GetRankingManager(void);	// �����L���O�}�l�[�W���[�擾
	static CBg *GetBg(void);	// �w�i�擾

private:
	// �ÓI�����o�ϐ�
	static CRankingManager *m_pRankingManager;	// �����L���O�}�l�[�W���[
	static CBg *m_pBg;	// �w�i�I�u�W�F�N�g
};

#endif	// _SCENE_RESULT_H_
