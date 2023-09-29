//============================================================
//
//	�f�[�^�ۑ��}�l�[�W���[�w�b�_�[ [retentionManager.h]
//	Author�F���c�E��
//
//============================================================
//************************************************************
//	��d�C���N���[�h�h�~
//************************************************************
#ifndef _RETENTION_MANAGER_H_
#define _RETENTION_MANAGER_H_

//************************************************************
//	�C���N���[�h�t�@�C��
//************************************************************
#include "main.h"

//************************************************************
//	�N���X��`
//************************************************************
// �f�[�^�ۑ��}�l�[�W���[�N���X
class CRetentionManager
{
public:
	// ���U���g��
	enum RESULT
	{
		RESULT_NONE,	// ����
		RESULT_FAILED,	// �N���A���s
		RESULT_CLEAR,	// �N���A����
		RESULT_MAX		// ���̗񋓌^�̑���
	};

	// �R���X�g���N�^
	CRetentionManager();

	// �f�X�g���N�^
	~CRetentionManager();

	// �����o�֐�
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V

	// �ÓI�����o�֐�
	static CRetentionManager *Create(void);	// ����
	static HRESULT Release(CRetentionManager *&prRetentionManager);	// �j��

	// �����o�֐�
	void SetResult(const RESULT result);	// �N���A�󋵐ݒ�
	void SetScore(const int nScore);		// �l���X�R�A�ݒ�
	RESULT GetResult(void) const;			// �N���A�󋵎擾
	int GetScore(void) const;				// �l���X�R�A�擾

private:
	// �����o�ϐ�
	RESULT m_result;	// �N���A��
	int m_nScore;		// �l���X�R�A
};

#endif	// _RETENTION_MANAGER_H_
