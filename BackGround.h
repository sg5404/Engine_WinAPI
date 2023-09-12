#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "BBasisSys.h"
#include "Player.h"

enum LOOPIMAGE
{
	LOOPBG1,
	LOOPBG2,
	LOOPBG3,
	LOOPBG4,
	LOOPCOUNT
};

typedef struct tagLOOPINFO
{
	int PosX;
	int Speed;
} LOOPINFO;

class BackGround : public Obj
{
public:
	BackGround();
	~BackGround();

public:
	// Obj을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render(HDC hdc, float dt) override;
	virtual void Release() override;

public:
	void SetStage(STAGE stage);
	void SetPlayer(Player* p) { m_Player = p; }

private:
	STAGE		m_Stage;
	Player*		m_Player;
	LOOPINFO	m_LoopInfo[LOOPCOUNT];

	BImage* m_CurrentBG;
	BImage	m_ImageBackGround[STAGE_COUNT];
	BImage  m_ImageLoopBG[LOOPCOUNT];
};

#endif // BACKGROUND_H

