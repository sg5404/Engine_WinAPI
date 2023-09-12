#ifndef BANIMATION_H
#define BANIMATION_H

#include "BBasisStd.h"

class BAnimation 
{
public:
	BAnimation();
	~BAnimation();

public:
	void Init(int totalW, int totalH, int frameW, int frameH);
	void Release();

	void SetDefinePlayFrame(bool reverse = false, bool loop = false);
	void SetPlayFrame(int start, int end, bool reverse = false, bool loop = false);
	void SetFPS(int framePerSec);

	void FrameUpdate(float elapsedTime);

	void Start();
	void Stop();
	void Pause();
	void Resume();

public:
	inline bool IsPlay() { return m_isPlay; }
	inline POINT GetFramePos() { return m_frameList[m_playList[m_nowPlayIndex]]; }
	inline int GetFrameWidth() { return m_frameWidth; }
	inline int GetFrameHeight() { return m_frameHeight; }

private:
	vector<POINT>	m_frameList;	// �ִϸ��̼� ������ �����
	vector<int>		m_playList;		// �ִϸ��̼� �÷��� �ε��� �����

	int		m_frameNum;				// �ִϸ��̼� ������ ����
	int		m_frameWidth;			// ������ ����ũ��
	int		m_frameHeight;			// ������ ����ũ��

	float	m_frameUpdateSec;		// ������ ��� �ð�
	float	m_elapsedSec;			// ��Ÿ Ÿ��

	int		m_nowPlayIndex;			// ���� �÷��� �ε���
	bool	m_isPlay;				// �ִϸ��̼� ��� ����
	bool	m_isLoop;				// �ִϸ��̼� ���� ����
};
#endif // BANIMATION_H

