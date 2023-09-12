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
	vector<POINT>	m_frameList;	// 애니메이션 프레임 저장용
	vector<int>		m_playList;		// 애니메이션 플레이 인덱스 저장용

	int		m_frameNum;				// 애니메이션 프레임 갯수
	int		m_frameWidth;			// 프레임 가로크기
	int		m_frameHeight;			// 프레임 세로크기

	float	m_frameUpdateSec;		// 프레임 경과 시간
	float	m_elapsedSec;			// 델타 타임

	int		m_nowPlayIndex;			// 현재 플레이 인덱스
	bool	m_isPlay;				// 애니메이션 재생 여부
	bool	m_isLoop;				// 애니메이션 루프 여부
};
#endif // BANIMATION_H

